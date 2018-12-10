#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <array>

template<std::size_t D, typename T>
class Vector {
    public:
        Vector(Vector &v);
        Vector(std::initializer_list<T> l);
        auto operator[](std::size_t s) -> T;
        auto operator+(Vector<D,T> lhs, Vector<D,T> rhs) -> Vector<D,T>;
        auto operator-(Vector<D,T> lhs, Vector<D,T> rhs) -> Vector<D,T>;
        auto operator*(Vector<D,T> lhs, T rhs) -> Vector<D,T> ;
        auto operator*(Vector<D,T> lhs, Vector<D,T> rhs);
    private:
        std::array<T, D> data;
}

#endif  
