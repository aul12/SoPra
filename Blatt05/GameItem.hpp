//
// Created by paul on 21.12.18.
//

#ifndef GAMEITEM_HPP
#define GAMEITEM_HPP

#include "Util/Rectangle.hpp"

namespace model {
    typedef util::Vector<2, double> Vec; ///< Vector as used in the model
    typedef util::Rectangle<double> Rect; ///< Rectangle as used in the model

    /**
     * A generic game item
     */
    class GameItem {
    public:
        /**
         * Create an game item with a given position and size
         * @param pos the position of the item
         * @param size the size of the item
         */
        GameItem(Vec pos, Vec size);

        /**
         * Get the current position of the game item
         * @return the center of the game item
         */
        auto getPosition() const -> Vec;

        /**
         * Get the dimensions of the game item
         * @return the size of the game item in each dimension
         */
        auto getDimension() const -> Vec;

        /**
         * Return the bounding rect of the game item
         * @return a rectangle containing the game item
         */
        auto getBoundingRect() const -> Rect;

    protected:
        Rect rect;
    };
}

#endif //TEST_GAMEITEM_HPP
