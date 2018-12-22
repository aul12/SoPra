/**
 * @file Environment.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the Environment
 */

#include "Environment.hpp"
#include "Config.hpp"

#include <fstream>
namespace controller {

    Environment::Environment(std::string fname) : config{fname},
        randomNumberGenerator(std::random_device{}()){
    }

    auto Environment::update(double deltaT) -> UpdateResult {
        // Move the player
        player.accelerate({config.player.accelerationSide,config.gravity/config.player.mass}, deltaT);
        player.move(deltaT);

        // Check for collision with obstacles
        for (const auto obstacle : obstacles) {
            if(player.getBoundingRect().intersects(obstacle->getBoundingRect())) {
                return UpdateResult::GAME_OVER;
            }
        }

        // Check if item is collected
        for (const auto &item : items) {
            if(player.getBoundingRect().intersects(item->getBoundingRect())) {
                this->activeItem = item;
                this->activeItem.value().get()->apply();
                items.clear();
            }
        }

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

                //@TODO implement me when all items exist
                //this->items.push_back(std::make_shared<model::Item>())
            }
        }
    }

    template <typename T>
    auto Environment::removeOutOfScopeAndGetLastX(std::deque<std::shared_ptr<T>> &gameItems) -> double{
        // Remove old items and check if new items are required
        double lastItemPositionX = 0;
        for (auto iter = gameItems.begin(); iter != gameItems.end(); iter++) {
            // Item is completely out of frame at the left side
            if((*iter).get()->getBoundingRect().topRight().get(0) < player.getPosition().get(0) - config.player.xPosInFrame) {
                gameItems.erase(iter);
            } else if ((*iter).get()->getPosition().get(0) > lastItemPositionX) {
                lastItemPositionX = (*iter).get()->getPosition().get(0);
            }
        }
        return lastItemPositionX;
    }
}