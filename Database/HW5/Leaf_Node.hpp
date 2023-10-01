#pragma once
#include "Declaration.hpp"

/***********************************************************************************
Template functions, including member functions, must be written entirely in the
header files. This means that if you have a template class, its implementation
must be entirely in a header file. This is because the compiler needs to have access
to the entire template definition (not just the signature) in order to generate code
for each instantiation of the template.
Ref: https://vorbrodt.blog/2021/06/23/templates-linking-and-everything-in-between/
***********************************************************************************/

namespace otis {

/***********************************/
/* Single Leaf Node Data Structure */
/***********************************/
template <class T>
class Leaf {
   private:
    // The capacity of the leaf node. The leaf can contain at most (2 * order) data.
    const std::size_t capacity;

    // The actual data store at here. The data type is T.
    std::vector<T> data;

    // The pointer of the parent internal node. It is used for reverse traversing.
    Index<T> *parent;

    // The pointer of the siblings.
    Leaf<T> *prev, *next;

   public:
    // Friend Class Declaration
    friend class B_Plus_Tree<T>;
    friend class Index<T>;

    // Default Constructor
    Leaf();

    // Constructor to set the capacity
    Leaf(std::size_t o);

    // Check if the leaf node is overflow or not. return true if it is overflow.
    bool is_overflow();

    // Check if the leaf node is full or not. return true if it is full.
    bool is_full();

    // Check if the leaf node is underflow or not. return true if it is underflow.
    // Underflow means the amount of data is less than order (half of the capacity).
    bool is_underflow();

    // Check if the leaf node is empty or not. return true if it is empty.
    bool is_empty();

    // Check if the leaf node contains data. Return true and the corresponding index in this leaf node if contains.
    FindDataResult find_data(T value);

    // Show the data in the leaf node.
    void show_data();
};

// Default Constructor
template <class T>
Leaf<T>::Leaf() : capacity(DEFAULT_ORDER << 1), parent(nullptr), prev(nullptr), next(nullptr) {}

// Constructor to set the capacity
template <class T>
Leaf<T>::Leaf(std::size_t c) : capacity(c), parent(nullptr), prev(nullptr), next(nullptr) {}

// Check if the leaf node is full or not. return true if it is full.
template <class T>
bool Leaf<T>::is_overflow() {
    return data.size() > capacity ? true : false;
}

// Check if the leaf node is full or not. return true if it is full.
template <class T>
bool Leaf<T>::is_full() {
    return data.size() >= capacity ? true : false;
}

// Check if the leaf node is underflow or not. return true if it is underflow.
// Underflow means the amount of data is less than order (half of the capacity).
template <class T>
bool Leaf<T>::is_underflow() {
    return data.size() < (capacity >> 1) ? true : false;
}

// Check if the leaf node is empty or not. return true if it is empty.
template <class T>
bool Leaf<T>::is_empty() {
    return data.size() == 0 ? true : false;
}

// Check if the leaf node contains data. Return true and the corresponding index in this leaf node if contains.
template <class T>
FindDataResult Leaf<T>::find_data(T value) {
    FindDataResult ret;

    // Perform binary search.
    std::size_t left = 0, mid, right = data.size();
    while (left < right) {
        mid = left + (right - left) / 2;
        if (data[mid] == value) {
            ret.found = true;
            ret.idx = mid;
            return ret;
        } else if (data[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    ret.found = false;
    ret.idx = 0;
    return ret;
}

// Show the data in the leaf node.
template <class T>
void Leaf<T>::show_data() {
    std::cout << "The data is:\n";
    for (std::size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i] << ' ';
    }
    std::cout << '\n';
}

};  // namespace otis
