/**
 * @file Player.hpp
 * @author paul
 * @date 21.12.18
 * @brief Declaration of the player class
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameItem.hpp"

namespace model {
    /**
     * Implements the main player for "Flappy Wizard"
     */
    class Player : public GameItem {
    public:
        Player(Vec pos = Vec{0,0}, Vec size = Vec{0,0}, Vec speed = Vec{0,0});
        /**
         * Move the item by using the internal speed
         * @param deltaT the difference between now and the last call to move (in seconds)
         */
        void move(double deltaT = 1.0);

        /**
         * Accelerate the item with a given acceleration
         * @param a the acceleration
         * @param deltaT length of the application of the acceleration
         */
        void accelerate(Vec a, double deltaT = 1.0);

        /**
         * Get the speed of the player
         * @return a Vec containing the speed in each dimension
         */
        auto getSpeed() const -> Vec;

        /**
         * Set the speed of the player, should only be used when physics get ignored (eg. when using certain items)
         * @param speed the new speed
         */
        void setSpeed(Vec speed);

        /**
         * Set the scale of the player
         * @param scale a positive number representing the scale
         */
        void scaleSize(double scale);

        /**
         * Set the player back to it's original size
         */
        void resetScale();
    private:
        Vec speed;
        double scale;
    };
}

#endif
