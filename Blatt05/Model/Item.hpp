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
         * Virtual function to apply the modification to the environment
         * @param environment the environment to modify
         */
        virtual void apply(controller::Environment &environment) const = 0;

        /**
         * Virtual function to remove all modifications from the environment
         * @param environment, the environment to demodify
         */
         virtual void remove(controller::Environment &environment) const = 0;
    protected:
        const double time = 0;
    };
}

#endif
