/**
 * @file Config.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of Config class
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

namespace controller {
    /**
     * Implements an interface for deserialization of the config.json file
     */
    class Config {
    public:
        /**
         * Read the config from a json file
         * @param fname the path to the json file
         */
        explicit Config(std::string fname);

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
            } turbo;
        } items;
        double gravity;
    };
}

#endif
