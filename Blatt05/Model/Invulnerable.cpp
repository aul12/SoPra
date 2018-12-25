/**
 * @file Invulnerable.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the Invulnerable class
 */

#include "Invulnerable.hpp"

void model::Invulnerable::apply(controller::Environment &environment) {
    environment.player.scaleSize(0.5);
    environment.invulnerable = true;
    environment.invulnerableObstacle.reset();
}

void model::Invulnerable::remove(controller::Environment &environment) {
    environment.player.resetScale();
    environment.invulnerable = false;
    environment.invulnerableObstacle.reset();
}
