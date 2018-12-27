/**
 * @file Troll.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the Troll class
 */

#include "Troll.hpp"
#include "../Controller/GameConfig.hpp"

namespace model {

    void Troll::apply(controller::Environment &environment) {
        std::uniform_real_distribution<double> scaleDist(environment.gameConfig.items.troll.minScale,
                environment.gameConfig.items.troll.maxScale);
        double scale = scaleDist(environment.randomNumberGenerator);
        oldMinHeight = environment.gameConfig.obstacles.minHeight;
        oldMaxHeight = environment.gameConfig.obstacles.maxHeight;

        environment.gameConfig.obstacles.minHeight *= scale;
        environment.gameConfig.obstacles.maxHeight *= scale;

        for (auto obstacle : environment.obstacles) {
            obstacle->setHeightScale(scale);
        }
    }

    void Troll::remove(controller::Environment &environment) {
        environment.gameConfig.obstacles.minHeight = oldMinHeight;
        environment.gameConfig.obstacles.maxHeight = oldMaxHeight;

        for (auto &obstacle : environment.obstacles) {
            obstacle.get()->resetScale();
        }
    }
}