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

/***************************************/
/* Single Internal Node Data Structure */
/***************************************/
template <class T>
class Index {
   private:
    // The capacity of the internal node. The leaf can contain at most (2 * order) keys and (2 * order + 1) pointers.
    const std::size_t capacity;

    // The keys store at here. The data type is T.
    std::vector<T> key;

    // The pointer of the child "internal" node.
    std::vector<Index<T> *> child;

    // The pointer of the child "leaf" node.
    std::vector<Leaf<T> *> data_ptr;

    // The pointer of the parent internal node. It is used for reverse traversing.
    Index<T> *parent;

    // The indicator shows if this internal node is the bottom of the internal node.
    bool is_bottom;

    // The total amount of data, including all its children.
    std::size_t num_idx_data;

    // The height of this internal node, we define the height of root is 0.
    std::size_t height;

    // Find the next internal node and the corresponding index which may contain data.
    IndexIdx<T> find_next_idx(T value);

   public:
    // Friend Class Declaration
    friend class B_Plus_Tree<T>;
    friend class Leaf<T>;

    // Default Constructor
    Index();

    // Constructor to set the capacity
    Index(std::size_t o);

    // Check if the internal node is overflow or not. return true if it is overflow.
    bool is_overflow();

    // Check if this node is full.
    bool is_full();

    // Check if the internal node is underflow or not. return true if it is underflow.
    // Underflow means the amount of data is less than order (half of the capacity).
    bool is_underflow();

    // Find the leaf node and the corresponding index which may contain data.
    LeafIdx<T> find_data_leaf(T value);
};

/******************************** private ********************************/

// Find the next internal node and the corresponding index which may contain data.
template <class T>
IndexIdx<T> Index<T>::find_next_idx(T value) {
    std::size_t left = 0, mid, right = key.size();
    IndexIdx<T> ret;

    // Perform binary search.
    while (left < right) {
        mid = left + (right - left) / 2;
        if (key[mid] <= value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    ret.index = child[left];
    ret.idx = left;
    return ret;
}

/******************************** public ********************************/

// Default Constructor
template <class T>
Index<T>::Index() : capacity(DEFAULT_ORDER << 1), parent(nullptr), is_bottom(true), num_idx_data(0), height(0) {
    child.resize(capacity + 2, nullptr);
    data_ptr.resize(capacity + 2, nullptr);
}

// Constructor to set the capacity
template <class T>
Index<T>::Index(std::size_t c) : capacity(c), parent(nullptr), is_bottom(true), num_idx_data(0), height(0) {
    child.resize(capacity + 2, nullptr);
    data_ptr.resize(capacity + 2, nullptr);
}

// Check if the internal node is overflow or not. return true if it is overflow.
template <class T>
bool Index<T>::is_overflow() {
    return (key.size() > capacity) ? true : false;
}

// Check if this node is full.
template <class T>
bool Index<T>::is_full() {
    return (key.size() >= capacity) ? true : false;
}

// Check if the internal node is underflow or not. return true if it is underflow.
// Underflow means the amount of data is less than order (half of the capacity).
template <class T>
bool Index<T>::is_underflow() {
    return key.size() < (capacity >> 1) ? true : false;
}

// Find the leaf node and the corresponding index which may contain data.
template <class T>
LeafIdx<T> Index<T>::find_data_leaf(T value) {
    LeafIdx<T> ret;
    std::size_t left = 0, mid, right = key.size();

    // The idx must be the bottom of the internal node.
    if (!is_bottom) {
        ret.leaf = nullptr;
        ret.idx = 0;
        return ret;
    }

    // Perform binary search.
    while (left < right) {
        mid = left + (right - left) / 2;
        if (key[mid] == value) {
            ret.leaf = data_ptr[mid + 1];
            ret.idx = mid + 1;
            return ret;
        } else if (key[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    ret.leaf = data_ptr[left];
    ret.idx = left;
    return ret;
}

};  // namespace otis
