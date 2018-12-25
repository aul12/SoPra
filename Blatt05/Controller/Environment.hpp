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
         * @param t the time the player should get accelerated upwards (must be positive)
         */
        void playerUp(double t);

        /**
         * Transform an point from global coordinates to reference frame on the screen
         * @param global the point in global coordinates
         * @return a point, such that (0,0) is in the top left corner of the screen
         */
        auto toLocal(model::Vec global) -> model::Vec;

        /**
         * Transform an point from local coordinates to global coordinates
         * @param local point in local coordinates
         * @return a point in global coordinates
         * @see toLocal
         */
        auto toGlobal(model::Vec local) -> model::Vec;

        /**
         * Returns the list of currently visible obstacles
         */
        auto getObstacles() const -> std::deque<std::shared_ptr<model::Obstacle>>;

        /**
         * Returns the list of currently visible items
         */
        auto getItems() const -> std::deque<std::shared_ptr<model::Item>>;

        /**
         * Return the player
         * @return the player in this env
         */
        auto getPlayer() const -> model::Player;

        /**
         * Returns the used config
         * @return the currently used config
         */
        auto getConfig() const -> controller::Config;

        /**
         * Returns the current score
         * @return the amounts of obstacles that have been passed
         */
        auto getPoints() const -> int;
    private:
        /**
         * Removes all items which left the environment on the left side
         * @tparam T the type of item, needs to be a child of GameItem
         * @param gameItems the list of items which should be modified
         */
        template <typename T>
        void removeOutOfScope(std::deque<std::shared_ptr<T>> &gameItems);

        /**
         * Find the rightmost item
         * @tparam T the type of item, needs to be a child of GameItem
         * @return the x position of the rightmost item
         */
        template <typename T>
        auto findLastItem(std::deque<std::shared_ptr<T>> &gameItems) -> double;

        /**
         * Removes all old obstacles and creates new ones if necessary
         */
        void updateObstacles();

        /**
         * Removes all old items and creates new ones if possible and necessary
         */
        void updateItems();

        /**
         * Checks if any point of the player is at the same x-position as any point of an obstacle
         * @return if the player is "in between" two obstacles
         */
        auto isAtObstacle() -> std::optional<std::shared_ptr<model::Obstacle>>;

        std::deque<std::shared_ptr<model::Obstacle>> obstacles;
        std::deque<std::shared_ptr<model::Item>> items;
        std::optional<std::shared_ptr<model::Item>> activeItem;
        std::optional<std::shared_ptr<model::Obstacle>> activeObstacle;
        model::Player player;
        int points;
        int pointMultiplexer;
        bool invulnerable;
        Config config;
        std::mt19937 randomNumberGenerator;
    };
}

#endif
