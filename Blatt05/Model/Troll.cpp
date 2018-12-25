/**
 * @file Troll.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the Troll class
 */

#include "Troll.hpp"
#include "../Controller/Config.hpp"

namespace model {

    void Troll::apply(controller::Environment &environment) {
        std::uniform_real_distribution<double> scaleDist(environment.config.items.troll.minScale,
                environment.config.items.troll.maxScale);
        double scale = scaleDist(environment.randomNumberGenerator);
        oldMinHeight = environment.config.obstacles.minHeight;
        oldMaxHeight = environment.config.obstacles.maxHeight;

        environment.config.obstacles.minHeight *= scale;
        environment.config.obstacles.maxHeight *= scale;

        for (auto obstacle : environment.obstacles) {
            obstacle->setHeightScale(scale);
        }
    }

    void Troll::remove(controller::Environment &environment) {
        environment.config.obstacles.minHeight = oldMinHeight;
        environment.config.obstacles.maxHeight = oldMaxHeight;

        for (auto &obstacle : environment.obstacles) {
            obstacle.get()->resetScale();
        }
    }
}