#pragma once

#include <babocar-core/numeric.hpp>
#include <babocar-core/arrays.hpp>
#include <type_traits>
#include <initializer_list>
#include <utility>

namespace bcr {

template <typename T>
class circular_iterator {
public:
    circular_iterator(T *data_, uint32_t capacity_, uint32_t idx_)
        : data_(data_)
        , capacity_(capacity_)
        , idx_(idx_) {}

    circular_iterator& operator++() {
        this->idx_++;
        return *this;
    }

    circular_iterator operator++(int32_t) {
        circular_iterator res = *this;
        this->idx_++;
        return res;
    }

    circular_iterator& operator--() {
        this->idx_--;
        return *this;
    }

    circular_iterator operator--(int32_t) {
        circular_iterator res = *this;
        this->idx_--;
        return res;
    }

    T* operator->() {
        return &this->data_[this->idx_ % this->capacity_];
    }

    T& operator*() {
        return this->data_[this->idx_ % this->capacity_];
    }

    bool operator==(const circular_iterator& other) const {
        return this->data_[this->idx_ % this->capacity_] == other.data_[other.idx_ % other.capacity_];
    }

    bool operator!=(const circular_iterator& other) const {
        return this->data_[this->idx_ % this->capacity_] != other.data_[other.idx_ % other.capacity_];
    }
private:

    T *data_;
    const uint32_t capacity_;
    uint32_t idx_;
};

template <typename T, uint32_t capacity_>
class ring_buffer {
public:
    typedef circular_iterator<T> iterator;
    typedef circular_iterator<const T> const_iterator;

    T& operator[](uint32_t pos) {
        return *reinterpret_cast<T*>(&this->data_[this->get_idx(pos)]);
    }

    const T& operator[](uint32_t pos) const {
        return *reinterpret_cast<const T*>(&this->data_[this->get_idx(pos)]);
    }

    /* @brief Default constructor - Sets size to 0.
     **/
    ring_buffer()
        : begin_(0)
        , size_(0) {}

    /* @brief Copy constructor - copies elements.
     * @param other The other buffer.
     **/
    ring_buffer(const ring_buffer<T, capacity_>& other)
        : begin_(other.begin_)
        , size_(other.size_) {
        bcr::copy(other.data_, this->data_, this->size_);
    }

    ring_buffer(const std::initializer_list<T>& values)
        : begin_(0)
        , size_(0) {
        if (values.size() <= capacity_) {
            for (const T& elem : values) {
                this->append(elem);
            }
        }
    }

    /* @brief Copies data from the other buffer.
     * @param other The other buffer.
     * @returns This buffer.
     **/
    ring_buffer<T, capacity_>& operator=(const ring_buffer<T, capacity_>& other) {
        this->begin_ = other.begin_;
        this->size_ = other.size_;
        bcr::copy(other.data_, this->data_, this->size_);
        return *this;
    }

    /* @brief Appends elements to the end of the buffer.
     * @param values The elements to append.
     * @param _size Number of elements to append.
     **/
    void append(const T *values, uint32_t _size) {
        for (uint32_t i = 0; i < _size; ++i) {
            this->append(values[i]);
        }
   }

    /* @brief Appends elements to the end of the buffer.
     * @param ring_buffer The elements to append.
     **/
    template <uint32_t capacity2>
    void append(const ring_buffer<T, capacity2>& values) {
        for (const T& item : values) {
            this->append(item);
        }
    }

    /* @brief Appends one element to the end of the buffer.
     * @param item The element to append.
     **/
    void append(const T& item) {
        if (this->full()) {
            (*this)[0] = item;
            this->begin_ = this->get_idx(1);
        } else {
            (*this)[this->size_++] = item;
        }
    }

    template <typename... Args>
    void emplace_back(Args... args) {
        if (this->full()) {
            (*this)[0] = T(std::forward<Args>(args)...);
            this->begin_ = this->get_idx(1);
        } else {
            (*this)[this->size_++] = T(std::forward<Args>(args)...);
        }
    }

    /* @brief Clears buffer.
     **/
    void clear() {
        for(T& elem : *this) {
            elem.~T();
        }
        this->begin_ = 0;
        this->size_ = 0;
    }

    iterator begin() {
        return iterator(reinterpret_cast<T*>(this->data_), capacity_, this->begin_);
    }

    const_iterator begin() const {
        return const_iterator(reinterpret_cast<const T*>(this->data_), capacity_, this->begin_);
    }

    iterator end() {
        return iterator(reinterpret_cast<T*>(this->data_), capacity_, this->size_);
    }

    const_iterator end() const {
        return const_iterator(reinterpret_cast<const T*>(this->data_), capacity_, this->size_);
    }

    uint32_t size() const { return this->size_; }

    uint32_t capacity() const { return capacity_; }

    bool empty() const { return !this->size_; }

    bool full() const { return this->size_ == capacity_; }

private:
    uint32_t get_idx(uint32_t pos) const {
        return (this->begin_ + pos) % capacity_;
    }

    typename std::aligned_storage<sizeof(T), alignof(T)>::type data_[capacity_];
    uint32_t begin_;
    uint32_t size_;
};
} // namespace bcr

