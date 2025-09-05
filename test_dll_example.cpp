// *******************************************************
//
//  test_dll_example.cpp
//  CS 271 Doubly Linked List Project: Example Test Driver
//  Fall 2025
//  TO-DO: This set of tests is insufficient! What cases is
//  it missing? Do the elements in a doubly linked list
//  always need to be ints?
//
// *******************************************************

#include <chrono>
#include <iostream>
#include <stdexcept>

#include "DoublyLinkedList.h"
using std::cerr;
using std::cout; // more specific than using namespace std -- fewer
                 // opportunities for conflicts!
using std::endl;
using std::string;

//=================================================
// stringify
// Create a string from a string, number, or type implementing to_string
//
// Parameters:
//  value: value to convert
//=================================================
template <typename T> string stringify(const T &value) {
  if constexpr (std::is_arithmetic_v<T>) {
    return std::to_string(value);
  } else if constexpr (std::is_same_v<T, std::string>) {
    return value;
  } else {
    return value.to_string();
  }
}

template <typename T>
void test(std::string description, T &actual, std::string expected) {
  cout << "Running: `" << description << "`" << endl;
  if (stringify(actual) != expected) {
    cout << "FAILED: `" << description << "`" << endl;
    cout << "Expected: `" << expected << "`" << endl;
    cout << "Actual: `" << stringify(actual) << "`" << endl;

  } else {
    cout << "Successful: `" << description << "`" << endl;
  }
  cout << "------------------------------" << endl;
}

void test_append() {
  try {
    DoublyLinkedList<int> dll;
    dll.append(0);
    test("Append single int", dll, "0");

    dll.append(2);
    dll.append(-1);
    test("Append multiple numbers", dll, "0 2 -1");
  } catch (std::exception &e) {
    cerr << "Error appending to list : " << e.what() << endl;
  }

  try {
    DoublyLinkedList<string> dll;
    dll.append("heyo");
    test("Append single string", dll, "heyo");

    dll.append("its");
    dll.append("me");
    test("Append multiple strings", dll, "heyo its me");
  } catch (std::exception &e) {
    cerr << "Error appending to list : " << e.what() << endl;
  }
}

void test_indexing() {
  try {
    DoublyLinkedList<int> dll;
    dll.append(0);
    dll.append(2);
    dll.append(-1);

    test("Index at first int element", dll[0], "0");

    test("Index at second int element", dll[1], "2");

    test("Index at third int element", dll[2], "-1");

  } catch (std::exception &e) {
    cerr << "Error indexing in list (operator[]) : " << e.what() << endl;
  }

  try {
    DoublyLinkedList<string> dll;
    dll.append("Slayter");
    dll.append("Olin");
    dll.append("Higley");

    test("Index at first string element", dll[0], "Slayter");

    test("Index at second string element", dll[1], "Olin");

    test("Index at third string element", dll[2], "Higley");

  } catch (std::exception &e) {
    cerr << "Error indexing in list (operator[]) : " << e.what() << endl;
  }

  // Test for out-of-bounds handling -- what other methods need this kind of
  // test?
  try {
    DoublyLinkedList<int> dll;
    dll.append(0);
    dll.append(2);
    dll.append(-1);

    dll[-1];
    cerr << "Expected exception not thrown in operator[] for out of bounds "
            "index (-1)"
         << endl;

  } catch (std::exception &e) {
    cout << "Exception correctly thrown in operator[] for out of bounds index "
            "(-1) : "
         << e.what() << endl;
  }

  // Out of bounds in the positive direction
  try {
    DoublyLinkedList<int> dll;
    dll.append(0);
    dll.append(2);
    dll.append(-1);

    dll[5];
    cerr << "Expected exception not thrown in operator[] for out of bounds "
            "index (5)"
         << endl;

  } catch (std::exception &e) {
    cout << "Exception correctly thrown in operator[] for out of bounds index "
            "(5) : "
         << e.what() << endl;
  }
}

