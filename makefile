sorting_test: sorting_test.o
	g++ -o sorting_test sorting_test.o

sorting_test.o: DoublyLinkedList.h DoublyLinkedList.cpp
	g++ -c sorting_test.cpp

test: test_dll_example.o
	g++ -o test test_dll_example.o
	
test_dll_example.o: test_dll_example.cpp DoublyLinkedList.h DoublyLinkedList.cpp
	g++ -c test_dll_example.cpp
