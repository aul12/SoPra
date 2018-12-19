#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <array>
#include <cassert>

template<int D, typename T>
class Vector {
    public:
        Vector() = default;

        Vector(Vector &v) {
            for (auto c = 0; c < D; c++) {
                this->data[c] = v[c];
            }
        }

        Vector(std::initializer_list<T> l) {
            assert(l.size() == D);
            int i = 0;
            for (const auto & it : l) {
                this->data[i++] = it;
            }
        };

        auto get(int s) const -> T {
            assert(s >= 0 && s < D);
            return this->data[s];
        }

        void set(int s, T v) {
            assert(s >= 0 && s < D);
            this->data[s] = v;
        }

        auto operator[](int s) -> T& {
            assert(s >= 0 && s < D);
            return this->data[s];
        }

        auto operator+(Vector<D,T> rhs) const -> Vector<D,T> {
            Vector<D,T> result;
            for (auto c = 0; c < D; c++) {
                result.set(c, this->data[c] + rhs.get(c));
            }
            return result;
        }

        auto operator-(Vector<D,T> rhs) -> Vector<D,T> {
            return *this + (rhs * (-1));
        }

        auto operator*(T rhs) -> Vector<D,T> {
            Vector<D,T> result;
            for (auto c = 0; c < D; c++) {
                result.set(c, this->data[c] * rhs);
            }
            return result;
        }

        auto operator*(Vector<D,T> rhs) const -> T {
            T result{0};
            for (auto c = 0; c < D; c++) {
                result += rhs.get(c) * this->data[c];
            }
            return result;
        }

        auto operator==(const Vector<D,T> &lhs) const -> bool {
            for(auto c = 0; c < D; c++) {
                if(lhs.get(c) != this->data[c]) {
                    return false;
                }
            }
            return true;
        }

    private:
        std::array<T, D> data;
};

#endif  
