/**
 * @file TurboMode.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the TurboMode class
 */

#include "TurboMode.hpp"
#include "../Controller/Config.hpp"

namespace model {
    void TurboMode::apply(controller::Environment &environment) {
        oldGravity = environment.config.gravity;
        oldUpAcceleration = environment.config.player.accelerationUp;
        oldMaxObstacle = environment.config.obstacles.maxHeight;

        double pathTop = environment.player.getBoundingRect().topRight()[1] - environment.config.items.turbo.deltaY;
        double pathBottom = environment.player.getBoundingRect().bottomRight()[1] + environment.config.items.turbo.deltaY;

        for (auto &obstacle : environment.obstacles) {
            double scale = 1.0;
            if(obstacle.get()->getObstacleSide() == ObstacleSide::TOP) {
                if (obstacle.get()->getBoundingRect().bottomRight()[1] > pathTop) {
                    scale = pathTop / obstacle.get()->getBoundingRect().bottomRight()[1];
                }
            } else {
                if(obstacle.get()->getBoundingRect().topRight()[1] < pathBottom) {
                    double relPathBottom = environment.config.environment.height - pathBottom;
                    double relHeight =
                            environment.config.environment.height - obstacle.get()->getBoundingRect().topRight()[1];
                    scale = relPathBottom / relHeight;
                }
            }
            obstacle.get()->setHeightScale(scale);
        }

        environment.config.gravity = 0;
        environment.config.player.accelerationUp = 0;
        environment.config.obstacles.maxHeight = std::min(pathTop, environment.config.environment.height-pathBottom);

        environment.player.setSpeed(
                {environment.player.getSpeed().get(0) * environment.config.items.turbo.speedMultiplier, 0});
    }

    void TurboMode::remove(controller::Environment &environment) {
        environment.config.gravity = oldGravity;
        environment.config.player.accelerationUp = oldUpAcceleration;
        environment.player.setSpeed(
                {environment.player.getSpeed().get(0) * (1.0/environment.config.items.turbo.speedMultiplier), 0});
        environment.config.obstacles.maxHeight = oldMaxObstacle;

        for (auto &obstacle : environment.obstacles) {
            obstacle.get()->resetScale();
        }
    }
}
