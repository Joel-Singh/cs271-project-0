#include "DoublyLinkedList.h"
#include "test.cpp"
#include <iostream>

void mergesort_correctness_test();

int main() { mergesort_correctness_test(); }

void mergesort_correctness_test() {
  {
    DoublyLinkedList<int> dll;
    dll.mergesort();
    test("Mergesort: empty list stays empty", dll, "");
  }

  {
    DoublyLinkedList<int> dll;
    dll.append(1);
    dll.mergesort();
    test("Mergesort: single list stays same", dll, "1");
  }

  {
    DoublyLinkedList<int> dll;
    dll.append(2);
    dll.append(1);
    dll.mergesort();
    test("Mergesort: sorting two elements", dll, "1 2");
  }

  {
    DoublyLinkedList<int> dll;
    dll.append(3);
    dll.append(2);
    dll.append(1);
    dll.mergesort();
    test("Mergesort: sorting three elements", dll, "1 2 3");
  }

  {
    DoublyLinkedList<int> dll;
    dll.append(9);
    dll.append(4);
    dll.append(11);
    dll.append(10);
    dll.append(382);
    dll.append(3241);
    dll.append(120);
    dll.mergesort();
    test("Mergesort: sorting seven elements", dll, "4 9 10 11 120 382 3241");
  }
}
