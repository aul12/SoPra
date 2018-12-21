//
// Created by paul on 19.12.18.
//

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Vector.hpp"

/**
 * Implementation of a generic non rotated rectangle in 2d cartesian coordinates with y pointing downwards.
 * @tparam T type of each dimension of the supporting vector, this type needs to support addition, multiplication and needs to be orderable
 */
template <typename T>
class Rectangle {
public:
    Rectangle() : anchor(0,0), size(0,0){};

    /**
     * Create an vector with a given anchor and size.
     * @param anchor the position of the top left corner of the rectangle
     * @param size the size of the rectangle, both values need to be non-negative
     */
    Rectangle(Vector<2,T> anchor, Vector<2,T> size) : anchor(anchor), size(size) {
        assert(size[0] >= 0 && size[1] >= 0);
    };

    /**
     * Returns if a given point is in the rectangle (including the edges)
     * @param pt the point to check
     * @return true if the point is in the rectangle
     */
    auto contains(Vector<2,T> pt) const -> bool {
        return pt.get(0) >= anchor.get(0) && pt.get(0) <= anchor.get(0) + size.get(0) &&
               pt.get(1) >= anchor.get(1) && pt.get(1) <= anchor.get(1) + size.get(1);
    }

    /**
     * Checks if two rectangles have a at least one point in common
     * @param rectangle the second rectangle
     * @return true if they share a point
     */
    auto intersects(Rectangle<T> rectangle) const -> bool {
        return this->contains(rectangle.topLeft()) ||
               this->contains(rectangle.topRight()) ||
               this->contains(rectangle.bottomLeft()) ||
               this->contains(rectangle.bottomRight()) ||
               rectangle.contains(this->topLeft()) ||
               rectangle.contains(this->topRight()) ||
               rectangle.contains(this->bottomLeft()) ||
               rectangle.contains(this->bottomRight());
    }

    /**
     * Get the top left corner of the rect
     * @return a vector of type T with dimension 2 pointing to the top left corner
     */
    auto topLeft() const -> Vector<2,T> {
        return anchor;
    }

    /**
     * Get the top right corner of the rect
     * @return a vector of type T with dimension 2 pointing to the top right corner
     */
    auto topRight() const -> Vector<2,T> {
        return {anchor.get(0) + size.get(0), anchor.get(1)};
    }

    /**
     * Get the bottom left corner of the rect
     * @return a vector of type T with dimension 2 pointing to the bottom left corner
     */
    auto bottomLeft() const -> Vector<2,T> {
        return {anchor.get(0), anchor.get(1) + size.get(1)};
    }

    /**
     * Get the bottom right corner of the rect
     * @return a vector of type T with dimension 2 pointing to the bottom right corner
     */
    auto bottomRight() const -> Vector<2,T> {
        return anchor + size;
    }

    /**
     * Shift the rectangle by a given offset
     * @param v the offset
     * @return the shifted rectangle
     */
    auto operator+(Vector<2,T> v) -> Rectangle<T> {
        return Rectangle<T>{anchor+v, size};
    }

    /**
     * Compare two rectangles, they are equal if both size and anchor are equal
     * @param rectangle the second rectangle
     * @return true if both rectangles are equal
     */
    auto operator==(Rectangle<T> rectangle) const -> bool {
        return this->anchor == rectangle.anchor && this->size == rectangle.size;
    }
private:
    Vector<2,T> anchor, size;
};


#endif //TEST_RECTANGLE_HPP
