/**
 * @file Environment.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of the Environment class
 */

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <deque>
#include <optional>
#include <random>
#include <memory>
#include "../Model/Obstacle.hpp"
#include "../Model/Player.hpp"
#include "Config.hpp"

/*
 * At this point a forward declaration is necessary, else we get issues because we have a cyclic dependency
 * graph (Environment, Item, DoublePoints).
 */
namespace model {
    class DoublePoints;
    class Invulnerable;
    class Troll;
    class TurboMode;
    class Item;
}

namespace controller {
    enum class UpdateResult {
        UPDATED, GAME_OVER
    };

    /**
     * The environment class implements an container for all model items and is responsible for the physics
     */
    class Environment {
    friend class model::DoublePoints;
    friend class model::Invulnerable;
    friend class model::Troll;
    friend class model::TurboMode;
    public:
        /**
         * Create an environment with a given config
         * @param configFile path to the configuration json file
         */
        Environment(std::string configFile);

        /**
         * Calculate the physics and rules for the next time step
         * @param deltaT the time difference to the last time step
         */
        auto update(double deltaT) -> UpdateResult;

        /**
         * Accelerate the player upwards
         * @param t the time the player should get accelerated upwards
         */
        void playerUp(double t);
    private:
        /**
         * Removes all items which left the environment on the left side and finds the rightmost item.
         * @tparam T the type of item, needs to be a child of GameItem
         * @param gameItems the list of items which should be modified
         * @return the x position of the rightmost item
         */
        template <typename T>
        auto removeOutOfScopeAndGetLastX(std::deque<std::shared_ptr<T>> &gameItems) -> double;

        /**
         * Removes all old obstacles and creates new ones if necessary
         */
        void updateObstacles();

        /**
         * Removes all old items and creates new ones if possible and necessary
         */
        void updateItems();

        std::deque<std::shared_ptr<model::Obstacle>> obstacles;
        std::deque<std::shared_ptr<model::Item>> items;
        std::optional<std::shared_ptr<model::Item>> activeItem;
        model::Player player;
        int points;
        double timeMultiplexer;
        double pointMultiplexer;
        bool invulnerable;
        Config config;
        std::mt19937 randomNumberGenerator;
    };
}

#endif
