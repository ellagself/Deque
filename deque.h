#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
private:
    T** blockmap;           // Pointer to the block map
    size_t block_size;      // Size of each block
    size_t block_capacity;  // Number of blocks in the blockmap
    size_t front_index;     // Index of the front block
    size_t back_index;      // Index of the back block
    size_t deque_size;      // Number of elements in the deque

    void expand_blockmap();

public:
    Deque(size_t initial_block_size = 4);
    ~Deque();

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();

    T& front() const;
    T& back() const;
    T& operator[](size_t index) const;

    bool empty() const;
    size_t size() const;
};

// Constructor
template <typename T>
Deque<T>::Deque(size_t initial_block_size)
    : blockmap(nullptr), block_size(initial_block_size), block_capacity(4),
      front_index(2), back_index(1), deque_size(0) {
    blockmap = new T*[block_capacity]();
}

// Destructor
template <typename T>
Deque<T>::~Deque() {
    for (size_t i = 0; i < block_capacity; ++i) {
        if (blockmap[i]) {
            delete[] blockmap[i];
        }
    }
    delete[] blockmap;
}

// Expand blockmap when capacity is exceeded
template <typename T>
void Deque<T>::expand_blockmap() {
    size_t new_capacity = block_capacity * 2;
    T** new_blockmap = new T*[new_capacity]();

    size_t offset = (new_capacity - block_capacity) / 2;

    for (size_t i = 0; i < block_capacity; ++i) {
        new_blockmap[i + offset] = blockmap[i];
    }

    delete[] blockmap;
    blockmap = new_blockmap;

    front_index += offset;
    back_index += offset;
    block_capacity = new_capacity;
}

// Push to front
template <typename T>
void Deque<T>::push_front(const T& value) {
    if (front_index == 0) {
        expand_blockmap();
    }
    if (!blockmap[front_index]) {
        blockmap[front_index] = new T[block_size];
    }
    blockmap[front_index][block_size - (deque_size % block_size) - 1] = value;
    --front_index;
    ++deque_size;
}

// Push to back
template <typename T>
void Deque<T>::push_back(const T& value) {
    if (back_index == block_capacity - 1) {
        expand_blockmap();
    }
    if (!blockmap[back_index]) {
        blockmap[back_index] = new T[block_size];
    }
    blockmap[back_index][deque_size % block_size] = value;
    ++back_index;
    ++deque_size;
}

// Pop from front
template <typename T>
void Deque<T>::pop_front() {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }
    ++front_index;
    --deque_size;
}

// Pop from back
template <typename T>
void Deque<T>::pop_back() {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }
    --back_index;
    --deque_size;
}

// Return front element
template <typename T>
T& Deque<T>::front() const {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }
    return blockmap[front_index][deque_size % block_size];
}

// Return back element
template <typename T>
T& Deque<T>::back() const {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }
    return blockmap[back_index][deque_size % block_size];
}

// Access element by index
template <typename T>
T& Deque<T>::operator[](size_t index) const {
    if (index >= deque_size) {
        throw out_of_range("Index out of range");
    }
    size_t absolute_index = front_index + index;
    size_t block = absolute_index / block_size;
    size_t offset = absolute_index % block_size;
    return blockmap[block][offset];
}

// Check if deque is empty
template <typename T>
bool Deque<T>::empty() const {
    return deque_size == 0;
}

// Get the size of the deque
template <typename T>
size_t Deque<T>::size() const {
    return deque_size;
}

#endif
