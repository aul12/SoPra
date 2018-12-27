/**
 * @file ResourceConfig.hpp
 * @author paul
 * @date 27.12.18
 * @brief Declaration of the ResourceConfig class
 */

#ifndef RESOURCECONFIG_HPP
#define RESOURCECONFIG_HPP

#include "../Lib/json.hpp"

namespace controller {

    /**
     * Implements an in memory representation of the resource part of the config.json file.
     * All changes that are made to the values are temporary and the original file
     * does not get changed.
     */
    class ResourceConfig {
    public:
        std::string font;
        std::string help;
        struct {
            std::string player;
            struct {
                std::string top, bottom;
            } obstacles;
            struct {
                std::string doublePoints, invulnerable, troll, turboMode;
            } items;
        } textures;
    };

    /**
     * This function is used by nlohmann::json for deserialization
     * @param json the root json object
     * @param resourceConfig the ResourceConfig to create
     * @see: https://github.com/nlohmann/json#arbitrary-types-conversions
     */
    void from_json(const nlohmann::json &json, ResourceConfig &resourceConfig);
}

#endif //TEST_RESOURCECONFIG_HPP
