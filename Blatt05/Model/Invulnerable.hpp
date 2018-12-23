/**
 * @file Invulnerable.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of the Invulnerable class
 */

#ifndef INVULNERABLE_HPP
#define INVULNERABLE_HPP

#include "Item.hpp"

namespace model {
    class Invulnerable : public Item {
    public:
        Invulnerable(Vec pos, Vec size, double lifeTime) : Item(pos, size, lifeTime){}
        void apply(controller::Environment &environment) const;
        void remove(controller::Environment &environment) const;
    };
}

#endif
