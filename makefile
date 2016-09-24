Lab10: main.o DictionaryDriver.o DictionaryEntry.o NotFoundException.o
	g++ -std=c++11 -g -Wall main.o DictionaryDriver.o DictionaryEntry.o NotFoundException.o -o Lab10

main.o: main.cpp BinaryNode.h BinaryNode.hpp DictionaryDriver.h DictionaryDriver.cpp DictionaryEntry.h DictionaryEntry.cpp BinarySearchTree.h BinarySearchTree.hpp NotFoundException.h NotFoundException.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

DictionaryDriver.o: BinaryNode.h BinaryNode.hpp BinarySearchTree.h BinarySearchTree.hpp NotFoundException.h NotFoundException.cpp DictionaryEntry.h DictionaryEntry.cpp DictionaryDriver.h DictionaryDriver.cpp
	g++ -std=c++11 -g -Wall -c DictionaryDriver.cpp
	
DictionaryEntry.o: DictionaryEntry.h DictionaryEntry.cpp
	g++ -std=c++11 -g -Wall -c DictionaryEntry.cpp

NotFoundException.o: NotFoundException.h NotFoundException.cpp
	g++ -std=c++11 -g -Wall -c NotFoundException.cpp

clean: 
	rm *.o Lab10
