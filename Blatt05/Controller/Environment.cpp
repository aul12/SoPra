/**
 * @file Environment.cpp
 * @author paul
 * @date 22.12.18
 * @brief Environment @TODO
 *
 * @TODO
 */

#include "Environment.hpp"
#include "Config.hpp"

#include <fstream>
namespace controller {

    Environment::Environment(std::string fname) : config{fname} {
    }

    void Environment::update(double deltaT) {
        player.accelerate({0,config.gravity/config.player.mass}, deltaT);
    }

    void Environment::playerUp(double t) {
        player.accelerate({0,config.player.accelerationUp}, t);
    }
}