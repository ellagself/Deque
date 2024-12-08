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
    cout << "Deque initialized with block_capacity: " << block_capacity << endl;
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
    cout << "Expanding blockmap to new_capacity: " << new_capacity << endl;

    // Move old blocks to new blockmap
    for (size_t i = 0; i < block_capacity; ++i) {
        new_blockmap[i + offset] = blockmap[i];
    }

    delete[] blockmap;
    blockmap = new_blockmap;

    // Update the front and back indices properly
    front_index += offset;
    back_index += offset;
    block_capacity = new_capacity;

    cout << "Expanded blockmap. New front_index: " << front_index << ", back_index: " << back_index << endl;
}

// Push to front
template <typename T>
void Deque<T>::push_front(const T& value) {
    cout << "Pushing to front: " << value << endl;

    // If front_index reaches the start, expand the blockmap
    if (front_index == 0) {
        expand_blockmap();
    }

    // Allocate new block if necessary for the front
    if (!blockmap[front_index]) {
        blockmap[front_index] = new T[block_size];
        cout << "Allocated block at front_index: " << front_index << endl;
    }

    // Insert value at the front
    blockmap[front_index][deque_size % block_size] = value;
    cout << "Inserted value " << value << " at front_index: " << front_index << endl;

    // Update front_index and wrap it around correctly
    front_index = (front_index - 1 + block_capacity) % block_capacity;
    ++deque_size;

    cout << "Deque size after push_front: " << deque_size << endl;
    cout << "front_index: " << front_index << ", back_index: " << back_index << endl;
}

// Push to back
template <typename T>
void Deque<T>::push_back(const T& value) {
    cout << "Pushing to back: " << value << endl;

    // If back_index reaches the end, expand the blockmap
    if (back_index == block_capacity - 1) {
        expand_blockmap();
    }

    // Allocate new block if necessary for the back
    if (!blockmap[back_index]) {
        blockmap[back_index] = new T[block_size];
        cout << "Allocated block at back_index: " << back_index << endl;
    }

    // Insert value at the back
    blockmap[back_index][deque_size % block_size] = value;
    cout << "Inserted value " << value << " at back_index: " << back_index << endl;

    // Update back_index and wrap it around correctly
    back_index = (back_index + 1) % block_capacity;
    ++deque_size;

    cout << "Deque size after push_back: " << deque_size << endl;
    cout << "front_index: " << front_index << ", back_index: " << back_index << endl;
}

// Pop from front
template <typename T>
void Deque<T>::pop_front() {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }

    cout << "Popping from front" << endl;

    // Move front_index and reduce deque_size
    front_index = (front_index + 1) % block_capacity;
    --deque_size;

    cout << "Deque size after pop_front: " << deque_size << endl;
    cout << "front_index: " << front_index << ", back_index: " << back_index << endl;
}

// Pop from back
template <typename T>
void Deque<T>::pop_back() {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }

    cout << "Popping from back" << endl;

    // Move back_index and reduce deque_size
    back_index = (back_index - 1 + block_capacity) % block_capacity;
    --deque_size;

    cout << "Deque size after pop_back: " << deque_size << endl;
    cout << "front_index: " << front_index << ", back_index: " << back_index << endl;
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

    size_t absolute_index = (front_index + 1 + index) % block_capacity;
    size_t block = absolute_index / block_size;
    size_t offset = absolute_index % block_size;

    cout << "Accessing index " << index << ", block: " << block << ", offset: " << offset << endl;

    if (!blockmap[block]) {
        throw out_of_range("Block is not allocated.");
    }

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
