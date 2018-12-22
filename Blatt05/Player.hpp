/**
 * @file Player.hpp
 * @author paul
 * @date 21.12.18
 * @brief Declaration of the player class
 */

#ifndef TEST_PLAYER_HPP
#define TEST_PLAYER_HPP

#include "GameItem.hpp"

namespace model {
    /**
     * Implements the main player for "Flappy Wizard"
     */
    class Player : public GameItem {
    public:
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
    private:
        Vec speed;
    };
}

#endif //TEST_PLAYER_HPP
