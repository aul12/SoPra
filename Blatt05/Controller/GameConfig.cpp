/**
 * @file Config.cpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of the Config class
 */

#include "GameConfig.hpp"

namespace controller {
    void from_json(const nlohmann::json &json, GameConfig &gc) {
        try {
            gc.gravity = json.at("gravity");
            gc.environment.height = json.at("environment").at("height");
            gc.environment.width = json.at("environment").at("width");
            gc.player.width = json.at("player").at("width");
            gc.player.height = json.at("player").at("height");
            gc.player.mass = json.at("player").at("mass");
            gc.player.accelerationUp = json.at("player").at("accelerationUp");
            gc.player.xPosInFrame = json.at("player").at("xPosInFrame");
            gc.player.accelerationSide = json.at("player").at("accelerationSide");
            gc.obstacles.deltaX = json.at("obstacles").at("deltaX");
            gc.obstacles.maxHeight = json.at("obstacles").at("maxHeight");
            gc.obstacles.minHeight = json.at("obstacles").at("minHeight");
            gc.obstacles.width = json.at("obstacles").at("width");
            gc.items.height = json.at("items").at("height");
            gc.items.width = json.at("items").at("width");
            gc.items.minDist = json.at("items").at("minDist");
            gc.items.spawnProb = json.at("items").at("spawnProb");
            gc.items.heightStandardDeviationScale = json.at("items").at("heightStandardDeviationScale");
            gc.items.troll.minScale = json.at("items").at("troll").at("minScale");
            gc.items.troll.maxScale = json.at("items").at("troll").at("maxScale");
            gc.items.turbo.deltaY = json.at("items").at("turbo").at("deltaY");
            gc.items.turbo.speedMultiplier = json.at("items").at("turbo").at("speedMultiplier");
            gc.items.lifetime = json.at("items").at("lifetime");
        } catch (nlohmann::json::exception &e) {
            throw std::runtime_error(e.what());
        }
    }
}
