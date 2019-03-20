#pragma once

#include <babocar-core/numeric.hpp>
#include <babocar-core/arrays.hpp>
#include <type_traits>
#include <initializer_list>

namespace bcr {

template <typename T, uint32_t capacity_>
class vec {
public:
    typedef T* iterator;
    typedef const T* const_iterator;

    T& operator[](uint32_t pos) {
        return *reinterpret_cast<T*>(&this->data_[pos]);
    }

    const T& operator[](uint32_t pos) const {
        return *reinterpret_cast<const T*>(&this->data_[pos]);
    }

    /* @brief Default constructor - Sets size to 0.
     **/
    vec() : size_(0) {}

    /* @brief Copy constructor - copies elements.
     * @param other The other vector.
     **/
    vec(const vec<T, capacity_>& other)
        : size_(other.size_) {
        bcr::copy(other.data_, this->data_, this->size_);
    }

    vec(const std::initializer_list<T>& values)
        : size_(0) {
        if (values.size() <= capacity_) {
            for (const T& elem : values) {
                this->append(elem);
            }
        }
    }

    /* @brief Copies data_ from the other vector.
     * @param other The other vector.
     * @returns This vec.
     **/
    vec<T, capacity_>& operator=(const vec<T, capacity_>& other) {
        bcr::copy(other.data_, this->data_, (this->size_ = other.size_));
        return *this;
    }

    /* @brief Appends elements to the end of the vector.
     * @param _data The elements to append.
     * @param _size Number of elements to append.
     * @returns Number of appended elements. Less than _size if vector capacity_ is reached.
     **/
    uint32_t append(const T *_data, uint32_t _size) {
        uint32_t num = bcr::min(_size, capacity_ - this->size_);
        bcr::copy(_data, this->end(), num);
        this->size_ += num;
        return num;
    }

    /* @brief Appends elements to the end of the vector.
     * @param vec The elements to append.
     * @returns Number of appended elements. Less than vec.size if vector capacity_ is reached.
     **/
    template <uint32_t capacity2>
    uint32_t append(const vec<T, capacity2>& vec) {
        return this->append(vec.data_, vec.size_);
    }

    /* @brief Appends one element to the end of the vector.
     * @param item The element to append.
     * @returns Number of appended elements. 1 if element has been appended successfully, 0 otherwise.
     **/
    uint32_t append(const T& item) {
        return this->append(&item, 1);
    }

    uint32_t insert(iterator pos, const T& item) {
        uint32_t num = this->size_ < capacity_ && pos - this->begin() <= size_ ? 1 : 0;
        if (num) {
            for (iterator it = this->end(); it != pos; --it) {
                std::swap(*it, *(it - 1));
            }
            *pos = item;
            this->size_++;
        }
        return num;
    }

    bool remove(iterator pos) {
        bool found = pos >= this->begin() && pos < this->end();
        if (found) {
            for(iterator it = pos; it < this->end() - 1; ++it) {
                std::swap(*it, *(it + 1));
            }
            this->size_--;
        }
        return found;
    }

    bool remove(const T& item) {
        bool found = false;
        for(uint32_t i = 0; i < this->size_; ++i) {
            if (*reinterpret_cast<T*>(&this->data_[i]) == item) {
                found = true;
            }
            if (found && i < this->size_ - 1) {  // shifts elements after removed item
                std::swap(*reinterpret_cast<T*>(&this->data_[i]), *reinterpret_cast<T*>(&this->data_[i + 1]));
            }
        }
        if (found) {
            this->size_--;
        }
        return found;
    }

    const_iterator find(const T& item) const {
        const_iterator it = this->begin();
        for (; it < this->end(); ++it) {
            if (*it == item) {
                break;
            }
        }
        return it;
    }

    iterator find(const T& item) {
        iterator it = this->begin();
        for (; it < this->end(); ++it) {
            if (*it == item) {
                break;
            }
        }
        return it;
    }

    /* @brief Clears vector.
     **/
    void clear() {
        for(T& elem : *this) {
            elem.~T();
        }
        this->size_ = 0;
    }

    iterator begin() {
        return reinterpret_cast<T*>(this->data_);
    }

    const_iterator begin() const {
        return reinterpret_cast<T*>(this->data_);
    }

    iterator end() {
        return reinterpret_cast<T*>(&this->data_[this->size_]);
    }

    const_iterator end() const {
        return reinterpret_cast<T*>(&this->data_[this->size_]);
    }

    uint32_t size() const { return this->size_; }

    uint32_t capacity() const { return capacity_; }

    T* data() { return reinterpret_cast<T*>(&this->data_); }

    const T* data() const { return reinterpret_cast<const T*>(&this->data_); }

private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data_[capacity_];
    uint32_t size_;
};
} // namespace bcr

