/**
 * @file TurboMode.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the TurboMode class
 */

#include "TurboMode.hpp"
#include "../Controller/GameConfig.hpp"

namespace model {
    void TurboMode::apply(controller::Environment &environment) {
        oldGravity = environment.gameConfig.gravity;
        oldUpAcceleration = environment.gameConfig.player.accelerationUp;
        oldMaxObstacle = environment.gameConfig.obstacles.maxHeight;

        double pathTop = environment.player.getBoundingRect().topRight()[1] - environment.gameConfig.items.turbo.deltaY;
        double pathBottom = environment.player.getBoundingRect().bottomRight()[1] + environment.gameConfig.items.turbo.deltaY;

        for (auto &obstacle : environment.obstacles) {
            double scale = 1.0;
            if(obstacle->getObstacleSide() == ObstacleSide::TOP) {
                if (obstacle->getBoundingRect().bottomRight()[1] > pathTop) {
                    scale = pathTop / obstacle->getBoundingRect().bottomRight()[1];
                }
            } else {
                if(obstacle->getBoundingRect().topRight()[1] < pathBottom) {
                    double relPathBottom = environment.gameConfig.environment.height - pathBottom;
                    double relHeight =
                            environment.gameConfig.environment.height - obstacle->getBoundingRect().topRight()[1];
                    scale = relPathBottom / relHeight;
                }
            }
            obstacle->setHeightScale(scale);
        }

        environment.gameConfig.gravity = 0;
        environment.gameConfig.player.accelerationUp = 0;
        environment.gameConfig.obstacles.maxHeight = std::min(pathTop, environment.gameConfig.environment.height-pathBottom);

        environment.player.setSpeed(
                {environment.player.getSpeed().get(0) * environment.gameConfig.items.turbo.speedMultiplier, 0});
    }

    void TurboMode::remove(controller::Environment &environment) {
        environment.gameConfig.gravity = oldGravity;
        environment.gameConfig.player.accelerationUp = oldUpAcceleration;
        environment.player.setSpeed(
                {environment.player.getSpeed().get(0) * (1.0/environment.gameConfig.items.turbo.speedMultiplier), 0});
        environment.gameConfig.obstacles.maxHeight = oldMaxObstacle;

        for (auto &obstacle : environment.obstacles) {
            obstacle->resetScale();
        }
    }
}
