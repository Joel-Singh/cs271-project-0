//=================================================
// Joel Singh
// September 2026
// DoublyLinkedList.cpp
// The file contains the class method definitions for the DoublyLinkedList
// class.
//=================================================

#include "DoublyLinkedList.h"
#include <cassert>
#include <iostream>
#include <stdlib.h>

using namespace std;

//=================================================
// copy_from
// Copies original
//
// Parameters:
//  original: What to copy
//=================================================

template <typename T>
void DoublyLinkedList<T>::copy_from(const DoublyLinkedList<T> &original) {
  clear();

  if (original.length() == 0) {
    return;
  }

  stored_length = 1;

  Node *ptr = original.head;

  Node *new_node = new Node;
  new_node->val = ptr->val;
  new_node->next = nullptr;
  new_node->prev = nullptr;

  head = new_node;

  while (ptr->next != nullptr) {
    Node *before = new_node;

    new_node = new Node;
    new_node->val = ptr->next->val;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    new_node->prev = before;
    before->next = new_node;

    ptr = ptr->next;
    stored_length++;
  }

  tail = new_node;
}

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
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &mylist)
    : DoublyLinkedList() {
  copy_from(mylist);
}

template <typename T> DoublyLinkedList<T>::~DoublyLinkedList<T>() { clear(); }

//=================================================
// operator=
// Assignment operator
// Parameters:
//  mylist: the other list to assign from
//=================================================
template <typename T>
DoublyLinkedList<T>
DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &mylist) {
  copy_from(mylist);
  return *this;
}

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
    assert(tail != nullptr);

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
// value is closer to it. Throws on invalid `index`.
//
// Parameters:
//  index: The index to get
//=================================================
template <typename T> T &DoublyLinkedList<T>::operator[](int index) {
  return get_node_at_index(index)->val;
}

//=================================================
// insert
// Inserts a node with `item` at `index`. Throws on invalid `index``
//
// Parameters:
//  item: the item to put on the node
//  index: the spot to put the node
//=================================================
template <typename T>
void DoublyLinkedList<T>::insert(const T &item, int index) {
  if (length() == 0 || index == length()) {
    append(item);
  } else {
    Node *new_node = new Node;
    new_node->val = item;
    new_node->prev = nullptr;
    new_node->next = nullptr;

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

//=================================================
// remove
// Removes a node at index, throws on invalid index.
//
// Parameters:
//  index: Index of node to remove
//=================================================
template <typename T> void DoublyLinkedList<T>::remove(int index) {
  Node *to_remove = get_node_at_index(index);

  Node *before = to_remove->prev;
  Node *after = to_remove->next;

  bool is_head = before == nullptr;
  if (is_head) {
    head = after;
  } else {
    before->next = after;
  }

  bool is_tail = after == nullptr;
  if (is_tail) {
    tail = before;
  } else {
    after->prev = before;
  }

  delete to_remove;

  stored_length--;
}

//=================================================
// operator+
// Concatenation operator
//
// Parameters:
//  mylist, the list to concatenate
//=================================================
template <typename T>
DoublyLinkedList<T>
DoublyLinkedList<T>::operator+(const DoublyLinkedList<T> &mylist) const {
  DoublyLinkedList<T> a(*this);
  DoublyLinkedList<T> b(mylist);

  Node *ptr = b.head;
  while (ptr != nullptr) {
    // Okay to use append because it is O(1)
    a.append(ptr->val);
    ptr = ptr->next;
  }

  return a;
}

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

template <typename T> bool DoublyLinkedList<T>::isEmpty() const {
  return stored_length == 0;
}

template <typename T> void DoublyLinkedList<T>::clear() {
  Node *next = head;
  while (next != nullptr) {
    next = head->next;
    delete head;
    head = next;
  }

  head = nullptr;
  tail = nullptr;

  stored_length = 0;
}

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

//=================================================
// merge
// Merges two lists together, helper function for mergesort
//
// Parameters:
//  left: left list
//  right: right list
//
// Return Value:
//  The merged list
//=================================================
template <typename T>
DoublyLinkedList<T> merge(const DoublyLinkedList<T> &left,
                          const DoublyLinkedList<T> &right) {
  using Node = typename DoublyLinkedList<T>::Node;

  DoublyLinkedList<T> merged;

  Node *left_ptr = left.head;
  Node *right_ptr = right.head;

  while ((left_ptr != nullptr) && (right_ptr != nullptr)) {
    if (left_ptr->val <= right_ptr->val) {
      merged.append(left_ptr->val);
      left_ptr = left_ptr->next;
    } else {
      merged.append(right_ptr->val);
      right_ptr = right_ptr->next;
    }
  }

  if (left_ptr != nullptr) {
    while (left_ptr != nullptr) {
      merged.append(left_ptr->val);
      left_ptr = left_ptr->next;
    }
  } else {
    while (right_ptr != nullptr) {
      merged.append(right_ptr->val);
      right_ptr = right_ptr->next;
    }
  }

  return merged;
}

//=================================================
// mergesort
// Sorts the doubly linked list via mergesort
//=================================================
template <typename T> void DoublyLinkedList<T>::mergesort() {
  int n = length();

  if (n > 1) {
    int mid = n / 2;

    DoublyLinkedList<T> left;
    DoublyLinkedList<T> right;

    Node *ptr = head;
    for (int i = 0; i < mid; i++) {
      assert(ptr != nullptr);

      left.append(ptr->val);
      ptr = ptr->next;
    }

    while (ptr != nullptr) {
      right.append(ptr->val);
      ptr = ptr->next;
    }

    left.mergesort();
    right.mergesort();
    *this = merge(left, right);
  }
}

//=================================================
// selectionSort
// Sort the douby linked list via selectionSort
//=================================================
template <typename T> void DoublyLinkedList<T>::selectionSort() {
  Node *ptr = head;

  while (ptr != nullptr) {
    Node *smallest = ptr;
    Node *finding_smallest = ptr->next;

    while (finding_smallest != nullptr) {
      if (finding_smallest->val < smallest->val) {
        smallest = finding_smallest;
      }
      finding_smallest = finding_smallest->next;
    }

    // Swap
    int temp = ptr->val;
    ptr->val = smallest->val;
    smallest->val = temp;

    ptr = ptr->next;
  }
}
