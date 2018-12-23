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

        for (auto &obstacle : environment.obstacles) {
            obstacle.get()->setHeightScale(scale);
        }
    }

    void Troll::remove(controller::Environment &environment) {
        for (auto &obstacle : environment.obstacles) {
            obstacle.get()->resetScale();
        }
    }
}