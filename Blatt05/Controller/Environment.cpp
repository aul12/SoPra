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

    Environment::Environment(std::string fname) : config{fname},
                                                  randomNumberGenerator{std::random_device{}()},
                                                  points{0}, timeMultiplexer{1}, pointMultiplexer{1}, invulnerable{false},
                                                  items{}, obstacles{}, activeItem{} {
        player = model::Player{{config.player.xPosInFrame, config.environment.height/2},
                               {config.player.width, config.player.height}};
    }

    auto Environment::update(double deltaT) -> UpdateResult {
        assert(deltaT > 0);

        // Move the player
        player.accelerate({config.player.accelerationSide,config.gravity/config.player.mass}, deltaT);
        player.move(deltaT);

        // Check if in bounds
        if(player.getBoundingRect().bottomLeft().get(1) < 0
           || player.getBoundingRect().topLeft().get(1) > config.environment.height) {
            return UpdateResult::GAME_OVER;
        }

        // Check for collision with obstacles
        for (const auto obstacle : obstacles) {
            if(player.getBoundingRect().intersects(obstacle->getBoundingRect())) {
                return UpdateResult::GAME_OVER;
            }
        }

        // Handle active items
        if(this->activeItem.has_value()) {
            this->activeItem.value().get()->decreaseRemainingTimeBy(deltaT);
            if(this->activeItem.value().get()->getRemainingTime() <= 0) {
                this->activeItem.reset();
            }
        } else {
            for (const auto &item : items) {
                if (player.getBoundingRect().intersects(item->getBoundingRect())) {
                    this->activeItem = item;
                    this->activeItem.value().get()->apply(*this);
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
        player.accelerate({0,config.player.accelerationUp}, t);
    }

    void Environment::updateObstacles() {
        double lastObstaclePosX = removeOutOfScopeAndGetLastX(obstacles);

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
        double lastItemPositionX = removeOutOfScopeAndGetLastX(items);

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
    auto Environment::removeOutOfScopeAndGetLastX(std::deque<std::shared_ptr<T>> &gameItems) -> double{
        // Remove old items
        if(gameItems.size() > 0) {
            gameItems.erase(std::remove_if(gameItems.begin(), gameItems.end(),
                                           [this](const std::shared_ptr<T> &item) {
                                               return item.get()->getBoundingRect().topRight().get(0) <
                                                      player.getPosition().get(0) - config.player.xPosInFrame;
                                           }));
        }

        // Find the last item
        double lastItemPositionX = 0;
        for (auto iter = gameItems.begin(); iter != gameItems.end(); iter++) {
            if ((*iter).get()->getPosition().get(0) > lastItemPositionX) {
                lastItemPositionX = (*iter).get()->getPosition().get(0);
            }
        }

        return lastItemPositionX;
    }

}