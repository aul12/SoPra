/**
 * @file Invulnerable.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the Invulnerable class
 */

#include "Invulnerable.hpp"

void model::Invulnerable::apply(controller::Environment &environment) const {
    environment.player.scaleSize(0.5);
    environment.invulnerable = true;
}

void model::Invulnerable::remove(controller::Environment &environment) const {
    environment.player.resetScale();
    environment.invulnerable = false;
}
