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
#include "../Model/Obstacle.hpp"
#include "../Model/Item.hpp"
#include "../Model/Player.hpp"
#include "Config.hpp"

namespace controller {
    class Environment {
    friend class model::Item;
    public:
        Environment(std::string configFile);
        void update(double deltaT);
        void playerUp(double t);
    private:
        std::deque<model::Obstacle> obstacles;
        std::deque<model::Item> items;
        std::optional<model::Item> activeItem;
        model::Player player;
        int points;
        double timeMultiplexer;
        const Config config;
    };
}

#endif
