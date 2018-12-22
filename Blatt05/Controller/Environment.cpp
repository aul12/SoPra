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

    Environment::Environment(std::string fname) : config{fname} {
    }

    auto Environment::update(double deltaT) -> UpdateResult {
        player.accelerate({0,config.gravity/config.player.mass}, deltaT);

        for (const auto &obstacle : obstacles) {
            if(player.getBoundingRect().intersects(obstacle.getBoundingRect())) {
                return UpdateResult::GAME_OVER;
            }
        }

        return UpdateResult::UPDATED;
    }

    void Environment::playerUp(double t) {
        player.accelerate({0,config.player.accelerationUp}, t);
    }
}