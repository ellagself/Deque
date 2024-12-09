/**
 * @file deque.h
 * @author Mangos
 * @date 2024-12-04
 * @brief header and implemention file for deque
 * 
 * contains function declarations and implementations
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
private:
    T** blockmap;           // pointer to the block map
    size_t block_size;      // size of each block
    size_t block_capacity;  // number of blocks in the blockmap
    size_t front_index;     // index of the front block
    size_t back_index;      // index of the back block
    size_t deque_size;      // number of elements in the deque

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

// constructor
template <typename T>

/**
 * constructor for deque
 *
 * @param size_t initial_block_size 
 * @pre 
 * @post deque exists
 * 
 */
Deque<T>::Deque(size_t initial_block_size)
    : blockmap(nullptr), block_size(initial_block_size), block_capacity(4),
      front_index(2), back_index(1), deque_size(0) {
    blockmap = new T*[block_capacity]();
    cout << "Deque initialized with block_capacity: " << block_capacity << endl;
}

// destructor
template <typename T>

/**
 * destrutor for deque
 *
 * @pre deque is constructed
 * @post deque is destructed 
 * 
 */
Deque<T>::~Deque() {
    for (size_t i = 0; i < block_capacity; ++i) {
        if (blockmap[i]) {
            delete[] blockmap[i];
        }
    }
    delete[] blockmap;
}

// expand blockmap when capacity is exceeded
template <typename T>

/**
 * expand blockmap
 *
 * @pre blockmap exists
 * @return void 
 * @post blockmap is expanded for deque
 * 
 */
void Deque<T>::expand_blockmap() {
    size_t new_capacity = block_capacity * 2;
    T** new_blockmap = new T*[new_capacity]();

    size_t offset = (new_capacity - block_capacity) / 2;
    cout << "Expanding blockmap to new_capacity: " << new_capacity << endl;

    // move old blocks to new blockmap
    for (size_t i = 0; i < block_capacity; ++i) {
        new_blockmap[i + offset] = blockmap[i];
    }

    delete[] blockmap;
    blockmap = new_blockmap;

    // update the front and back indices properly
    front_index += offset;
    back_index += offset;
    block_capacity = new_capacity;

    cout << "Expanded blockmap. New front_index: " << front_index << ", back_index: " << back_index << endl;
}

// push to front
template <typename T>

/**
 * push front
 *
 * @param const T& value 
 * @pre deque exists 
 * @return void 
 * @post value is pushed to front
 * 
 */
void Deque<T>::push_front(const T& value) {
    cout << "Pushing to front: " << value << endl;
    if (deque_size == block_capacity * block_size) {
      expand_blockmap();
    }
    
    // front_index reaches the start, expand the blockmap
    if (front_index == 0) {
      front_index = block_capacity - 1;
    } else {
      --front_index;
    }

    // allocate new block if necessary 
    if (!blockmap[front_index]) {
        blockmap[front_index] = new T[block_size];
        cout << "Allocated block at front_index: " << front_index << endl;
    }

    size_t offset = (deque_size == 0) ? 0 : deque_size % block_size;
    blockmap[front_index][offset] = value;
    ++deque_size;

    // insert value at the front
    blockmap[front_index][deque_size % block_size] = value;
    cout << "Inserted value " << value << " at front_index: " << front_index << endl;

    // update front_index and wrap it around correctly
    front_index = (front_index - 1 + block_capacity) % block_capacity;
    ++deque_size;

    cout << "Deque size after push_front: " << deque_size << endl;
    cout << "front_index: " << front_index << ", back_index: " << back_index << endl;
}

// Push to back
template <typename T>

/**
 * push back
 *
 * @param const T& value 
 * @pre deque exists and is constructed
 * @return void 
 * @post value is pushed back
 * 
 */
void Deque<T>::push_back(const T& value) {
    cout << "Pushing to back: " << value << endl;

    // back_index reaches the end, expand the blockmap
    if (back_index == block_capacity - 1) {
        expand_blockmap();
    }

    // allocate new block if necessary 
    if (!blockmap[back_index]) {
        blockmap[back_index] = new T[block_size];
        cout << "Allocated block at back_index: " << back_index << endl;
    }

    // insert value at the back
    blockmap[back_index][deque_size % block_size] = value;
    cout << "Inserted value " << value << " at back_index: " << back_index << endl;

    // update back_index and wrap it around correctly
    back_index = (back_index + 1) % block_capacity;
    ++deque_size;

    cout << "Deque size after push_back: " << deque_size << endl;
    cout << "front_index: " << front_index << ", back_index: " << back_index << endl;
}

// pop from front
template <typename T>

/**
 * pop front
 *
 * @pre deque exists
 * @return void 
 * @post value is popped to front
 * 
 */
void Deque<T>::pop_front() {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }

    cout << "Popping from front" << endl;

    // move front_index and reduce deque_size
    front_index = (front_index + 1) % block_capacity;
    --deque_size;

    cout << "Deque size after pop_front: " << deque_size << endl;
    cout << "front_index: " << front_index << ", back_index: " << back_index << endl;
}

// pop from back
template <typename T>

/**
 * pop back 
 *
 * @pre deque exists
 * @return void 
 * @post value is popped to back
 * 
 */
void Deque<T>::pop_back() {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }

    cout << "Popping from back" << endl;

    // move back_index and reduce deque_size
    back_index = (back_index - 1 + block_capacity) % block_capacity;
    --deque_size;

    cout << "Deque size after pop_back: " << deque_size << endl;
    cout << "front_index: " << front_index << ", back_index: " << back_index << endl;
}

// return front element
template <typename T>

/**
 * return front element
 *
 * @pre element exists
 * @return T& 
 * @post element is returned
 * 
 */
T& Deque<T>::front() const {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }

    return blockmap[front_index][deque_size % block_size];
}

// return back element
template <typename T>

/**
 * returns back element
 *
 * @pre deque exists, is not empty
 * @return T& 
 * @post back element is returned
 * 
 */
T& Deque<T>::back() const {
    if (empty()) {
        throw out_of_range("Deque is empty");
    }

    return blockmap[back_index][deque_size % block_size];
}

// access element by index
template <typename T>

/**
 * operator 
 *
 * @param size_t index 
 * @pre deque exists
 * @return T& 
 * @post element is accessed by index
 * 
 */
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

// check if deque is empty
template <typename T>

/**
 * check if empty 
 *
 * @pre deque exists
 * @return bool 
 * @post deque is found empty or with contents
 * 
 */
bool Deque<T>::empty() const {
    return deque_size == 0;
}

// get the size of the deque
template <typename T>

/**
 * deque size
 *
 * @pre deque exists
 * @return size_t 
 * @post size of deque is returned
 * 
 */
size_t Deque<T>::size() const {
    return deque_size;
}

#endif
