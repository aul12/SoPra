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
    /**
     * This class implements the Invulnerable Item
     *  @see Item
     */
    class Invulnerable : public Item {
    public:
        Invulnerable(Vec pos, Vec size, double lifeTime) : Item(pos, size, lifeTime){}
        void apply(controller::Environment &environment);
        void remove(controller::Environment &environment);
    };
}

#endif
