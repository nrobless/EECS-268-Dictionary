/*
*	File : DictionaryEntry.h
*	Author :  Nicholas Robless
*	Date : 4/22/2016
*	Purpose : Header file of DictionaryDriver. Used to create and modify a BST full of DictionaryEntry items according to user input.
*/

#ifndef DICTIONARYDRIVER_H
#define DICTIONARYDRIVER_H

#include <iostream>
#include <fstream>
#include <string>

#include "BinarySearchTree.h"
#include "DictionaryEntry.h"
#include "NotFoundException.h"

// Global functions.
std::istream& operator>>(std::istream& is, DictionaryEntry& dict);
std::ostream& operator<<(std::ostream& os, const DictionaryEntry& dict);
void visit(std::string& aKey);
void visit(DictionaryEntry& anItem);

class DictionaryDriver
{
    private:
        bool treeCopied;
        BinarySearchTree<DictionaryEntry, std::string> bst;
        BinarySearchTree<DictionaryEntry, std::string>* copyBst;

        std::string convertWord(std::string str);
        void printMenu();
        void save(std::string order, std::string tree, ofstream& outFile);

        void testAdd(BinarySearchTree<DictionaryEntry, std::string> dictionary);
        void testRemove(BinarySearchTree<DictionaryEntry, std::string> dictionary);
        void testWriteToFile(BinarySearchTree<DictionaryEntry, std::string> dictionary);

    public:
        DictionaryDriver();
        ~DictionaryDriver();

        void createTree(std::string filename);
        void run();
};

#endif
