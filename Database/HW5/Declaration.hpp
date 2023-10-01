#pragma once
#include <bits/stdc++.h>

namespace otis {

/**************/
/* Parameters */
/**************/
// The default order of all kinds of nodes in B+ tree.
static const std::size_t DEFAULT_ORDER = 2;

// Class Pre-definition
template <class T>
class Leaf;
template <class T>
class Index;
template <class T>
class B_Plus_Tree;

// Structure for returning pointer and index.
template <class T>
struct LeafIdx {
    Leaf<T> *leaf;
    std::size_t idx;
};

template <class T>
struct IndexIdx {
    Index<T> *index;
    std::size_t idx;
};

struct FindDataResult {
    bool found;
    std::size_t idx;
};

// Enumerate the direction
enum Direction {
    LEFT,
    RIGHT
};

};  // namespace otis
