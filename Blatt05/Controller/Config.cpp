/**
 * @file Config.cpp
 * @author paul
 * @date 27.12.18
 * @brief Implementation of the Config class
 */

#include "Config.hpp"

#include <fstream>

namespace controller {
    Config::Config(const std::string &fname) {
        std::ifstream ifstream{fname};
        nlohmann::json json;
        if (!ifstream.good()) {
            throw std::runtime_error("Could not open the config file");
        }

        try {
            ifstream >> json;
            this->gameConfig = json.at("game").get<GameConfig>();
            this->resourceConfig = json.at("resource").get<ResourceConfig>();
        } catch (nlohmann::json::exception &e) {
            throw std::runtime_error(e.what());
        }
    }

    auto Config::getGameConfig() -> const GameConfig & {
        return gameConfig;
    }

    auto Config::getResourceConfig() -> const ResourceConfig & {
        return resourceConfig;
    }
}
