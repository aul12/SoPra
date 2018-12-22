/**
 * @file Config.cpp
 * @author paul
 * @date 22.12.18
 * @brief Config @TODO
 *
 * @TODO
 */

#include "Config.hpp"

#include "../Lib/json.hpp"

namespace controller {
    using json = nlohmann::json;

    Config::Config(std::string fname) {
        std::ifstream ifstream(fname);
        if(!ifstream.is_open()) {
            throw std::runtime_error("Could not open config.json");
        }

        try {
            json json;
            ifstream >> json;
        } catch (json::exception e) {
            throw std::runtime_error(e.what());
        }
    }
}
