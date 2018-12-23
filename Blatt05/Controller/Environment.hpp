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
        Environment(std::string configFile);
        auto update(double deltaT) -> UpdateResult;
        void playerUp(double t);
    private:
        template <typename T>
        auto removeOutOfScopeAndGetLastX(std::deque<std::shared_ptr<T>> &gameItems) -> double;
        void updateObstacles();
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
