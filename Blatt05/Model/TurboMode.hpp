/**
 * @file TurboMode.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of the TurboMode class
 */

#ifndef TURBOMODE_HPP
#define TURBOMODE_HPP

#include "Item.hpp"

namespace model {
    class TurboMode : public Item {
    public:
        TurboMode(Vec pos, Vec size, double lifeTime) : Item(pos, size, lifeTime){}
        void apply(controller::Environment &environment) const;
        void remove(controller::Environment &environment) const;
    };
}

#endif
