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

            this->gravity = json[gravity];
            this->environment = {
                .height = json["environment"]["height"],
                .width = json["environment"]["width"]
            };
            this->player = {
                .width = json["player"]["width"],
                .height = json["player"]["height"],
                .mass = json["player"]["mass"],
                .accelerationUp = json["player"]["accelerationUp"],
                .initial = {
                    .x = json["player"]["initial"]["x"],
                    .y = json["player"]["initial"]["y"],
                }
            };
        } catch (json::exception e) {
            throw std::runtime_error(e.what());
        }
    }
}
