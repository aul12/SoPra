/**
 * @file TurboMode.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the TurboMode class
 */

#include "TurboMode.hpp"

namespace model {
    void TurboMode::apply(controller::Environment &environment) {
        oldGravity = environment.config.gravity;
        environment.player.setSpeed({environment.player.getSpeed().get(0) * 5, 0});

        double pathTop = environment.player.getBoundingRect().topRight()[1];

        for (auto &obstacle : environment.obstacles) {

        }
    }

    void TurboMode::remove(controller::Environment &environment) {
        environment.config.gravity = oldGravity;
        environment.player.setSpeed({environment.player.getSpeed().get(0) * (1.0/5), 0});
    }
}
