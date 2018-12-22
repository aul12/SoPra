/**
 * @file Obstacle.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of the Obstacle class
 */

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "GameItem.hpp"

namespace model {
    /**
     * Discrimination between top and bottom tube
     */
    enum class ObstacleSide {
        TOP, BOTTOM
    };

    /**
     * Implements an obstacle (Tube)
     */
    class Obstacle : public GameItem {
    public:
        /**
         * Creates an obstacle with a given position and size
         * @param pos the center of the obstacle
         * @param size the size of the obstacle
         * @param obstacleSide differentiate between tubes at the top and at the bottom
         */
        Obstacle(Vec pos, Vec size, ObstacleSide obstacleSide);

        /**
         * Set the scale of the height of the tube
         * @param scale an positive scale value
         */
        void setHeightScale(double scale);

        /**
         * Get the height scale
         * @return a positive value containing the height scale
         */
        auto getHeightScale() const -> double;

        /**
         * Resets the height scale to 1
         */
        void resetScale();

        /**
         * Return if the obstacle is at the top or at the bottom
         * @return
         */
        auto getObstacleSide() const -> ObstacleSide;
    private:
        const ObstacleSide obstacleSide;
        double heightScale;
    };
}


#endif
