#pragma once
#include "Internal_Node.hpp"
#include "Leaf_Node.hpp"

/**************************************************************************************
 * Template functions, including member functions, must be written entirely in the
 * header files. This means that if you have a template class, its implementation
 * must be entirely in a header file. This is because the compiler needs to have access
 * to the entire template definition (not just the signature) in order to generate code
 * for each instantiation of the template.
 * Ref: https://vorbrodt.blog/2021/06/23/templates-linking-and-everything-in-between/
 **************************************************************************************/
/*******************************************************************************************************************
 * Nonstatic member as a default argument of a nonstatic member function
 * https://stackoverflow.com/questions/4539406/nonstatic-member-as-a-default-argument-of-a-nonstatic-member-function
 *******************************************************************************************************************/

namespace otis {

/*****************************/
/* The definition of B+ Tree */
/*****************************/
template <class T>
class B_Plus_Tree {
   private:
    // The amount of data.
    std::size_t num_data;

    // The capaticy of the B+ tree.
    const std::size_t capaticy;

    // The root of the B+ tree.
    Index<T> *root;

    // Find the bottom internal node which may contain data.
    Index<T> *find_bottom_idx(T value, Index<T> *idxptr);

    // The default idxptr is root.
    Index<T> *find_bottom_idx(T value);

    // Print a single internal node.
    void print_single_index(Index<T> *idx);

    // Print a single data leaf node.
    void print_single_leaf(Leaf<T> *l);

    // Find the non-full leaf node. Return NULL if cannot found.
    Leaf<T> *find_non_full_leaf(Leaf<T> *start, Direction dir);

    // Solve leaf node overflow
    void leaf_overflow(Leaf<T> *l);

    // Solve internal node overflow
    void index_overflow(Index<T> *idx);

    // Merge two data leaf nodes. This direction represents the position of the node where underflow occurs relative to the node that is to be merged.
    // WARNING: The data pointer l will be nullptr after merging if direction is RIGHT.
    // e.g. [1,_,_,_] [4,5,6,_] LEFT  --> [1,4,5,6][_,_,_,_]
    // e.g. [1,4,5,_] [6,_,_,_] RIGHT --> [1,4,5,6][_,_,_,_]
    void merge_leaf(Leaf<T> *l, Direction dir);

    // Move data to solve leaf underflow. This direction represents the position of the node where underflow occurs relative to the node that is to be merged.
    // e.g. [1,_,_,_] [4,5,6,7] LEFT  --> [1,4,_,_][5,6,7,_]
    // e.g. [1,4,5,6] [7,_,_,_] RIGHT --> [1,4,_,_][5,6,7,_]
    void move_data(Leaf<T> *l, Direction dir);

    // Merge two internal nodes. This direction represents the position of the node where underflow occurs relative to the node that is to be merged.
    // WARNING: The index pointer idx will be nullptr after merging if direction is RIGHT.
    // e.g. P(32,50,_,_) (26,_,_,_)  (38,44,_,_) ... LEFT  -->  P(50,_,_,_) (26,32,38,44) (_,_,_,_) ...; P is parent.
    // e.g. P(32,50,_,_) ... (38,44,_,_) (61,_,_,_)  RIGHT -->  P(32,_,_,_) ... (38,44,50,61) (_,_,_,_); P is parent.
    void merge_index(IndexIdx<T> &idxinf, Direction dir);

    // Move keys to solve internal node underflow. This direction represents the position of the node where underflow occurs relative to the node that is to be merged.
    // e.g. P(32,50,_,_) (26,_,_,_)  (34,38,44,_) ... LEFT  -->  P(34,50,_,_) (26,32,_,_) (38,44,_,_) ...; P is parent.
    // e.g. P(32,50,_,_) ... (34,38,44,_) (61,_,_,_)  RIGHT -->  P(32,44,_,_) ... (34,38,_,_) (50,61,_,_); P is parent.
    void move_key(IndexIdx<T> &idxinf, Direction dir);

    // Solve leaf node underflow
    void leaf_underflow(Leaf<T> *l);

    // Solve internal node underflow
    void index_underflow(Index<T> *idx);

    // Add height to all the children recursively.
    void add_height(Index<T> *idx);

    // Substract height to all the children recursively.
    void sub_height(Index<T> *idx);

   public:
    // Default Constructor
    B_Plus_Tree();

    // Constructor to set the capaticy
    B_Plus_Tree(std::size_t o);

    // Destructor to delete the B+ tree
    ~B_Plus_Tree();

    // copy constructor
    B_Plus_Tree(const B_Plus_Tree &) = delete;

    // move constructor
    B_Plus_Tree(B_Plus_Tree &&) = delete;

    // copy assignment
    B_Plus_Tree &operator=(const B_Plus_Tree &) = delete;
    B_Plus_Tree &operator=(B_Plus_Tree &&) = delete;

    // Get capacity
    std::size_t get_capacity();

    // Checking if a value is contained in this B+ tree.
    bool contains_value(T value);

    // Insert a value into this B+ tree. Return false if there is a duplicate.
    bool insert_value(T value);

    // Delete a value from this B+ tree. Return false if there is no this value.
    bool delete_value(T value);

    // Print the B+ tree in preorder traversal.
    void print_data(Index<T> *idxptr, std::size_t tab_cnt, bool show_debug_msg);

    // The default idxptr is root.
    void print_data(bool show_debug_msg);

    // The default idxptr is root, do not show amount of data in a index by default.
    void print_data();

