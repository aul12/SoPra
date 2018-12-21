//
// Created by paul on 21.12.18.
//

#ifndef GAMEITEM_HPP
#define GAMEITEM_HPP

#include "Util/Rectangle.hpp"

typedef Vector<2, double> Vec;
typedef Rectangle<double> Rect;

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
    auto getDimension()  const -> Vec;

    /**
     * Return the bounding rect of the game item
     * @return a rectangle containing the game item
     */
    auto getBoundingRect() const -> Rect;

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
    Rect rect;
    Vec speed;
};


#endif //TEST_GAMEITEM_HPP
