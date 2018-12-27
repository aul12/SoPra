/**
 * @file ResourceConfig.cpp
 * @author paul
 * @date 27.12.18
 * @brief Implementation of the ResourceConfig class
 */

#include "ResourceConfig.hpp"

namespace controller {
    void from_json(const nlohmann::json &json, ResourceConfig &resourceConfig) {
        resourceConfig.font = json.at("font");
        resourceConfig.help = json.at("help");
        resourceConfig.textures.player = json.at("textures").at("player");
        resourceConfig.textures.obstacles.top = json.at("textures").at("obstacles").at("top");
        resourceConfig.textures.obstacles.bottom = json.at("textures").at("obstacles").at("bottom");
        resourceConfig.textures.items.doublePoints = json.at("textures").at("items").at("doublePoints");
        resourceConfig.textures.items.invulnerable = json.at("textures").at("items").at("invulnerable");
        resourceConfig.textures.items.troll = json.at("textures").at("items").at("troll");
        resourceConfig.textures.items.turboMode = json.at("textures").at("items").at("turboMode");
    }
}
