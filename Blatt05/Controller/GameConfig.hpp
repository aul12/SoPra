/**
 * @file Config.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of Config class
 */

#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP

#include <string>
#include "../Lib/json.hpp"

namespace controller {
    /**
     * Implements an in memory representation of the game part of the config.json file.
     * All changes that are made to the values are temporary and the original file
     * does not get changed.
     */
    class GameConfig {
    public:
        struct {
            double accelerationUp;
            double mass;
            double width;
            double height;
            double xPosInFrame;
            double accelerationSide;
        } player;
        struct {
            double width, height;
        } environment;
        struct {
            double deltaX;
            double minHeight, maxHeight;
            double width;
        } obstacles;
        struct {
            double width, height;
            double minDist;
            double spawnProb;
            double heightStandardDeviationScale;
            double lifetime;
            struct {
                double minScale;
                double maxScale;
            } troll;
            struct {
                double deltaY;
                double speedMultiplier;
            } turbo;
        } items;
        double gravity;
    };

    /**
     * This function is used by nlohmann::json for deserialization
     * @param json the root json object
     * @param gc the game config to create
     * @see: https://github.com/nlohmann/json#arbitrary-types-conversions
     */
    void from_json(const nlohmann::json& json, GameConfig& gc);
}

#endif
