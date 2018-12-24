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
    /**
     * This class implements the TurboMode Item
     *  @see Item
     */
    class TurboMode : public Item {
    public:
        TurboMode(Vec pos, Vec size, double lifeTime) : Item(pos, size, lifeTime){}
        void apply(controller::Environment &environment);
        void remove(controller::Environment &environment);

    private:
        double oldGravity;
        double oldUpAcceleration;
        double oldMaxObstacle;
    };
}

#endif
