//
// Created by paul on 19.12.18.
//

#ifndef TEST_RECTANGLE_HPP
#define TEST_RECTANGLE_HPP

#include "Vector.h"

template <typename T>
class Rectangle {
public:
    Rectangle() : anchor(0,0), size(0,0){};
    Rectangle(Vector<2,T> anchor, Vector<2,T> size) : anchor(anchor), size(size){};

    /**
     * Returns wheter a given point is in the rectangle (including the edges)
     * @param pt the point to check
     * @return true if the point is in the rectangle
     */
    auto contains(Vector<2,T> pt) const -> bool {
        return pt.get(0) >= anchor.get(0) && pt.get(0) <= anchor.get(0) + size.get(0) &&
               pt.get(1) >= anchor.get(1) && pt.get(1) <= anchor.get(1) + size.get(1);
    }

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

    auto topLeft() const -> Vector<2,T> {
        return anchor;
    }

    auto topRight() const -> Vector<2,T> {
        return {anchor.get(0) + size.get(0), anchor.get(1)};
    }

    auto bottomLeft() const -> Vector<2,T> {
        return {anchor.get(0), anchor.get(1), size.get(1)};
    }

    auto bottomRight() const -> Vector<2,T> {
        return anchor + size;
    }

    auto operator+(Vector<2,T> v) -> Rectangle<T> {
        return Rectangle<T>{anchor+v, size};
    }
private:
    Vector<2,T> anchor, size;
};


#endif //TEST_RECTANGLE_HPP
