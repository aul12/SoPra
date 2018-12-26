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
     * Implements an in memory representation of the config.json file.
     * All changes that are made to the values are temporary and the original file
     * does not gez changed.
     */
    class Config {
    public:
        /**
         * Read the config from a json file or creates an new file if it doesn't exist.
         * @param fname the path to the json file
         * @throws std::runtime_exception if the file is not a json file or not in the right format.
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
                double speedMultiplier;
            } turbo;
        } items;
        double gravity;
    };
}

#endif
