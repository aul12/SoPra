/**
 * @file Environment.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the Environment
 */

#include "Environment.hpp"
#include "Config.hpp"
#include "../Model/Item.hpp"
#include "../Model/DoublePoints.hpp"
#include "../Model/Invulnerable.hpp"
#include "../Model/Troll.hpp"
#include "../Model/TurboMode.hpp"

#include <fstream>

namespace controller {

    Environment::Environment(std::string fname) : points{0},
                                                  pointMultiplexer{1}, invulnerable{false},
                                                  config{fname},
                                                  randomNumberGenerator{std::random_device{}()} {
        player = model::Player{{config.player.xPosInFrame, config.environment.height/2},
                               {config.player.width, config.player.height}};
    }

    auto Environment::update(double deltaT) -> UpdateResult {
        assert(deltaT > 0);

        // Move the player
        player.accelerate({config.player.accelerationSide,config.gravity}, deltaT);
        player.move(deltaT);

        // Check if in bounds
        if(player.getBoundingRect().bottomLeft().get(1) < 0
           || player.getBoundingRect().topLeft().get(1) > config.environment.height) {
            return UpdateResult::GAME_OVER;
        }

        auto newActiveObst = isAtObstacle();
        if (activeObstacle.has_value() && !newActiveObst.has_value()) {
            activeObstacle.reset();
            points += pointMultiplexer;
        } else if (newActiveObst.has_value()) {
            activeObstacle = newActiveObst;
        }

        // Check for collision with obstacles
        for (const auto obstacle : obstacles) {
            if (player.getBoundingRect().intersects(obstacle->getBoundingRect())) {
                if (invulnerable) {
                    this->activeItem.value()->remove(*this);
                    this->activeItem.reset();
                } else {
                    return UpdateResult::GAME_OVER;
                }
            }
        }

        // Handle active items
        if(this->activeItem.has_value()) {
            this->activeItem.value()->decreaseRemainingTimeBy(deltaT);
            if(this->activeItem.value()->getRemainingTime() <= 0) {
                this->activeItem.value()->remove(*this);
                this->activeItem.reset();
            }
        } else {
            for (const auto &item : items) {
                if (player.getBoundingRect().intersects(item->getBoundingRect())) {
                    this->activeItem = item;
                    this->activeItem.value()->apply(*this);
                    items.clear();
                }
            }
        }

        // Create new items/obstacles and delete old ones
        this->updateItems();
        this->updateObstacles();

        return UpdateResult::UPDATED;
    }

    void Environment::playerUp(double t) {
        assert(t > 0);
        player.accelerate({0,config.player.accelerationUp}, t);
    }

    void Environment::updateObstacles() {
        removeOutOfScope(obstacles);
        double lastObstaclePosX = findLastItem(obstacles);

        double distFromRightEdge =
                config.environment.width - (lastObstaclePosX - player.getPosition().get(0) + config.player.xPosInFrame);
        // New obstacle required
        if(distFromRightEdge > config.obstacles.deltaX) {
            std::uniform_real_distribution<double> gen(config.obstacles.minHeight, config.obstacles.maxHeight);
            double bottomHeight = gen(randomNumberGenerator);
            double topHeight = gen(randomNumberGenerator);
            double xPos = player.getPosition().get(0) - config.player.xPosInFrame +
                          config.environment.width + config.obstacles.width;
            obstacles.push_back(std::make_shared<model::Obstacle>(model::Vec{xPos, topHeight/2},
                                                                  model::Vec{config.obstacles.width, topHeight}, model::ObstacleSide::TOP));
            obstacles.push_back(std::make_shared<model::Obstacle>(model::Vec{xPos, config.environment.height - bottomHeight/2},
                                                                  model::Vec{config.obstacles.width, bottomHeight}, model::ObstacleSide::BOTTOM));
        }
    }

