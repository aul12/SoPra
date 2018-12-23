/**
 * @file DoublePoints.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of the DoublePoints class
 */

#ifndef DOUBLEPOINTS_HPP
#define DOUBLEPOINTS_HPP

#include "Item.hpp"

namespace model {
    /**
     * This class implements the DoublePoints Item
     *  @see Item
     */
    class DoublePoints : public Item {
    public:
        DoublePoints(Vec pos, Vec size, double lifeTime) : Item(pos, size, lifeTime){}
        void apply(controller::Environment &environment);
        void remove(controller::Environment &environment);
    };
}

#endif
