/**
 * @file Config.cpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of the Config class
 */

#include "Config.hpp"

#include <fstream>

#include "../Lib/json.hpp"

namespace controller {
    using json = nlohmann::json;

    Config::Config(std::string fname) {
        std::ifstream ifstream(fname);
        if(!ifstream.is_open() || !ifstream.good()) {
            throw std::runtime_error("Could not open config.json");
        }

        try {
            json json;
            ifstream >> json;

            this->gravity = json["gravity"];
            this->environment.height = json["environment"]["height"];
            this->environment.width = json["environment"]["width"];
            this->player.width = json["player"]["width"];
            this->player.height = json["player"]["height"];
            this->player.mass = json["player"]["mass"];
            this->player.accelerationUp = json["player"]["accelerationUp"];
            this->player.xPosInFrame = json["player"]["xPosInFrame"];
            this->player.accelerationSide = json["player"]["accelerationSide"];
            this->obstacles.deltaX = json["obstacles"]["deltaX"];
            this->obstacles.maxHeight = json["obstacles"]["maxHeight"];
            this->obstacles.minHeight = json["obstacles"]["minHeight"];
            this->obstacles.width = json["obstacles"]["width"];
            this->items.height = json["items"]["height"];
            this->items.width = json["items"]["width"];
            this->items.minDist = json["items"]["minDist"];
            this->items.spawnProb = json["items"]["spawnProb"];
            this->items.heightStandardDeviationScale = json["items"]["heightStandardDeviationScale"];
            this->items.troll.minScale = json["items"]["troll"]["minScale"];
            this->items.troll.maxScale = json["items"]["troll"]["maxScale"];
            this->items.turbo.deltaY = json["items"]["turbo"]["deltaY"];
            this->items.lifetime = json["items"]["lifetime"];
        } catch (json::exception &e) {
            throw std::runtime_error(e.what());
        }
    }
}
