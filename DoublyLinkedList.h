//========================================================
// CS 271
// Fall 2025
// DoublyLinkedList.h
// This file contains the DoublyLinkedList class declaration.
// This is similar to your 173 Linked List project.
// But there are key differences! Review the assignment document
// carefully.
//========================================================

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

#ifndef LIST_H
#define LIST_H

template <class T> class DoublyLinkedList {
public:
  DoublyLinkedList();
  DoublyLinkedList(const DoublyLinkedList<T> &mylist);
  ~DoublyLinkedList();
  DoublyLinkedList<T> operator=(const DoublyLinkedList<T> &mylist);
  void append(const T &item);
  T &operator[](int index);
  void insert(const T &item, int index);
  void remove(int index);
  DoublyLinkedList<T> operator+(const DoublyLinkedList<T> &mylist) const;
  int length() const;
  bool isEmpty() const;
  void clear();
  void mergesort();
  void selectionSort();
  // void insertionSort();
  template <class U>
  friend DoublyLinkedList<U> merge(const DoublyLinkedList<U> &left,
                                   const DoublyLinkedList<U> &right);
  // Returns a string representation of the list to make testing easier
  std::string to_string() const {
    std::stringstream s;

    Node *ptr = nullptr;

    if (head != nullptr) {
      s << head->val;
      ptr = head->next;
    }

    while (ptr != nullptr) {
      s << " " << ptr->val;
      ptr = ptr->next;
    }

    return s.str();
  };

private:
  // Private members you will need, at minimum:
  // 1. a struct representing a Node
  // 		(Hint: what did a Node struct look like for a singly linked
  // list? 			what needs to change for a doubly linked list?)
  // 2. a pointer to the first Node in the list (head)
  // 3. a pointer to the last Node in the list (tail)
  // Fill in other private members as needed

  struct Node {
    T val;
    Node *next;
    Node *prev;
  };

  Node *head;
  Node *tail;
  int stored_length;

  void throw_on_invalid_index(int index);
  Node *get_node_at_index(int index);

  void copy_from(const DoublyLinkedList<T> &original);
};

#include "DoublyLinkedList.cpp"

#endif