    void Environment::updateItems() {
        removeOutOfScope(items);
        double lastItemPositionX =  findLastItem(items);

        double distFromRightEdge =
                config.environment.width - (lastItemPositionX - player.getPosition().get(0) + config.player.xPosInFrame);
        // New item possible
        if(distFromRightEdge > config.items.minDist && !activeItem.has_value()) {
            std::uniform_real_distribution<double> newRequiredGen(0,1);

            // New item required
            if(newRequiredGen(randomNumberGenerator) < config.items.spawnProb) {
                double xPos = player.getPosition().get(0) - config.player.xPosInFrame +
                              config.environment.width + config.obstacles.width;
                std::normal_distribution heightDistribution(config.environment.height/2,
                                                            config.environment.height * config.items.heightStandardDeviationScale);
                double yPos = heightDistribution(randomNumberGenerator);
                model::Vec pos{xPos, yPos};
                model::Vec size{config.items.width, config.items.height};
                double lifetime = config.items.lifetime;

                std::uniform_int_distribution<int> itemTypeDist(0,3);

                // Decide which item to use. @TODO this is ugly
                int itemType = itemTypeDist(randomNumberGenerator);
                switch (itemType) {
                    case 0: // Double Points
                        this->items.push_back(std::make_shared<model::DoublePoints>(pos, size, lifetime));
                        break;
                    case 1: // Invulnerable
                        this->items.push_back(std::make_shared<model::Invulnerable>(pos, size, lifetime));
                        break;
                    case 2: // Troll
                        this->items.push_back(std::make_shared<model::Troll>(pos, size, lifetime));
                        break;
                    case 3: // TurboMode
                        this->items.push_back(std::make_shared<model::TurboMode>(pos, size, lifetime));
                        break;
                    default:
                        // We really shouldn't be here
                        throw std::runtime_error("It seems like uniform_int_distribution is broken");
                }
            }
        }
    }

    template <typename T>
    void Environment::removeOutOfScope(std::deque<std::shared_ptr<T>> &gameItems) {
        if(gameItems.size() > 0) {
            gameItems.erase(std::remove_if(gameItems.begin(), gameItems.end(),
                                           [this](const std::shared_ptr<T> item) {
                                               return
                                                       toLocal(item->getBoundingRect().topRight()).get(0) < 0;
                                           }), gameItems.end());
        }
    }

    template<typename T>
    auto Environment::findLastItem(std::deque<std::shared_ptr<T>> &gameItems) -> double {
        // Find the last item
        double lastItemPositionX = 0;
        for (auto iter = gameItems.begin(); iter != gameItems.end(); iter++) {
            if ((*iter)->getPosition().get(0) > lastItemPositionX) {
                lastItemPositionX = (*iter)->getPosition().get(0);
            }
        }

        return lastItemPositionX;
    }

    auto Environment::getObstacles() const -> std::deque<std::shared_ptr<model::Obstacle>> {
        return obstacles;
    }

    auto Environment::getItems() const -> std::deque<std::shared_ptr<model::Item>> {
        return items;
    }

    auto Environment::getPlayer() const -> model::Player {
        return player;
    }

    auto Environment::getConfig() const -> controller::Config {
        return config;
    }

    auto Environment::toLocal(model::Vec global) -> model::Vec {
        return {global.get(0) - player.getPosition().get(0) + config.player.xPosInFrame,
                global.get(1)};
    }

    auto Environment::toGlobal(model::Vec local) -> model::Vec {
        return {local.get(0) + player.getPosition().get(0) - config.player.xPosInFrame,
                local.get(1)};
    }

    auto Environment::isAtObstacle() -> std::optional<std::shared_ptr<model::Obstacle>> {
        for (const auto obstacle : obstacles) {
            if (player.getBoundingRect().topRight().get(0) >= obstacle->getBoundingRect().topLeft().get(0) &&
                player.getBoundingRect().topLeft().get(0) <= obstacle->getBoundingRect().topRight().get(0)) {

                return {obstacle};
            }
        }
        return {};
    }

    auto Environment::getPoints() const -> int {
        return points;
    }
}