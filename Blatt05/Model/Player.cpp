/**
 * @file Player.cpp
 * @author paul
 * @date 21.12.18
 * @brief Implementation of player class
 */
#include "Player.hpp"

namespace model {
    Player::Player(Vec pos, Vec size, Vec speed) : GameItem(pos, size), speed(speed) {}

    void Player::move(double deltaT) {
        this->rect = this->rect + this->speed * deltaT;
    }

    void Player::accelerate(Vec a, double deltaT) {
        this->speed = this->speed + a * deltaT;
    }
}