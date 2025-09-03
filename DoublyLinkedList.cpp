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

  if (tail == nullptr) {
    // Head should also be null
    assert(head == nullptr);
    this->head = n;
    this->tail = n;
  } else {
    // The next pointer on the tail node should be null
    assert(tail->next == nullptr);
    n->prev = tail;
    tail->next = n;
    tail = n;
  }
}

template <typename T> T &DoublyLinkedList<T>::operator[](int index) {}

template <typename T>
void DoublyLinkedList<T>::insert(const T &item, int index) {}

template <typename T> void DoublyLinkedList<T>::remove(int index) {}

template <typename T>
DoublyLinkedList<T>
DoublyLinkedList<T>::operator+(const DoublyLinkedList<T> &mylist) const {}

template <typename T> int DoublyLinkedList<T>::length() const {}

template <typename T> bool DoublyLinkedList<T>::isEmpty() const {}

template <typename T> void DoublyLinkedList<T>::clear() {}
