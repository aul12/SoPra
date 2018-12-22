/**
 * @file Config.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of Config class
 * @TODO
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>

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
            struct {
                double x, y;
            } initial;
        } player;
        struct {
            double width, height;
        } environment;
        double gravity;
    };
}

#endif
