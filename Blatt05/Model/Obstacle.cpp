/**
 * @file Obstacle.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of Obstacle class
 */

#include "Obstacle.hpp"

model::Obstacle::Obstacle(model::Vec pos, model::Vec size, model::ObstacleSide obstacleSide) :
 GameItem(pos, size), obstacleSide(obstacleSide), heightScale(1) {

}

void model::Obstacle::setHeightScale(double scale) {
    assert(scale > 0);
    double currentHeight = this->rect.getSize().get(1);
    double originalHeight = currentHeight / this->heightScale;
    double newHeight = originalHeight * scale;
    double deltaY = newHeight-currentHeight;

    this->rect.setSize(Vec{this->rect.getSize()[0], newHeight});
    if(obstacleSide == ObstacleSide::BOTTOM) {
        this->rect = this->rect + Vec{0, - deltaY};
    }

    this->heightScale = scale;
}

auto model::Obstacle::getHeightScale() const -> double {
    return this->heightScale;
}

void model::Obstacle::resetScale() {
    this->setHeightScale(1.0);
}

auto model::Obstacle::getObstacleSide() const -> model::ObstacleSide {
    return this->obstacleSide;
}

