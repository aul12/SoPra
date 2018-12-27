/**
 * @file Config.hpp
 * @author paul
 * @date 27.12.18
 * @brief Declaration of the Config class
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "GameConfig.hpp"
#include "ResourceConfig.hpp"

namespace controller {
    /**
     * Represents an in memory representation of the config.json file.
     */
    class Config {
    public:
        /**
         * Reads the json file and creates a resource and a game config
         * @param fname the path to the file
         * @throws std::runtime_error if the file doesn't exists or is malformed
         */
        explicit Config(const std::string &fname);

        /**
         * Returns the game part of the config
         * @return returns the GameConfig of the Config
         * @see GameConfig
         */
        auto getGameConfig() -> const GameConfig&;

        /**
         * Returns the resource part of the config
         * @return returns the ResourceConfig of the Config
         * @see ResourceConfig
         */
        auto getResourceConfig() -> const ResourceConfig&;
    private:
        GameConfig gameConfig;
        ResourceConfig resourceConfig;
    };
}


#endif
