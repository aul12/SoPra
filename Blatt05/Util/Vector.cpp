#include "Vector.h"
#include <cassert>

Vector::Vector(Vector &v) {
    for (auto c = 0; c < D; c++) {
        this->data[c] = v[c];
    }
}

Vector::Vector(std::initializer_list<T> l) : data(l) {}

auto Vector::operator[](std::size_t s) -> T {
    assert(s < D);
    return this->data[s];
}

auto Vector::operator+(Vector<D,T> lhs, Vector<D,T> rhs) -> Vector<D,T> {
    Vector<D,T> result;
    for (auto c = 0; c < D; c++) {
        result[c] = lhs[c] + rhs[c];
    }
    return result;
}

auto Vector::operator-(Vector<D,T> lhs, Vector<D,T> rhs) -> Vector<D,T> {
    return lhs + (-1 * rhs);
}

auto Vector::operator*(Vector<D,T> lhs, T rhs) -> Vector<D,T>  {
    Vector<D,T> result;
    for (auto c = 0; c < D; c++) {
        result[c] = lhs[c] * rhs;
    }
    return result;
}

auto Vector::operator*(Vector<D,T> lhs, Vector<D,T> rhs) {
    T result{0};
    for (auto c = 0; c < D; c++) {
        result += rhs[c] * lhs[c];
    }
    return result;
}
