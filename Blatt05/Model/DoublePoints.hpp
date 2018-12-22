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
    class DoublePoints : public Item {
    public:
        void apply(controller::Environment &environment) const;
        void remove(controller::Environment &environment) const;
    };
}

#endif
