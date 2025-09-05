//=================================================
// Joel Singh
// September 2026
// DoublyLinkedList.cpp
// The file contains the class method definitions for the List class.
//=================================================

#include "DoublyLinkedList.h"
#include <cassert>
#include <iostream>
#include <stdlib.h>

using namespace std;

//=================================================
// Default constructor
// Constructs an empty doubly linked list
//=================================================
template <typename T> DoublyLinkedList<T>::DoublyLinkedList() {
  head = nullptr;
  tail = nullptr;
  stored_length = 0;
}

//=================================================
// Copy Constructor
// Constructs a list from another one
// Parameters:
//  mylist: The other list
//=================================================
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &mylist) {
  head = nullptr;
  tail = nullptr;
}

template <typename T> DoublyLinkedList<T>::~DoublyLinkedList<T>() {}

//=================================================
// operator=
// Assignment operator
// Parameters:
//  mylist: the other list
// Return Value:
//  Return Value
//=================================================
template <typename T>
DoublyLinkedList<T>
DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &mylist) {}

//=================================================
// append
// Appends to the doubly linked list in O(1) time using the tail pointer
// Parameters:
//  item: The item to append
// Return Value:
//  void
//=================================================
template <typename T> void DoublyLinkedList<T>::append(const T &item) {
  Node *n = new Node;

  n->val = item;
  n->next = nullptr;
  n->prev = nullptr;

  if (length() == 0) {
    assert(head == nullptr);
    assert(tail == nullptr);
    head = n;
    tail = n;
  } else {
    // The next pointer on the tail node should be null
    assert(tail->next == nullptr);
    n->prev = tail;
    tail->next = n;
    tail = n;
  }

  stored_length++;
}

//=================================================
// operator[]
// Get a list value at `index`. Traverse from the head. Or the tail if the list
// value is closer to it.
//
// Parameters:
//  index: The index to get
//=================================================
template <typename T> T &DoublyLinkedList<T>::operator[](int index) {
  return get_node_at_index(index)->val;
}

//=================================================
// insert
// Inserts a node with `item` at `index`
//
// Parameters:
//  item: the item to put on the node
//  index: the spot to put the node
//=================================================
template <typename T>
void DoublyLinkedList<T>::insert(const T &item, int index) {
  Node *new_node = new Node;
  new_node->val = item;

  if (length() == 0 || index == length()) {
    append(item);
  } else {
    Node *after = get_node_at_index(index);
    Node *before = after->prev;

    bool prepending = before == nullptr;
    if (prepending) {
      head = new_node;
      new_node->next = after;
      after->prev = new_node;
    } else {
      new_node->prev = before;

      new_node->next = after;

      before->next = new_node;

      after->prev = new_node;
    }

    stored_length++;
  }
}

template <typename T> void DoublyLinkedList<T>::remove(int index) {}

template <typename T>
DoublyLinkedList<T>
DoublyLinkedList<T>::operator+(const DoublyLinkedList<T> &mylist) const {}

//=================================================
// length()
// Returns the length of the list in O(1) time by having a bookkeeping variable
// automatically kepeing track of the length
//
// Return Value:
//  An int representing the length
//=================================================
template <typename T> int DoublyLinkedList<T>::length() const {
  return this->stored_length;
}

template <typename T> bool DoublyLinkedList<T>::isEmpty() const {}

template <typename T> void DoublyLinkedList<T>::clear() {}

//=================================================
// throw_on_invalid_index
// Throws a runtime_error on an invalid index
//
// Parameters:
//  The index to check
//=================================================
template <typename T>
void DoublyLinkedList<T>::throw_on_invalid_index(int index) {
  if (index < 0 || index >= length()) {
    throw runtime_error("`" + std::to_string(index) +
                        "` is invalid index for list of length " +
                        std::to_string(length()));
  }
}

//=================================================
// get_node_at_index
// Gets a node at a specific index, throwing if the index is invalid. Optimized
// to start from the head or tail, whichever is closest
//
// Parameters:
//  index: The index to get the node at
//=================================================
template <typename T>
typename DoublyLinkedList<T>::Node *
DoublyLinkedList<T>::get_node_at_index(int index) {
  throw_on_invalid_index(index);

  assert(head != nullptr);

  bool closer_to_tail = ((length() - 1) - index) < index;
  if (closer_to_tail) {
    Node *ptr = tail;
    for (int i = 1; i < length() - index; i++) {
      assert(ptr->prev != nullptr);
      ptr = ptr->prev;
    }

    return ptr;
  } else {
    Node *ptr = head;
    for (int i = 0; i < index; i++) {
      assert(ptr->next != nullptr);
      ptr = ptr->next;
    }

    return ptr;
  }
}
