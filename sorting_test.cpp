#include "DoublyLinkedList.h"
#include "string"
#include "test.cpp"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = filesystem;

enum class SortingMethods { MergeSort };

void mergesort_correctness_test();
void sorting_efficiency_test(fs::path data_file, SortingMethods sorting_method);

int main() {
  mergesort_correctness_test();

  string datafiles[] = {
      "./data/randomizedData/10.in",     "./data/randomizedData/100.in",
      "./data/randomizedData/1000.in",   "./data/randomizedData/10000.in",
      "./data/randomizedData/100000.in", "./data/reversedData/10.in",
      "./data/reversedData/100.in",      "./data/reversedData/1000.in",
      "./data/reversedData/10000.in",    "./data/reversedData/100000.in",
      "./data/sortedData/10.in",         "./data/sortedData/100.in",
      "./data/sortedData/1000.in",       "./data/sortedData/10000.in",
      "./data/sortedData/100000.in"};

  SortingMethods sorting_methods[] = {SortingMethods::MergeSort};

  for (SortingMethods method : sorting_methods) {
    for (string file : datafiles) {
      sorting_efficiency_test(file, method);
    }
  }
}

void sorting_efficiency_test(fs::path data_file,
                             SortingMethods sorting_method) {
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

  string sorting_method_str;
  if (sorting_method == SortingMethods::MergeSort) {
    dll.mergesort();
    sorting_method_str = "Mergesort";
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

  cout << "`" << data_file << "`" << " took " << elapsed.count()
       << " nanoseconds to sort using " << sorting_method_str << endl;
}

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
