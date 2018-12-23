/**
 * @file DoublePoints.cpp
 * @author paul
 * @date 22.12.18
 * @brief Implementation of the DoublePoints class
 */

#include "DoublePoints.hpp"

namespace model {
    void DoublePoints::apply(controller::Environment &environment) {
        environment.pointMultiplexer = 2;
    }

    void DoublePoints::remove(controller::Environment &environment) {
        environment.pointMultiplexer = 1;
    }
}
