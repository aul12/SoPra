#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <array>
#include <cassert>

template<std::size_t D, typename T>
class Vector {
    public:
        Vector(Vector &v) {
            for (auto c = 0; c < D; c++) {
                this->data[c] = v[c];
            }
        }

        Vector(std::initializer_list<T> l) : data(l) {};

        auto operator[](std::size_t s) -> T {
            assert(s < D);
            return this->data[s];
        }

        auto operator+(Vector<D,T> lhs, Vector<D,T> rhs) -> Vector<D,T> {
            Vector<D,T> result;
            for (auto c = 0; c < D; c++) {
                result[c] = lhs[c] + rhs[c];
            }
            return result;
        }

        auto operator-(Vector<D,T> lhs, Vector<D,T> rhs) -> Vector<D,T> {
            return lhs + (-1 * rhs);
        }

        auto operator*(Vector<D,T> lhs, T rhs) -> Vector<D,T> {
            Vector<D,T> result;
            for (auto c = 0; c < D; c++) {
                result[c] = lhs[c] * rhs;
            }
            return result;
        }

        auto operator*(Vector<D,T> lhs, Vector<D,T> rhs) -> T {
            T result{0};
            for (auto c = 0; c < D; c++) {
                result += rhs[c] * lhs[c];
            }
            return result;
        }

    private:
        std::array<T, D> data
}

#endif  
