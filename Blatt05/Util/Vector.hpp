#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <array>
#include <cassert>
#include <valarray>

namespace util {
    /**
     * Implementation of a generic vector.
     * @tparam D Dimension (Elements) of the vector
     * @tparam T Type of the Vector, for this type addition and multiplication should be defined.
     */
    template<int D, typename T>
    class Vector {
    public:

        /**
         * The default constructor, this doesn't set initial values.
         */
        Vector() = default;

        /**
         * Copy constructor, creates a deep copy
         * @param v the vector which should be copied
         */
        Vector(const Vector<D, T> &v) {
            for (auto c = 0; c < D; c++) {
                this->data.at(c) = v.get(c);
            }
        }

        /**
         * Create a vector of type T from a vector of type T2 with the same dimensions
         * @tparam T2 type of the argument vector
         * @param vector the vector of type T2 which should get converted
         */
        template<typename T2>
        explicit Vector(const Vector<D, T2> v) {
            static_assert(std::is_convertible<T2, T>::value);
            for (auto c = 0; c < D; c++) {
                this->data.at(c) = static_cast<T>(v.get(c));
            }
        }

        /**
         * Create a Vector from an initializer list, the length of the list has to be equal to the dimension
         * @param l an initializer list of type T
         */
        Vector(std::initializer_list<T> l) {
            assert(l.size() == D);
            int i = 0;
            for (const auto &it : l) {
                this->data.at(i++) = it;
            }
        };

        /**
         * Get a copy of the item at position s.
         * @param s the index, this value needs to be equal or larger 0 but smaller D
         * @return a copy of the item at position s.
         */
        auto get(int s) const -> T {
            assert(s >= 0 && s < D);
            return this->data.at(s);
        }

        /**
         * Set a item at a position, this method copies the item and replaces the old item. This method simply
         * overwrites the old item, there is no guarantee that the destructor is getting called.
         * @param s the index at which the item is placed. s needs to be larger or equal to 0 but smaller than D.
         * @param v the item which gets copied into the vector
         */
        void set(int s, T v) {
            assert(s >= 0 && s < D);
            this->data.at(s) = v;
        }

        /**
         * Get the s-th element
         * @param s the index of the element, this value needs to be larger or equal to 0 but smaller than D
         * @return a reference to the s-th element
         */
        auto operator[](int s) -> T & {
            assert(s >= 0 && s < D);
            return this->data.at(s);
        }

        /**
         * Element wise addition of two vectors of the same dimension and size
         * @param rhs the vector which should get added
         * @return the sum of both vectors.
         */
        auto operator+(Vector<D, T> rhs) const -> Vector<D, T> {
            Vector<D, T> result;
            for (auto c = 0; c < D; c++) {
                result.set(c, this->data.at(c) + rhs.get(c));
            }
            return result;
        }

        /**
         * Element wise substraction of two vectors of the same dimension and size
         * @param rhs the vector which should get substracted
         * @return the difference of both vectors.
         */
        auto operator-(Vector<D, T> rhs) const -> Vector<D, T> {
            return *this + (rhs * (-1));
        }

        /**
         * Scale each element of the vector.
         * @param rhs the value with which to scale the vector
         * @return the scaled vector
         */
        auto operator*(T rhs) const -> Vector<D, T> {
            Vector<D, T> result;
            for (auto c = 0; c < D; c++) {
                result.set(c, this->data.at(c) * rhs);
            }
            return result;
        }

        /**
         * Calculate the dot (inner) product of two vectors
         * @param rhs the second vector
         * @return a scalar value T
         */
        auto operator*(Vector<D, T> rhs) const -> T {
            T result{0};
            for (auto c = 0; c < D; c++) {
                result += rhs.get(c) * this->data.at(c);
            }
            return result;
        }

        /**
         * Compare two vectors element-wise. The comparison is done on basis of a strict equal of each element,
         * be careful regarding floating point numbers.
         * @param lhs the second vector
         * @return true if all elements are equal, else false
         */
        auto operator==(const Vector<D, T> &lhs) const -> bool {
            for (auto c = 0; c < D; c++) {
                if (lhs.get(c) != this->data.at(c)) {
                    return false;
                }
            }
            return true;
        }

        /**
         * Calculate the L2 (length) of the vector
         * @return the length of the vector, the type is deduced by the compiler depending on T
         */
        auto norm() const {
            return std::sqrt(this->operator*(*this));
        }

    private:
        std::array<T, D> data;
    };
}

#endif  