void test_insert() {
  try {
    DoublyLinkedList<int> dll;

    dll.insert(1, 0);
    test("Insert one element", dll, "1");

    dll.insert(2, 0);
    test("Insert multiple elements", dll, "2 1");

    dll.insert(-1, 1);
    test("Insert multiple elements", dll, "2 -1 1");

    dll.insert(5, 3);
    test("Insert multiple elements", dll, "2 -1 1 5");

  } catch (std::exception &e) {
    cerr << "Error inserting into list : " << e.what() << endl;
  }

  try {
    DoublyLinkedList<string> dll;

    dll.insert("Slayter", 0);
    test("Insert one element", dll, "Slayter");

    dll.insert("Higley", 0);
    test("Insert multiple elements", dll, "Higley Slayter");

    dll.insert("Barney", 1);
    test("Insert multiple elements", dll, "Higley Barney Slayter");

    dll.insert("Olin", 3);
    test("Insert multiple elements", dll, "Higley Barney Slayter Olin");

  } catch (std::exception &e) {
    cerr << "Error inserting into list : " << e.what() << endl;
  }

  // Test for out-of-bounds handling
  try {
    DoublyLinkedList<int> dll;
    dll.insert(0, 0);
    dll.insert(1, 1);
    dll.insert(2, 2);
    dll.insert(-1, -1);

    cerr << "Expected exception not thrown in insert for out of bounds "
            "index (-1)"
         << endl;

  } catch (std::exception &e) {
    cout << "Exception correctly thrown in insert for out of bounds index "
            "(-1) : "
         << e.what() << endl;
  }

  // Out of bounds in the positive direction
  try {
    DoublyLinkedList<int> dll;
    dll.insert(0, 0);
    dll.insert(1, 1);
    dll.insert(2, 2);
    dll.insert(99, 99);

    cerr << "Expected exception not thrown in insert for out of bounds "
            "index (99)"
         << endl;

  } catch (std::exception &e) {
    cout << "Exception correctly thrown in insert for out of bounds index "
            "(99) : "
         << e.what() << endl;
  }
}
//
// void test_remove() {
//   try {
//     DoublyLinkedList<int> dll;
//     dll.append(1);
//     dll.append(2);
//     dll.append(3);
//     dll.append(4);
//     dll.append(5);
//
//     dll.remove(0);
//     string dll_str = dll.to_string();
//     if (dll_str != "2 3 4 5") {
//       cout << "Incorrect remove result. Expected 2 3 4 5 but got : " <<
//       dll_str
//            << endl;
//     }
//
//     dll.remove(3);
//     dll_str = dll.to_string();
//     if (dll_str != "2 3 4") {
//       cout << "Incorrect remove result. Expected 2 3 4 but got : " << dll_str
//            << endl;
//     }
//
//     dll.remove(1);
//     dll_str = dll.to_string();
//     if (dll_str != "2 4") {
//       cout << "Incorrect remove result. Expected 2 4 but got : " << dll_str
//            << endl;
//     }
//
//   } catch (std::exception &e) {
//     cerr << "Error removing from list : " << e.what() << endl;
//   }
// }
//
// // Testing length after testing append and remove
// void test_length() {
//   try {
//     DoublyLinkedList<int> dll;
//     int n = dll.length();
//     if (n != 0) {
//       cout << "Incorrect length. Expected 0 but got : " << n << endl;
//     }
//     dll.append(6);
//     dll.append(5);
//     dll.append(4);
//     dll.append(3);
//     dll.append(2);
//     n = dll.length();
//     if (n != 5) {
//       cout << "Incorrect length. Expected 5 but got : " << n << endl;
//     }
//     dll.remove(4);
//     dll.remove(2);
//     n = dll.length();
//     if (n != 3) {
//       cout << "Incorrect length. Expected 3 but got : " << n << endl;
//     }
//   } catch (std::exception &e) {
//     cerr << "Error in determining length : " << e.what() << endl;
//   }
// }
//
// // Testing copy constructor after testing append, remove, and length
// void test_copy_constructor() {
//   try {
//     DoublyLinkedList<int> x;
//     x.append(0);
//     x.append(2);
//     x.append(-1);
//
//     DoublyLinkedList<int> y(x);
//     string dll_str = y.to_string();
//     if (dll_str != "0 2 -1") {
//       cout << "Incorrect copy constructor result. Expected 0 2 -1 but got : "
//            << dll_str << endl;
//     }
//
//     x.append(3);
//     y.append(9);
//
//     dll_str = y.to_string();
//     if (dll_str != "0 2 -1 9") {
//       cout << "Incorrect copy constructor result after append. Expected 0 2
//       -1 "
//               "9 but got : "
//            << dll_str << endl;
//     }
//
//     dll_str = x.to_string();
//     if (dll_str != "0 2 -1 3") {
//       cout << "Incorrect copy constructor result after append. Expected 0 2
//       -1 "
//               "3 but got : "
//            << dll_str << endl;
//     }
//
//     x.remove(0);
//     dll_str = y.to_string();
//     if (dll_str != "0 2 -1 9") {
//       cout << "Incorrect copy constructor result after remove. Expected 0 2
//       -1 "
//               "9 but got : "
//            << dll_str << endl;
//     }
//
//     dll_str = x.to_string();
//     if (dll_str != "2 -1 3") {
//       cout << "Incorrect copy constructor result after remove. Expected 2 -1
//       3 "
//               "but got : "
//            << dll_str << endl;
//     }
//
//   } catch (std::exception &e) {
//     cerr << "Error copying list : " << e.what() << endl;
//   }
// }
//
// // Testing assignment after testing append, remove, and length
// void test_assignment() {
//   try {
//     DoublyLinkedList<int> x;
//     x.append(0);
//     x.append(2);
//     x.append(-1);
//
//     DoublyLinkedList<int> y = x;
//     string dll_str = y.to_string();
//     if (dll_str != "0 2 -1") {
//       cout << "Incorrect assignment result. Expected 0 2 -1 but got : "
//            << dll_str << endl;
//     }
//
//     x.append(3);
//     y.append(9);
//
//     dll_str = y.to_string();
//     if (dll_str != "0 2 -1 9") {
//       cout << "Incorrect assignment result after append. Expected 0 2 -1 9
//       but "
//               "got : "
//            << dll_str << endl;
//     }
//
//     dll_str = x.to_string();
//     if (dll_str != "0 2 -1 3") {
//       cout << "Incorrect assignment result after append. Expected 0 2 -1 3
//       but "
//               "got : "
//            << dll_str << endl;
//     }
//
//     x.remove(0);
//     dll_str = y.to_string();
//     if (dll_str != "0 2 -1 9") {
//       cout << "Incorrect assignment result after remove. Expected 0 2 -1 9
//       but "
//               "got : "
//            << dll_str << endl;
//     }
//
//     dll_str = x.to_string();
//     if (dll_str != "2 -1 3") {
//       cout << "Incorrect assignment result after remove. Expected 2 -1 3 but
//       "
//               "got : "
//            << dll_str << endl;
//     }
//
//   } catch (std::exception &e) {
//     cerr << "Error assigning list : " << e.what() << endl;
//   }
// }
//
// void test_isEmpty() {
//   try {
//     DoublyLinkedList<int> dll;
//     if (!dll.isEmpty()) {
//       cout << "Empty list identified as non-empty" << endl;
//     }
//     dll.append(1);
//     dll.append(2);
//     if (dll.isEmpty()) {
//       cout << "Non-empty list identified as empty" << endl;
//     }
//     dll.remove(1);
//     if (dll.isEmpty()) {
//       cout << "Non-empty list identified as empty" << endl;
//     }
//     dll.remove(0);
//     if (!dll.isEmpty()) {
//       cout << "Empty list identified as non-empty" << endl;
//     }
//   } catch (std::exception &e) {
//     cerr << "Error in determining if list is empty : " << e.what() << endl;
//   }
// }
//
// void test_clear() {
//   try {
//     DoublyLinkedList<int> dll;
//     dll.append(1);
//     dll.append(2);
//
//     dll.clear();
//
//     if (!dll.isEmpty()) {
//       cout << "Cleared list identified as non-empty" << endl;
//     }
//     if (dll.length() != 0) {
//       cout << "Cleared list has length longer than 0" << endl;
//     }
//
//     dll.append(3);
//
//     if (dll.isEmpty()) {
//       cout << "List identified as empty after append following clear" <<
//       endl;
//     }
//     if (dll.length() != 1) {
//       cout << "Incorect length after clearing and appending. Expected 1 but "
//               "got : "
//            << dll.length() << endl;
//     }
//
//     string dll_str = dll.to_string();
//     if (dll_str != "3") {
//       cout << "Incorrect append after clearing. Expected 3 but got : "
//            << dll_str << endl;
//     }
//
//   } catch (std::exception &e) {
//     cerr << "Error in clearing list : " << e.what() << endl;
//   }
// }
//
// void test_concatenate() {
//   try {
//     DoublyLinkedList<int> x;
//     x.append(1);
//     x.append(2);
//     x.append(3);
//     x.append(4);
//
//     DoublyLinkedList<int> y;
//     y.append(7);
//     y.append(8);
//     y.append(9);
//
//     string dll_str = (x + y).to_string();
//
//     if (dll_str != "1 2 3 4 7 8 9") {
//       cout << "Incorrect concatenate. Expected 1 2 3 4 7 8 9 but got : "
//            << dll_str << endl;
//     }
//
//   } catch (std::exception &e) {
//     cerr << "Error in concatenating lists : " << e.what() << endl;
//   }
// }
//
// // Find the number of nanoseconds it takes to run each method when n is large
// // How can we use this to check if the time complexity is what we expect?
//
// void time_test() {
//   std::srand(std::time(0)); // seed random with current time
//   DoublyLinkedList<int> x;
//   // TO-DO: generate large list
//
//   int total = 0;
//
//   int val = std::rand() % 100000;
//   auto begin = std::chrono::high_resolution_clock::now();
//   x.append(val);
//   auto end = std::chrono::high_resolution_clock::now();
//   auto elapsed =
//       std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//   cout << "append time test took " << elapsed.count() << " nanoseconds" <<
//   endl; total += elapsed.count();
//
//   begin = std::chrono::high_resolution_clock::now();
//   int n = x.length();
//   end = std::chrono::high_resolution_clock::now();
//   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//   begin); cout << "length time test took " << elapsed.count() << "
//   nanoseconds" << endl; total += elapsed.count();
//
//   begin = std::chrono::high_resolution_clock::now();
//   x[n - 1];
//   end = std::chrono::high_resolution_clock::now();
//   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//   begin); cout << "indexing time test took " << elapsed.count() << "
//   nanoseconds"
//        << endl;
//   total += elapsed.count();
//
//   begin = std::chrono::high_resolution_clock::now();
//   x.remove(n - 1);
//   n--;
//   end = std::chrono::high_resolution_clock::now();
//   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//   begin); cout << "remove time test took " << elapsed.count() << "
//   nanoseconds" << endl; total += elapsed.count();
//
//   begin = std::chrono::high_resolution_clock::now();
//   x.insert(val, n);
//   n++;
//   end = std::chrono::high_resolution_clock::now();
//   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//   begin); cout << "insert time test took " << elapsed.count() << "
//   nanoseconds" << endl; total += elapsed.count();
//
//   begin = std::chrono::high_resolution_clock::now();
//   x.isEmpty();
//   end = std::chrono::high_resolution_clock::now();
//   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//   begin); cout << "isEmpty time test took " << elapsed.count() << "
//   nanoseconds"
//        << endl;
//   total += elapsed.count();
//
//   begin = std::chrono::high_resolution_clock::now();
//   x.clear();
//   end = std::chrono::high_resolution_clock::now();
//   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//   begin); cout << "clear time test took " << elapsed.count() << "
//   nanoseconds" << endl; total += elapsed.count();
//
//   begin = std::chrono::high_resolution_clock::now();
//   DoublyLinkedList<int> y(x);
//   end = std::chrono::high_resolution_clock::now();
//   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//   begin); cout << "copy constructor time test took " << elapsed.count()
//        << " nanoseconds" << endl;
//   total += elapsed.count();
//
//   begin = std::chrono::high_resolution_clock::now();
//   x + y;
//   end = std::chrono::high_resolution_clock::now();
//   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//   begin); cout << "concatenate time test took " << elapsed.count() << "
//   nanoseconds"
//        << endl;
//   total += elapsed.count();
//
//   begin = std::chrono::high_resolution_clock::now();
//   DoublyLinkedList<int> z = x;
//   end = std::chrono::high_resolution_clock::now();
//   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
//   begin); cout << "assignment time test took " << elapsed.count() << "
//   nanoseconds"
//        << endl;
//   total += elapsed.count();
//
//   cout << "Total time: " << total << endl;
// }

int main() {
  test_append();
  test_indexing();
  test_insert();
  // test_remove();
  // test_length();
  // test_copy_constructor();
  // test_assignment();
  // test_isEmpty();
  // test_clear();
  // test_concatenate();
  //
  // time_test();

  cout << "Testing completed" << endl;

  return 0;
}
