#pragma once
#include <iostream>
using namespace std;

/// @brief SinglyLinkedListNode class for use in a singly linked list. Contains some data and a pointer to the next node in the list.
/// @tparam T Template for use of generic data.
template<typename T>
class SinglyLinkedListNode {
private:
    T data;
    SinglyLinkedListNode* next;

    template <typename U>
    friend class SinglyLinkedList;

public:
    /// @brief SinglyLinkedListNode constructor.
    SinglyLinkedListNode();
    /// @brief SinglyLinkedListNode parameterized constructor.
    /// @param newData The new data to be stored in the node's data attribute.
    SinglyLinkedListNode(T newData);
};

/// @brief SinglyLinkedList class: implementation of a singly linked list. Contains a pointer to its head and a counter for the number of nodes.
/// @tparam T Template for use of generic data.
template <typename T>
class SinglyLinkedList {
private:
    SinglyLinkedListNode<T>* head;
    int size;

    /// @brief Helper method to swap data between two nodes.
    void swapData(SinglyLinkedListNode<T>*& a, SinglyLinkedListNode<T>*& b);

public:
    /// @brief SinglyLinkedList constructor.
    SinglyLinkedList();
    /// @brief SingyLinkedList copy constructor.
    /// @param other 
    SinglyLinkedList(const SinglyLinkedList<T>& other);
    /// @brief SinglyLinkedList assignment constructor.
    /// @param other 
    /// @return 
    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
    /// @brief SinglyLinkedList destructor.
    ~SinglyLinkedList();

    /// @brief Inserts a new node as the list's head.
    void insertHead(const T& data);
    /// @brief Inserts a new node as the list's tail.
    void insertTail(const T& data);
    /// @brief Inserts a new node after a node that contains a certain data value.
    void insertAfter(const T& target, const T& data);
    /// @brief Inserts a new node before a node that contains a certain data value.
    void insertBefore(const T& target, const T& data);
    /// @brief Inserts a new node at a specific position in the list.
    void insertAt(int position, const T& data);
    /// @brief Inserts a new node in an orderly manner: smallest to biggest.
    void insertOrdered(const T& data);

    /// @brief Deletes the list's head node.
    void deleteHead();
    /// @brief Deletes the list's tail node.
    void deleteTail();
    /// @brief Deletes the node after a node containing a target value.
    void deleteAfter(const T& target);
    /// @brief Deletes the node before a node containing a target value.
    void deleteBefore(const T& target);
    /// @brief Deletes the node at a specific position.
    void deleteAt(int position);
    /// @brief Deletes a node with a specific value.
    void deleteByValue(const T& target);

    /// @brief Searches for a node with a specific value.
    SinglyLinkedListNode<T>* search(const T& target) const;
    /// @brief Sorts the list using bubble sort.
    void sort();
    /// @brief Prints all nodes in the list.
    void print() const;
    /// @brief Clears the list.
    void clear();

    /// @brief Overload of comparison operator == to check if two SLLs are the same (their nodes' data and pointers are the same).
    /// @param other The other list to compare with.
    /// @return True if equals; false otherwise.
    bool operator==(const SinglyLinkedList& other) const;
};

#include <singlyLinkedList.tpp>