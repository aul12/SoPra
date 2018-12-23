/**
 * @file Player.cpp
 * @author paul
 * @date 21.12.18
 * @brief Implementation of player class
 */
#include "Player.hpp"

namespace model {
    Player::Player(Vec pos, Vec size, Vec speed) : GameItem(pos, size), speed(speed), scale(1) {}

    void Player::move(double deltaT) {
        this->rect = this->rect + this->speed * deltaT;
    }

    void Player::accelerate(Vec a, double deltaT) {
        this->speed = this->speed + a * deltaT;
    }

    auto Player::getSpeed() const -> Vec {
        return speed;
    }

    void Player::scaleSize(double scale) {
        assert(scale > 0);
        Vec currentSize = this->rect.getSize();
        Vec normalSize = currentSize * (1/this->scale);
        Vec newSize = normalSize * scale;
        Vec deltaSize = newSize - currentSize;

        this->rect = this->rect + (deltaSize * (-0.5));
        this->rect.setSize(newSize);

        this->scale = scale;
    }

    void Player::resetScale() {
        this->scaleSize(1);
    }

    void Player::setSpeed(Vec speed) {
        this->speed = speed;
    }
}
