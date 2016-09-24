//  Subsetted from:
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 16-4.

/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryNode.h"
#include "NotFoundException.h"

template<typename ItemType, typename KeyType>
class BinarySearchTree
{
    private:
        BinaryNode<ItemType>* rootPtr;

        // Recursively deletes all nodes from the tree.
        void destroyTree(BinaryNode<ItemType>* subTreePtr);

        // Recursively finds where the given node should be placed and
        // inserts it in a leaf at that point.
        BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode);

        // Returns a pointer to the node containing the given value,
        // or nullptr if not found.
        BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const KeyType& target) const;

        // Recursive helper functions for public traversals.
        void inorderHelper(void visit(ItemType&), BinaryNode<ItemType>* subTreePtr) const;
        void preorderHelper(void visit(ItemType&), BinaryNode<ItemType>* subTreePtr) const;
        void postorderHelper(void visit(ItemType&), BinaryNode<ItemType>* subTreePtr) const;

        // Helper function for saving the tree to a file.
        void saveHelper(BinaryNode<ItemType>* subTreePtr, ofstream& outFile, std::string order);

        // Helper function for copy constructor.
        BinaryNode<ItemType>* copyHelper(const BinaryNode<ItemType>* subTreePtr);

        // Helper functions for removal of nodes.
        BinaryNode<ItemType>* removeHelper(BinaryNode<ItemType>* subTreePtr, const KeyType target, bool& success);
        BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* deletePtr);
        BinaryNode<ItemType>* findSuccessor(BinaryNode<ItemType>* nodeToDeletePtr, ItemType& inorderSucessor);

    public:
        //------------------------------------------------------------
        // Constructor and Destructor Section.
        //------------------------------------------------------------
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree<ItemType,KeyType>& tree);
        ~BinarySearchTree();

        //------------------------------------------------------------
        // Public Methods Section.
        //------------------------------------------------------------
        bool add(const ItemType& newEntry);
        ItemType getEntry(const KeyType& aKey) const throw(NotFoundException);
        bool contains(const KeyType& aKey) const;

        void save(ofstream& outFile, std::string order);
        void removeEntry(const KeyType& aKey) throw(NotFoundException);
        //------------------------------------------------------------
        // Public Traversals Section.
        //------------------------------------------------------------

        void inorderTraverse(void visit(ItemType&)) const;
        void preorderTraverse(void visit(ItemType&)) const;
        void postorderTraverse(void visit(ItemType&)) const;

}; // end BinarySearchTree

#include "BinarySearchTree.hpp"

#endif
