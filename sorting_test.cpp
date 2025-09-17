#include "DoublyLinkedList.h"
#include "string"
#include "test.cpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = filesystem;

enum class SortingMethods { MergeSort };

void sort_correctness_test(SortingMethods method);
void sorting_efficiency_test(fs::path data_file, SortingMethods sorting_method);
template <typename T>
void sort_based_on_method(DoublyLinkedList<T> &dll, SortingMethods method);
string method_to_string(SortingMethods method);

int main() {
  SortingMethods sorting_methods[] = {SortingMethods::MergeSort};
  for (SortingMethods method : sorting_methods) {
    sort_correctness_test(method);
  }

  string datafiles[] = {
      "./data/randomizedData/10.in",     "./data/randomizedData/100.in",
      "./data/randomizedData/1000.in",   "./data/randomizedData/10000.in",
      "./data/randomizedData/100000.in", "./data/reversedData/10.in",
      "./data/reversedData/100.in",      "./data/reversedData/1000.in",
      "./data/reversedData/10000.in",    "./data/reversedData/100000.in",
      "./data/sortedData/10.in",         "./data/sortedData/100.in",
      "./data/sortedData/1000.in",       "./data/sortedData/10000.in",
      "./data/sortedData/100000.in"};

  for (SortingMethods method : sorting_methods) {
    for (string file : datafiles) {
      sorting_efficiency_test(file, method);
    }
  }
}

void sorting_efficiency_test(fs::path data_file, SortingMethods method) {
  ifstream in(data_file); // the in flag is optional
  if (!in.is_open()) {
    cerr << "Failed  to open " << data_file << endl;
    exit(0);
  }

  DoublyLinkedList<int> dll;
  string line;
  while (getline(in, line)) {
    dll.append(stoi(line));
  }

  auto begin = std::chrono::high_resolution_clock::now();

  sort_based_on_method(dll, method);

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

  cout << "`" << data_file << "`" << " took " << elapsed.count()
       << " nanoseconds to sort using " << method_to_string(method) << endl;
}

void sort_correctness_test(SortingMethods method) {
  {
    DoublyLinkedList<int> dll;
    sort_based_on_method(dll, method);
    test(method_to_string(method) + " : empty list stays empty", dll, "");
  }

  {
    DoublyLinkedList<int> dll;
    dll.append(1);
    sort_based_on_method(dll, method);
    test(method_to_string(method) + " : single list stays same", dll, "1");
  }

  {
    DoublyLinkedList<int> dll;
    dll.append(2);
    dll.append(1);
    sort_based_on_method(dll, method);
    test(method_to_string(method) + " : sorting two elements", dll, "1 2");
  }

  {
    DoublyLinkedList<int> dll;
    dll.append(3);
    dll.append(2);
    dll.append(1);
    sort_based_on_method(dll, method);
    test(method_to_string(method) + " : sorting three elements", dll, "1 2 3");
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
    sort_based_on_method(dll, method);
    test(method_to_string(method) + " : sorting seven elements", dll,
         "4 9 10 11 120 382 3241");
  }
}

template <typename T>
void sort_based_on_method(DoublyLinkedList<T> &dll, SortingMethods method) {
  if (method == SortingMethods::MergeSort) {
    dll.mergesort();
  } else {
    throw runtime_error("Missing branch");
  }
}

string method_to_string(SortingMethods method) {
  if (method == SortingMethods::MergeSort) {
    return "Mergesort";
  } else {
    throw runtime_error("Missing branch");
  }
}
