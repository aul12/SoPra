/**
 * @file Item.hpp
 * @author paul
 * @date 22.12.18
 * @brief Declaration of the Item class
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include "GameItem.hpp"
#include "../Controller/Environment.hpp"

namespace model {
    /**
     * Implements an generic item
     */
    class Item : public GameItem {
    public:
        /**
         * Constructor
         * @param pos the position of the item
         * @param size the size of the item
         * @param lifeTime the active time of the item
         */
        Item(Vec pos, Vec size, double lifeTime) : GameItem(pos, size), time(lifeTime){}

        /**
         * Virtual function to apply the modification to the environment
         * @param environment the environment to modify
         */
        virtual void apply(controller::Environment &environment) const = 0;

        /**
         * Virtual function to remove all modifications from the environment
         * @param environment, the environment to demodify
         */
        virtual void remove(controller::Environment &environment) const = 0;

        /**
         * Returns the time the item is active, this value is constant if the item is not active
         * and gets smaller when the item is active.
         * @return the remaining time (in seconds)
         */
        auto getRemainingTime() const -> double {
            return time;
        }

        /**
         * Decreas the remaing time
         * @param deltaT the difference in seconds.
         */
        void decreaseRemainingTimeBy(double deltaT) {
            this->time -= deltaT;
        }
    protected:
        double time = 0;
    };
}

#endif