    // Test the double-linked list in data leaf nodes
    void print_data_leaf();

    // Delete the entire B+ tree
    void drop_tree(Index<T> *idxptr);

    // The default idxptr is root.
    void drop_tree();
};

/******************************** private ********************************/

// Find the bottom internal node which may contain data.
template <class T>
Index<T> *B_Plus_Tree<T>::find_bottom_idx(T value, Index<T> *idxptr) {
    if (idxptr == nullptr) {
        return nullptr;
    }
    if (idxptr->is_bottom) {
        return idxptr;
    }
    return find_bottom_idx(value, idxptr->find_next_idx(value).index);
}

// The default idxptr is root.
template <class T>
Index<T> *B_Plus_Tree<T>::find_bottom_idx(T value) {
    return find_bottom_idx(value, root);
}

// Print a single internal node.
template <class T>
void B_Plus_Tree<T>::print_single_index(Index<T> *idx) {
    std::cout << '(';
    for (std::size_t i = 0; i < capaticy; ++i) {
        if (i < idx->key.size()) {
            std::cout << idx->key[i];
        } else {
            std::cout << '_';
        }

        if (i == capaticy - 1) {
            std::cout << ')';
        } else {
            std::cout << ',';
        }
    }
    return;
}

// Print a single data leaf node.
template <class T>
void B_Plus_Tree<T>::print_single_leaf(Leaf<T> *l) {
    std::cout << '[';
    for (std::size_t i = 0; i < capaticy; ++i) {
        if (i < l->data.size()) {
            std::cout << l->data[i];
        } else {
            std::cout << '_';
        }

        if (i == capaticy - 1) {
            std::cout << ']';
        } else {
            std::cout << ',';
        }
    }
}

// Find the non-full leaf node. Return NULL if cannot found.
template <class T>
Leaf<T> *B_Plus_Tree<T>::find_non_full_leaf(Leaf<T> *start, Direction dir) {
    while (start != nullptr) {
        if (start->data.size() < capaticy) {
            return start;
        }
        switch (dir) {
            case LEFT:
                start = start->prev;
                break;

            case RIGHT:
                start = start->next;
                break;

            default:
                break;
        }
    }
    return nullptr;
}

// Solve leaf node overflow
template <class T>
void B_Plus_Tree<T>::leaf_overflow(Leaf<T> *l) {
    // Check if overflow occurs.
    if (!l->is_overflow()) {
        return;
    }

    // Specify the parent internal node of the leaf node.
    Index<T> *parent = l->parent;
    assert(parent != nullptr);

    // Create a new leaf node.
    Leaf<T> *newleaf = new Leaf<T>(capaticy);

    // Split the data
    for (std::size_t i = 0; i <= (capaticy >> 1); ++i) {
        newleaf->data.insert(newleaf->data.begin(), l->data.back());
        l->data.pop_back();
    }

    // Setup the new leaf node.
    newleaf->parent = parent;
    newleaf->prev = l;
    newleaf->next = l->next;
    if (newleaf->next != nullptr) {
        newleaf->next->prev = newleaf;
    }

    // Setup the old leaf node.
    l->next = newleaf;

    // Copy up
    parent->key.push_back(newleaf->data[0]);

    // Sort the key (Insertion sort)
    T temp = parent->key[parent->key.size() - 1];
    std::size_t i;
    for (i = parent->key.size() - 1; i > 0; --i) {
        if (parent->key[i - 1] > temp) {
            parent->key[i] = parent->key[i - 1];
            parent->data_ptr[i + 1] = parent->data_ptr[i];
        } else {
            break;
        }
    }
    parent->key[i] = temp;
    parent->data_ptr[i + 1] = newleaf;

    // Recursively check the parent internal node.
    index_overflow(parent);

    return;
}

// Solve internal node overflow
template <class T>
void B_Plus_Tree<T>::index_overflow(Index<T> *idx) {
    // Check if overflow occurs.
    if (!idx->is_overflow()) {
        return;
    }

    // Split the internal node into 3 internal nodes, which are the middle value, and the rest to the two sides.
    Index<T> *newidx = new Index<T>(capaticy);
    newidx->is_bottom = idx->is_bottom;
    newidx->height = idx->height;

    // Split the key
    for (std::size_t i = 0; i < (capaticy >> 1); ++i) {
        newidx->key.push_back(idx->key.back());
        idx->key.pop_back();
    }
    T mid_val = idx->key.back();
    idx->key.pop_back();
    std::reverse(newidx->key.begin(), newidx->key.end());

    if (idx->is_bottom) {
        // Setup the data pointer
        for (std::size_t i = 0; i <= (capaticy >> 1); ++i) {
            newidx->data_ptr[i] = idx->data_ptr[i + (capaticy >> 1) + 1];
            idx->data_ptr[i + (capaticy >> 1) + 1] = nullptr;
            if (newidx->data_ptr[i] != nullptr) {
                newidx->data_ptr[i]->parent = newidx;
            }
        }

        // num_idx_data
        idx->num_idx_data = 0;
        for (std::size_t i = 0; i <= (capaticy >> 1); ++i) {
            if (idx->data_ptr[i] != nullptr) {
                idx->num_idx_data += idx->data_ptr[i]->data.size();
            }
            if (newidx->data_ptr[i] != nullptr) {
                newidx->num_idx_data += newidx->data_ptr[i]->data.size();
            }
        }
    } else {
        // Setup the children pointer
        for (std::size_t i = 0; i <= (capaticy >> 1); ++i) {
            newidx->child[i] = idx->child[i + (capaticy >> 1) + 1];
            idx->child[i + (capaticy >> 1) + 1] = nullptr;
            if (newidx->child[i] != nullptr) {
                newidx->child[i]->parent = newidx;
            }
        }

        // num_idx_data
        idx->num_idx_data = 0;
        for (std::size_t i = 0; i <= (capaticy >> 1); ++i) {
            if (idx->child[i] != nullptr) {
                idx->num_idx_data += idx->child[i]->num_idx_data;
            }
            if (newidx->child[i] != nullptr) {
                newidx->num_idx_data += newidx->child[i]->num_idx_data;
            }
        }
    }

    // If this original internal node is root.
    if (root == idx) {
        // Push up the middle value to be the new root.
        Index<T> *newroot = new Index<T>(capaticy);
        newroot->key.push_back(mid_val);
        newroot->is_bottom = false;
        newroot->num_idx_data = idx->num_idx_data + newidx->num_idx_data;

        // Setup the new parent.
        idx->parent = newroot;
        newidx->parent = newroot;

        // Setup the new root.
        root = newroot;

        // We need to add height to all the children recursively.
        add_height(idx);
        add_height(newidx);

        // Setup the index pointer
        newroot->child[0] = idx;
        newroot->child[1] = newidx;
    } else {
        // Specify the parent of the leaf node.
        Index<T> *parent = idx->parent;

        // Setup the new parent.
        newidx->parent = parent;

        // Push up the middle value to the parent of this internal node.
        parent->key.push_back(mid_val);
        // parent->num_idx_data += idx->num_idx_data + newidx->num_idx_data;

        // Sort the key (Insertion sort)
        T temp = parent->key[parent->key.size() - 1];
        std::size_t i;
        for (i = parent->key.size() - 1; i > 0; --i) {
            if (parent->key[i - 1] > temp) {
                parent->key[i] = parent->key[i - 1];
                parent->child[i + 1] = parent->child[i];
            } else {
                break;
            }
        }
        parent->key[i] = temp;
        parent->child[i + 1] = newidx;

        // Check RECURSIVELY if OVERFLOW occurs again for their parents.
        index_overflow(parent);
    }

    return;
}

// Merge two data leaf nodes. This direction represents the position of the node where underflow occurs relative to the node that is to be merged.
// WARNING: The data pointer l will be nullptr after merging if direction is RIGHT.
// e.g. [1,_,_,_] [4,5,6,_] LEFT  --> [1,4,5,6][_,_,_,_]
// e.g. [1,4,5,_] [6,_,_,_] RIGHT --> [1,4,5,6][_,_,_,_]
template <class T>
void B_Plus_Tree<T>::merge_leaf(Leaf<T> *l, Direction dir) {
    Leaf<T> *dataptr = l;
    Leaf<T> *nextdataptr = dataptr->next;
    // The nextdataptr must at the right hand side of the dataptr.
    switch (dir) {
        case LEFT:
            nextdataptr = dataptr->next;
            break;
        case RIGHT:
            nextdataptr = dataptr->prev;
            std::swap(dataptr, nextdataptr);
            break;
        default:
            nextdataptr = dataptr->next;
            break;
    }
    assert(nextdataptr != nullptr);
    LeafIdx<T> datainf = dataptr->parent->find_data_leaf(dataptr->data[0]);
    LeafIdx<T> nextdatainf = nextdataptr->parent->find_data_leaf(nextdataptr->data[0]);
    assert(dataptr == datainf.leaf);
    assert(nextdataptr == nextdatainf.leaf);
    assert(dataptr->data.size() + nextdataptr->data.size() <= capaticy);

    // Copy data from right to left
    for (std::size_t i = 0; i < nextdataptr->data.size(); ++i) {
        dataptr->data.push_back(nextdataptr->data[i]);
        ++(dataptr->parent->num_idx_data);
        --(nextdataptr->parent->num_idx_data);
    }

    // If the parents of the two data leaves are same
    if (dataptr->parent == nextdataptr->parent) {
        // Delete the key
        dataptr->parent->key.erase(dataptr->parent->key.begin() + datainf.idx);

        // Move the data pointer
        for (std::size_t i = nextdatainf.idx; i < capaticy + 1; ++i) {
            dataptr->parent->data_ptr[i] = dataptr->parent->data_ptr[i + 1];
        }
        dataptr->parent->data_ptr[capaticy + 1] = nullptr;
    }

    // Otherwise, their parent are different.
    else {
        // Find co-ancestor
        Index<T> *this_ancestor = dataptr->parent->parent;
        Index<T> *next_ancestor = nextdataptr->parent->parent;
        while (this_ancestor != next_ancestor) {
            if (this_ancestor->parent != nullptr && next_ancestor->parent != nullptr) {
                this_ancestor = this_ancestor->parent;
                next_ancestor = next_ancestor->parent;
            } else {
                std::cerr << "\x1B[31mError occurs in merge_leaf.\x1B[0m\n";
                return;
            }
        }

        // Specify the information of the leaf node, its right sibling, and their indices from their parent.
        // IndexIdx<T> dataparent = this_ancestor->find_next_idx(dataptr->data[0]);
        IndexIdx<T> dataparent = this_ancestor->find_next_idx(dataptr->parent->key[0]);

        // Update the key in ancestor
        assert(nextdatainf.idx == 0);
        this_ancestor->key[dataparent.idx] = nextdataptr->parent->key[nextdatainf.idx];

        // Delete the key
        nextdataptr->parent->key.erase(nextdataptr->parent->key.begin() + nextdatainf.idx);

        // Move the data pointer
        for (std::size_t i = nextdatainf.idx; i < capaticy + 1; ++i) {
            nextdataptr->parent->data_ptr[i] = nextdataptr->parent->data_ptr[i + 1];
        }
        nextdataptr->parent->data_ptr[capaticy + 1] = nullptr;
    }  // End check if the parents of the two data leaves are same

    // Setup the doubly-linked list
    dataptr->next = nextdataptr->next;
    if (nextdataptr->next != nullptr) {
        nextdataptr->next->prev = dataptr;
    }

    // Delete the empty leaf node.
    delete nextdataptr;
    return;
}

// Move data to solve leaf underflow. This direction represents the position of the node where underflow occurs relative to the node that is to be merged.
// e.g. [1,_,_,_] [4,5,6,7] LEFT  --> [1,4,_,_][5,6,7,_]
// e.g. [1,4,5,6] [7,_,_,_] RIGHT --> [1,4,5,_][6,7,_,_]
template <class T>
void B_Plus_Tree<T>::move_data(Leaf<T> *l, Direction dir) {
    Leaf<T> *dataptr = l;
    Leaf<T> *nextdataptr = dataptr->next;
    switch (dir) {
        case LEFT:
            nextdataptr = dataptr->next;
            break;
        case RIGHT:
            nextdataptr = dataptr->prev;
            break;
        default:
            nextdataptr = dataptr->next;
            break;
    }
    assert(nextdataptr != nullptr);
    LeafIdx<T> datainf = dataptr->parent->find_data_leaf(dataptr->data[0]);
    LeafIdx<T> nextdatainf = nextdataptr->parent->find_data_leaf(nextdataptr->data[0]);
    assert(dataptr == datainf.leaf);
    assert(nextdataptr == nextdatainf.leaf);
    T temp;

    // Move data from nextdataptr to dataptr til dataptr is not underflow.
    while (dataptr->is_underflow()) {
        switch (dir) {
            case LEFT:
                temp = nextdataptr->data[0];
                nextdataptr->data.erase(nextdataptr->data.begin());
                dataptr->data.push_back(temp);
                break;
            case RIGHT:
                temp = nextdataptr->data.back();
                nextdataptr->data.pop_back();
                dataptr->data.insert(dataptr->data.begin(), temp);
                break;
            default:
                break;
        }
        ++(dataptr->parent->num_idx_data);
        --(nextdataptr->parent->num_idx_data);
    }

    // The nextdataptr must at the right hand side of the dataptr from now on.
    if (dir == RIGHT) {
        std::swap(dataptr, nextdataptr);
        datainf = dataptr->parent->find_data_leaf(dataptr->data[0]);
        nextdatainf = nextdataptr->parent->find_data_leaf(nextdataptr->data[0]);
    }

    // Specify the new key
    temp = nextdataptr->data[0];

    // If the parents of the two data leaves are same
    if (dataptr->parent == nextdataptr->parent) {
        // Assign the new key to parent.
        dataptr->parent->key[datainf.idx] = temp;
    }

    // Otherwise, their parent are different.
    else {
        // Find co-ancestor
        Index<T> *this_ancestor = dataptr->parent->parent;
        Index<T> *next_ancestor = nextdataptr->parent->parent;
        while (this_ancestor != next_ancestor) {
            if (this_ancestor->parent != nullptr && next_ancestor->parent != nullptr) {
                this_ancestor = this_ancestor->parent;
                next_ancestor = next_ancestor->parent;
            } else {
                std::cerr << "\x1B[31mError occurs in move_data.\x1B[0m\n";
                return;
            }
        }

        // Specify the information of the leaf node, its right sibling, and their indices from their parent.
        IndexIdx<T> dataparent = this_ancestor->find_next_idx(dataptr->data[0]);

        // Update the key in ancestor
        assert(nextdatainf.idx == 0);
        this_ancestor->key[dataparent.idx] = nextdataptr->data[0];
    }
    return;
}

// Merge two internal nodes. This direction represents the position of the node where underflow occurs relative to the node that is to be merged.
// WARNING: The index pointer idx will be nullptr after merging if direction is RIGHT.
// e.g. P(32,50,_,_) (26,_,_,_)  (38,44,_,_) ... LEFT  -->  P(50,_,_,_) (26,32,38,44) (_,_,_,_) ...; P is parent.
// e.g. P(32,50,_,_) ... (38,44,_,_) (61,_,_,_)  RIGHT -->  P(32,_,_,_) ... (38,44,50,61) (_,_,_,_); P is parent.
template <class T>
void B_Plus_Tree<T>::merge_index(IndexIdx<T> &idxinf, Direction dir) {
    Index<T> *merge = idxinf.index;
    Index<T> *parent = merge->parent;
    Index<T> *target = nullptr;
    std::size_t idx = idxinf.idx;
    bool target_has_no_data_or_key = false;

    // The target must at the right hand side of the index.
    switch (dir) {
        case LEFT:
            target = parent->child[idxinf.idx + 1];
            break;
        case RIGHT:
            merge = parent->child[idxinf.idx - 1];
            target = idxinf.index;
            idx = idxinf.idx - 1;
            break;
        default:
            break;
    }
    assert(merge != nullptr);
    assert(parent != nullptr);
    assert(target != nullptr);
    assert(merge->key.size() + target->key.size() + 1 <= capaticy);

    // Copy children from right to left.
    if (merge->is_bottom) {
        // Check if the target has no data pointer
        if (target->data_ptr[0] == nullptr) {
            target_has_no_data_or_key = true;
        } else {
            for (std::size_t i = 0; i < target->key.size() + 1; ++i) {
                merge->data_ptr[merge->key.size() + 1 + i] = target->data_ptr[i];

                // Setup the new parent for all data pointer.
                if (merge->data_ptr[merge->key.size() + 1 + i] != nullptr) {
                    merge->data_ptr[merge->key.size() + 1 + i]->parent = merge;
                }
            }
        }
    } else {
        // Check if the target has no children
        if (target->child[0] == nullptr) {
            target_has_no_data_or_key = true;
        } else {
            for (std::size_t i = 0; i < target->key.size() + 1; ++i) {
                merge->child[merge->key.size() + 1 + i] = target->child[i];

                // Setup the new parent for all children.
                if (merge->child[merge->key.size() + 1 + i] != nullptr) {
                    merge->child[merge->key.size() + 1 + i]->parent = merge;
                }
            }
        }
    }

    // If the direction is RIGHT and the target has no data or key, then we don't need to copy key from parent.
    if (!(dir == RIGHT && target_has_no_data_or_key)) {
        // Copy keys from parent.
        merge->key.push_back(parent->key[idx]);
    }

    // Copy keys from right (target) to left (merge).
    for (std::size_t i = 0; i < target->key.size(); ++i) {
        merge->key.push_back(target->key[i]);
    }

    // Calculate new number of index data.
    merge->num_idx_data += target->num_idx_data;

    // Delete the key at index idx in parent.
    parent->key.erase(parent->key.begin() + idx);

    for (std::size_t i = idx + 1; i < capaticy + 1; ++i) {
        parent->child[i] = parent->child[i + 1];
    }
    parent->child[capaticy + 1] = nullptr;

    // Delete the empty target internal node.
    delete target;

    return;
}

// Move keys to solve internal node underflow. This direction represents the position of the node where underflow occurs relative to the node that is to be merged.
// e.g. P(32,50,_,_) (26,_,_,_)  (34,38,44,_) ... LEFT  -->  P(34,50,_,_) (26,32,_,_) (38,44,_,_) ...; P is parent.
// e.g. P(32,50,_,_) ... (34,38,44,_) (61,_,_,_)  RIGHT -->  P(32,44,_,_) ... (34,38,_,_) (50,61,_,_); P is parent.
template <class T>
void B_Plus_Tree<T>::move_key(IndexIdx<T> &idxinf, Direction dir) {
    Index<T> *move = idxinf.index;
    Index<T> *parent = move->parent;
    Index<T> *target = nullptr;
    std::size_t idx = idxinf.idx;

    // The target must at the right hand side of the index.
    switch (dir) {
        case LEFT:
            target = parent->child[idxinf.idx + 1];
            break;
        case RIGHT:
            target = parent->child[idxinf.idx - 1];
            idx = idxinf.idx - 1;
            break;
        default:
            break;
    }
    assert(move != nullptr);
    assert(parent != nullptr);
    assert(target != nullptr);
    assert(move->key.size() + target->key.size() + 1 > capaticy);

    // Move one key and one child/data pointer from "target" to "move" to make "move" is not underflow.
    switch (dir) {
        case LEFT:
            // child/data
            if (move->is_bottom) {
                // Move a data leaf pointer from "target" to "move".
                move->data_ptr[move->key.size() + 1] = target->data_ptr[0];

                // Assign new parent.
                if (move->data_ptr[move->key.size() + 1] != nullptr) {
                    move->data_ptr[move->key.size() + 1]->parent = move;
                }

                // Shift one index left for all data leaf pointer in "target".
                for (std::size_t i = 0; i < target->key.size(); ++i) {
                    target->data_ptr[i] = target->data_ptr[i + 1];
                }
                target->data_ptr[target->key.size()] = nullptr;
            } else {
                // Move an internal node pointer from "target" to "move".
                move->child[move->key.size() + 1] = target->child[0];

                // Assign new parent.
                if (move->child[move->key.size() + 1] != nullptr) {
                    move->child[move->key.size() + 1]->parent = move;
                }

                // Shift one index left for all internal node pointer in "target".
                for (std::size_t i = 0; i < target->key.size(); ++i) {
                    target->child[i] = target->child[i + 1];
                }
                target->child[target->key.size()] = nullptr;
            }

            // key
            move->key.push_back(parent->key[idx]);
            parent->key[idx] = target->key[0];
            target->key.erase(target->key.begin());
            break;
        case RIGHT:
            // child/data
            if (move->is_bottom) {
                // Shift one index right for all data leaf pointer in "move".
                for (std::size_t i = 0; i < capaticy + 1; ++i) {
                    move->data_ptr[capaticy + 1 - i] = move->data_ptr[capaticy - i];
                }

                // Move a data leaf pointer from "target" to "move".
                move->data_ptr[0] = target->data_ptr[target->key.size()];
                target->data_ptr[target->key.size()] = nullptr;

                // Assign new parent.
                if (move->data_ptr[0] != nullptr) {
                    move->data_ptr[0]->parent = move;
                }
            } else {
                // Shift one index right for all internal node pointer in "move".
                for (std::size_t i = 0; i < capaticy + 1; ++i) {
                    move->child[capaticy + 1 - i] = move->child[capaticy - i];
                }

                // Move an internal node pointer from "target" to "move".
                move->child[0] = target->child[target->key.size()];
                target->child[target->key.size()] = nullptr;

                // Assign new parent.
                if (move->child[0] != nullptr) {
                    move->child[0]->parent = move;
                }
            }

            // key
            move->key.insert(move->key.begin(), parent->key[idx]);
            parent->key[idx] = target->key.back();
            target->key.pop_back();
            break;
        default:
            break;
    }

    // Calculate new number of index data.
    move->num_idx_data = 0;
    target->num_idx_data = 0;
    if (move->is_bottom) {
        Leaf<T> *ltmp;
        for (std::size_t i = 0; i < move->key.size() + 1; ++i) {
            ltmp = move->data_ptr[i];
            if (ltmp != nullptr) {
                move->num_idx_data += ltmp->data.size();
            }
        }
        for (std::size_t i = 0; i < target->key.size() + 1; ++i) {
            ltmp = target->data_ptr[i];
            if (ltmp != nullptr) {
                target->num_idx_data += ltmp->data.size();
            }
        }
    } else {
        Index<T> *itmp;
        for (std::size_t i = 0; i < move->key.size() + 1; ++i) {
            itmp = move->child[i];
            if (itmp != nullptr) {
                move->num_idx_data += itmp->num_idx_data;
            }
        }
        for (std::size_t i = 0; i < target->key.size() + 1; ++i) {
            itmp = target->child[i];
            if (itmp != nullptr) {
                target->num_idx_data += itmp->num_idx_data;
            }
        }
    }

    return;
}

// Solve leaf node underflow
template <class T>
void B_Plus_Tree<T>::leaf_underflow(Leaf<T> *l) {
    Leaf<T> *dataptr = l;

    // If the leaf node is underflow
    if (dataptr->is_underflow()) {
        // Check if the leaf node has right sibling.
        if (dataptr->next != nullptr) {
            // Specify the parent of the next data leaf node.
            Index<T> *next_dataptr_parent = dataptr->next->parent;

            // If these two leaf nodes can be merged.
            if (dataptr->data.size() + dataptr->next->data.size() <= capaticy) {
                merge_leaf(dataptr, LEFT);

                // Check if the parent is empty recursively.
                index_underflow(next_dataptr_parent);
            }

            // Otherwise, move data from the right sibling til the leaf node is not underflow.
            else {
                move_data(dataptr, LEFT);
            }  // End check if these two leaf nodes can be merged.
        }

        // If the leaf node has NO right sibling, check if the leaf node has left sibling.
        else if (dataptr->prev != nullptr) {
            // Specify the parent of the next data leaf node.
            Index<T> *dataptr_parent = dataptr->parent;

            // If these two leaf nodes can be merged.
            if (dataptr->data.size() + dataptr->prev->data.size() <= capaticy) {
                merge_leaf(dataptr, RIGHT);
                // WARNING: The dataptr is nullptr after merging in this situation.

                // Check if the parent is empty recursively.
                index_underflow(dataptr_parent);
            }

            // Otherwise, move data from the right sibling til the leaf node is not underflow.
            else {
                move_data(dataptr, RIGHT);
            }  // End check if these two leaf nodes can be merged.
        }

        // Otherwise, there is only one leaf node left.
        else {
            // If the leaf node is empty
            if (dataptr->data.size() == 0) {
                // It means that the tree is empty.
                delete dataptr;
                delete root;
                root = nullptr;
            }
            // We can't do any re-distribution here.
        }  // End check if the leaf node has right sibling.
    }
    return;
}

// Solve internal node underflow
template <class T>
void B_Plus_Tree<T>::index_underflow(Index<T> *idx) {
    // If the idx is NULL, then ignore it.
    if (idx == nullptr) {
        return;
    }

    // Deal with root.
    if (idx == root) {
        // If there is no key in root.
        if (idx->key.size() == 0) {
            // If this root is not at bottom.
            if (!idx->is_bottom) {
                // Specify the first child of internal node in the old root (idx).
                Index<T> *newroot = idx->child[0];

                // Delete the origin root.
                delete root;
                newroot->parent = nullptr;

                // Assign the new root.
                root = newroot;

                // Decrease height
                sub_height(root);
            }

            // Otherwise, this root is at bottom.
            else {
                // Specify the only one data leaf pointer.
                Leaf<T> *dataptr = idx->data_ptr[0];
                assert(dataptr != nullptr);

                // Add new key to root. The new key is the last value of data + 1.
                idx->key.push_back(dataptr->data.back() + 1);
            }
        }

        // Otherwise, the root has at least one key, then we don't need to consider the underflow for root.
        return;
    }

    // If the internal node is underflow
    if (idx->is_underflow()) {
        Index<T> *parent = idx->parent;
        assert(parent != nullptr);
        IndexIdx<T> idxinf = parent->find_next_idx(idx->key[0]);
        assert(idx == idxinf.index);

        // Check if the leaf node has right sibling.
        if (parent->child[idxinf.idx + 1] != nullptr) {
            // Specify the right sibling
            Index<T> *next = parent->child[idxinf.idx + 1];

            // If these two leaf nodes can be merged.
            if (idx->key.size() + next->key.size() + 1 <= capaticy) {
                // Merge it
                merge_index(idxinf, LEFT);

                // Check if the parent is empty recursively.
                index_underflow(idx->parent);
            }

            // Otherwise, move data from the right sibling til the leaf node is not underflow.
            else {
                move_key(idxinf, LEFT);
            }
        }

        // If the leaf node has NO right sibling, check if the leaf node has left sibling.
        else if (idxinf.idx != 0) {
            if (parent->child[idxinf.idx - 1] != nullptr) {  // Two step checking to avoid size_t underflow (0 - 1 = -1).
                // Specify the right sibling
                Index<T> *prev = parent->child[idxinf.idx - 1];

                // If these two leaf nodes can be merged.
                if (idx->key.size() + prev->key.size() + 1 <= capaticy) {
                    // Merge it
                    merge_index(idxinf, RIGHT);

                    // Check if the parent is empty recursively.
                    index_underflow(prev->parent);
                }

                // Otherwise, move data from the right sibling til the leaf node is not underflow.
                else {
                    move_key(idxinf, RIGHT);
                }
            }
        }
    }

    return;
}

// Add height to all the children recursively.
template <class T>
void B_Plus_Tree<T>::add_height(Index<T> *idx) {
    ++(idx->height);
    for (std::size_t i = 0; i < capaticy + 1; ++i) {
        if (idx->child[i] == nullptr) {
            break;
        } else {
            add_height(idx->child[i]);
        }
    }
    return;
}

// Substract height to all the children recursively.
template <class T>
void B_Plus_Tree<T>::sub_height(Index<T> *idx) {
    // Avoid underflow.
    if (idx->height > 0) {
        --(idx->height);
    }

    for (std::size_t i = 0; i < capaticy + 1; ++i) {
        if (idx->child[i] == nullptr) {
            break;
        } else {
            sub_height(idx->child[i]);
        }
    }
    return;
}

/******************************** public ********************************/

// Default Constructor
template <class T>
B_Plus_Tree<T>::B_Plus_Tree() : B_Plus_Tree(DEFAULT_ORDER << 1) {}

// Constructor to set the order
template <class T>
B_Plus_Tree<T>::B_Plus_Tree(std::size_t o) : num_data(0), capaticy(o << 1), root(nullptr) {}

// Destructor to delete the B+ tree
template <class T>
B_Plus_Tree<T>::~B_Plus_Tree() {
    drop_tree();
}

// Get capacity
template <class T>
std::size_t B_Plus_Tree<T>::get_capacity() {
    return capaticy;
}

// Checking if a value is contained in a B+ tree.
template <class T>
bool B_Plus_Tree<T>::contains_value(T value) {
    // Check if the B+ tree is empty.
    if (root == nullptr) {
        return false;
    }

    // The bottom of the internal node
    Index<T> *bot_idx = find_bottom_idx(value);

    // The leaf node pointer.
    LeafIdx<T> data = bot_idx->find_data_leaf(value);

    // Check if the leaf node is legal.
    if (data.leaf == nullptr) {
        return false;
    }

    // Find the data.
    return data.leaf->find_data(value).found;
}

// Insert a value into this B+ tree. Return false if there is a duplicate.
template <class T>
bool B_Plus_Tree<T>::insert_value(T value) {
    // Check if there is a duplicate
    if (contains_value(value)) {
        return false;
    }

    // If this is a new/empty B+ tree, then we don't need to consider the underflow and re-distribution.
    if (root == nullptr) {
        // Create a new internal node.
        Index<T> *newidx = new Index<T>(capaticy);

        // Create a new leaf node.
        Leaf<T> *newleaf = new Leaf<T>(capaticy);

        // Assign the root to be this new internal node.
        root = newidx;

        // Setup for leaf node.
        newleaf->parent = newidx;
        newleaf->data.push_back(value);

        // Setup for internal node.
        newidx->key.push_back(value + 1);
        newidx->data_ptr[0] = newleaf;
        ++(newidx->num_idx_data);

        // Add the new value successfully.
        ++num_data;

        return true;
    }

    // If this B+ tree has at least 1 data.
    // Search the appropriate bottom internal node.
    Index<T> *bot_idx = find_bottom_idx(value);

    // Search the appropriate leaf node.
    LeafIdx<T> data = bot_idx->find_data_leaf(value);

    // If the leaf node is NULL, then underflow is occured.
    if (data.leaf == nullptr) {
        // Specify the left sibling.
        Leaf<T> *leftsibling = bot_idx->data_ptr[data.idx - 1];

        // Create a new leaf node.
        Leaf<T> *newleaf = new Leaf<T>(capaticy);

        // Setup for leaf node.
        newleaf->parent = bot_idx;
        newleaf->data.push_back(value);
        newleaf->prev = leftsibling;
        leftsibling->next = newleaf;

        // Setup for internal node.
        // if (bot_idx->key.size() < data.idx) {
        //     bot_idx->key.push_back(value);
        // }
        bot_idx->data_ptr[data.idx] = newleaf;

        // Update the total amount of data for each internal node.
        Index<T> *traverse = bot_idx;
        while (traverse != nullptr) {
            ++(traverse->num_idx_data);
            traverse = traverse->parent;
        }

        // Re-distribution
        leaf_underflow(newleaf);
    }
    // The leaf node exists. Insert the value into the leaf node.
    else {
        data.leaf->data.push_back(value);

        // Sort the leaf node.
        std::sort(data.leaf->data.begin(), data.leaf->data.end());

        // Update the total amount of data for each internal node.
        Index<T> *traverse = bot_idx;
        while (traverse != nullptr) {
            ++(traverse->num_idx_data);
            traverse = traverse->parent;
        }

        // Check if the leaf node overflows.
        leaf_overflow(data.leaf);
    }
    // Add the new value successfully.
    ++num_data;

    return true;
}

// Delete a value from this B+ tree. Return false if there is no this value.
template <class T>
bool B_Plus_Tree<T>::delete_value(T value) {
    // Check if the B+ tree is empty
    if (root == nullptr || num_data == 0) {
        return false;
    }

    // Search the appropriate bottom internal node.
    Index<T> *bot_idx = find_bottom_idx(value);

    // Search the appropriate leaf node.
    LeafIdx<T> data = bot_idx->find_data_leaf(value);

    // Check if the B+ tree contains this value.
    if (data.leaf == nullptr) {
        return false;
    }
    
    FindDataResult result = data.leaf->find_data(value);
    if (!result.found) {
        return false;
    }

    // Delete the data.
    data.leaf->data.erase(data.leaf->data.begin() + result.idx);

    // Update the total amount of data for each internal node.
    Index<T> *idxptr = bot_idx;
    while (idxptr != nullptr) {
        --(idxptr->num_idx_data);
        idxptr = idxptr->parent;
    }
    --num_data;

    // Check if the leaf node underflows.
    leaf_underflow(data.leaf);

    return true;
}

// Print the B+ tree in preorder traversal.
template <class T>
void B_Plus_Tree<T>::print_data(Index<T> *idxptr, std::size_t tab_cnt, bool show_debug_msg) {
    std::size_t i = 0, k = 0, tab = 0;

    // Check if the internal node is valid.
    if (idxptr == nullptr) {
        return;
    }

    // Print tab
    for (tab = 0; tab < tab_cnt; ++tab) {
        std::cout << '\t';
    }

    // Print internal node
    print_single_index(idxptr);

    // Print the total amount of data, including all its children.
    if (show_debug_msg) {
        std::cout << ": #" << idxptr->num_idx_data << ", h: " << idxptr->height;
    }

    std::cout << '\n';

    // Print the next internal node
    if (!idxptr->is_bottom) {
        for (k = 0; k < capaticy + 1; ++k) {
            print_data(idxptr->child[k], tab_cnt + 1, show_debug_msg);
        }
    } else {  // Print the leaf node.
        for (i = 0; i < idxptr->data_ptr.size(); ++i) {
            Leaf<T> *dataptr = idxptr->data_ptr[i];
            if (dataptr == nullptr) {
                break;
            }

            // Print tab
            for (tab = 0; tab < tab_cnt + 1; ++tab) {
                std::cout << '\t';
            }

            print_single_leaf(dataptr);
            std::cout << '\n';
        }
    }
}

// The default idxptr is root.
template <class T>
void B_Plus_Tree<T>::print_data(bool show_debug_msg) {
    print_data(root, 0, show_debug_msg);
    std::cout << '\n'
              << num_data << " data in B+ tree.\n\n";
    if (show_debug_msg) {
        print_data_leaf();
    }
    return;
}

// The default idxptr is root, do not show amount of data in a index by default.
template <class T>
void B_Plus_Tree<T>::print_data() {
    print_data(false);
    return;
}

// Test the double-linked list in data leaf nodes
template <class T>
void B_Plus_Tree<T>::print_data_leaf() {
    Index<T> *first_bot_idx = root;
    Leaf<T> *first_data_leaf, *traverse;

    if (root == nullptr) {
        return;
    }

    while (!first_bot_idx->is_bottom) {
        first_bot_idx = first_bot_idx->child[0];
    }
    first_data_leaf = first_bot_idx->data_ptr[0];
    traverse = first_data_leaf;

    std::cout << "-------------------------------\n";
    std::cout << "Testing the doubly-linked list.\n\n";
    std::cout << "From left to right:\n";
    while (true) {
        print_single_leaf(traverse);
        std::cout << " --> ";
        if (traverse->next != nullptr) {
            traverse = traverse->next;
        } else {
            std::cout << "NULL";
            break;
        }
    }
    std::cout << "\n\n";

    std::cout << "From right to left:\n";
    while (true) {
        print_single_leaf(traverse);
        std::cout << " --> ";
        if (traverse->prev != nullptr) {
            traverse = traverse->prev;
        } else {
            std::cout << "NULL";
            break;
        }
    }
    std::cout << '\n';

    assert(traverse == first_data_leaf);

    return;
}

// Delete the entire B+ tree
template <class T>
void B_Plus_Tree<T>::drop_tree(Index<T> *idxptr) {
    std::size_t i = 0, k = 0;

    // Check if the internal node is valid.
    if (idxptr == nullptr) {
        return;
    }

    // Find the next internal node
    if (!idxptr->is_bottom) {
        for (k = 0; k < capaticy + 1; ++k) {
            drop_tree(idxptr->child[k]);
        }
    } else {  // Delete the leaf node.
        for (i = 0; i < idxptr->data_ptr.size(); ++i) {
            Leaf<T> *dataptr = idxptr->data_ptr[i];
            if (dataptr == nullptr) {
                break;
            }
            delete dataptr;
        }
    }

    // Delete the internal node
    delete idxptr;
    idxptr = nullptr;
}

// The default idxptr is root.
template <class T>
void B_Plus_Tree<T>::drop_tree() {
    return drop_tree(root);
}

};  // namespace otis
