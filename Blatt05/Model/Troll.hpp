/**
 * @file Troll.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of the Troll class
 */

#ifndef TROLL_HPP
#define TROLL_HPP

#include "Item.hpp"

namespace model {
    class Troll : public Item {
    public:
        Troll(Vec pos, Vec size, double lifeTime) : Item(pos, size, lifeTime){}
        void apply(controller::Environment &environment) const;
        void remove(controller::Environment &environment) const;
    };
}

#endif
