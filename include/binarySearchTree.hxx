#pragma once
#include <iostream>
using namespace std;

/// @brief BinarySearchTreeNode class for use in a binary search tree. Contains some data, and pointers to its two children nodes.
/// @tparam T Template for use of generic data. 
template <typename T>
class BinarySearchTreeNode {
  private:
    T data;
    BinarySearchTreeNode* left;
    BinarySearchTreeNode* right;

    template <typename U>
    friend class BinarySearchTree;

  public:
    /// @brief BinarySearchTreeNode constructor.
    BinarySearchTreeNode();
    /// @brief BinarySearchTreeNode copy constructor.
    /// @param other 
    BinarySearchTreeNode(const BinarySearchTreeNode& other);
    /// @brief BinarySearchTreeNode parameterized constructor.
    /// @param newData The new data to be stored in the node's data attribute.
    BinarySearchTreeNode(T newData);
    
    /// @brief Overload of comparison operator == to check if two BST Nodes are the same (their data is the same, and all of their children are equal).
    /// @param otherNode The other node to compare with.
    /// @return True if the nodes are equal; false otherwise.
    bool operator==(const BinarySearchTreeNode& otherNode) const;
};

/// @brief BinarySearchTree class: implementation of a binary search tree. Contains a pointer to its root as an attribute.
/// @tparam T Template for use of generic data.
template <typename T>
class BinarySearchTree {
  private:
    BinarySearchTreeNode<T>* root;

    /// @brief Helper method to find the parent node of a particular child node.
    /// @param child The node whose parent is to be found.
    /// @return A pointer to the parent node.
    BinarySearchTreeNode<T>* findParent(const BinarySearchTreeNode<T>* child);
    /// @brief Helper method to find the successor node when deleting another node.
    /// @param predecessor The node whose successor must be found.
    /// @return A pointer to the successor node.
    BinarySearchTreeNode<T>* findSuccessor(const BinarySearchTreeNode<T>* predecessor);
    /// @brief A helper method to recursively search for a node within the tree.
    /// @param target The data of the node to be searched.
    /// @param current The root of the current tree or sub-tree.
    /// @return A pointer to the node that contains the target data.
    BinarySearchTreeNode<T>* recursiveSearch(const T& target, BinarySearchTreeNode<T>* current) const;
    /// @brief A helper method to recursively traverse the tree in order to find the position in which to insert a new node.
    /// @param data The data that the new node must contain.
    /// @param current The root of the current tree or sub-tree.
    void recursiveInsert(const T& data, BinarySearchTreeNode<T>* current);
    /// @brief A helper method to recursively traverse and print the values in the tree.
    /// @param current The root of the current tree or sub-tree.
    void printInOrder(const BinarySearchTreeNode<T>* current);
    /// @brief A helper method to delete all the nodes in the tree in post order.
    /// @param current The root of the current tree or sub-tree.
    void deletePostOrder(BinarySearchTreeNode<T>* current);
    
  public:
    /// @brief BinarySearchTree constructor.
    BinarySearchTree();
    /// @brief BinarySearchTree copy constructor.
    /// @param other 
    BinarySearchTree(const BinarySearchTree& other);
    /// @brief BinarySearchTree assignment operator.
    /// @param other 
    /// @return 
    BinarySearchTree& operator=(const BinarySearchTree& other);
    /// @brief BinarySearchTree destructor.
    ~BinarySearchTree();

    /// @brief Inserts a new node. Maintains BST order (lesser values to the left, greater values to the right).
    /// @param data The data to be stored in the new node.
    void insert(const T& data);

    /// @brief Removes a node from the tree. Handles pointer management so the BST structure is preserved.
    /// @param data The data of the node to be removed.
    void remove(const T& data);

    /// @brief Searches a node containing a specific target data.
    /// @param target The target data of the node to be searched.
    /// @return A pointer to the node found. nullptr if not found.
    BinarySearchTreeNode<T>* search(const T& target) const;
    /// @brief Prints the tree's contents, ordered smallest to largest.
    void print();
    /// @brief Clears the tree without deleting the instance.
    void clear();

    /// @brief Overload of comparison operator == to check if two BSTs are the same (their nodes' data and pointers are the same).
    /// @note For this to be called, two trees must be compared, not pointers to two trees.
    /// @param other The other tree to compare with.
    /// @return True if equals; false otherwise.
    bool operator==(const BinarySearchTree& other) const;
};

#include <binarySearchTree.tpp>