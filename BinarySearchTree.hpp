//  Subsetted from:
//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file BinarySearchTree.cpp */

#include <iostream>

// PRIVATE HELPER METHODS - IMPLEMENT THESE

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
    if(subTreePtr->getLeftChildPtr())
    {
        destroyTree(subTreePtr->getLeftChildPtr());
    }
    if(subTreePtr->getRightChildPtr())
    {
        destroyTree(subTreePtr->getRightChildPtr());
    }
    delete subTreePtr;
}

template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType,KeyType>::insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr)
{
    if (!subTreePtr)
    {
        return newNodePtr;
    }
    else if (subTreePtr->getItem() > newNodePtr->getItem())
    {
        BinaryNode<ItemType>* tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else
    {
        BinaryNode<ItemType>* tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType, KeyType>::findNode(BinaryNode<ItemType>* subTreePtr, const KeyType& target) const
{
    if(!subTreePtr)
    {
        return nullptr;
    }
    else if (subTreePtr->getItem() == target)
    {
        return subTreePtr;
    }
    else if (subTreePtr->getItem() < target)
    {
        return findNode(subTreePtr->getRightChildPtr(), target);
    }
    else
    {
        return findNode(subTreePtr->getLeftChildPtr(), target);
    }
}

// Traversal helpers.
template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::inorderHelper(void visit(ItemType&), BinaryNode<ItemType>* subTreePtr) const
{
    if(subTreePtr)
    {
        inorderHelper(visit, subTreePtr->getLeftChildPtr());
        ItemType item = subTreePtr->getItem();
        visit(item);
        inorderHelper(visit, subTreePtr->getRightChildPtr());
    }
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::preorderHelper(void visit(ItemType&), BinaryNode<ItemType>* subTreePtr) const
{
    if(subTreePtr)
    {
        ItemType item = subTreePtr->getItem();
        visit(item);
        preorderHelper(visit, subTreePtr->getLeftChildPtr());
        preorderHelper(visit, subTreePtr->getRightChildPtr());
    }
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::postorderHelper(void visit(ItemType&), BinaryNode<ItemType>* subTreePtr) const
{
    if(subTreePtr)
    {
        postorderHelper(visit, subTreePtr->getLeftChildPtr());
        postorderHelper(visit, subTreePtr->getRightChildPtr());
        ItemType item = subTreePtr->getItem();
        visit(item);
    }
}

// Save helper function.
template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::saveHelper(BinaryNode<ItemType>* subTreePtr, ofstream& outFile, std::string order)
{
    if(order == "inorder")
    {
        if(subTreePtr)
        {
            saveHelper(subTreePtr->getLeftChildPtr(), outFile, order);
            ItemType item = subTreePtr->getItem();
            outFile << item;
            saveHelper(subTreePtr->getRightChildPtr(), outFile, order);
        }
    }
    else if(order == "preorder")
    {
        if(subTreePtr)
        {
            ItemType item = subTreePtr->getItem();
            outFile << item;
            saveHelper(subTreePtr->getLeftChildPtr(), outFile, order);
            saveHelper(subTreePtr->getRightChildPtr(), outFile, order);
        }
    }
    else if(order == "postorder")
    {
        if(subTreePtr)
        {
            saveHelper(subTreePtr->getLeftChildPtr(), outFile, order);
            saveHelper(subTreePtr->getRightChildPtr(), outFile, order);
            ItemType item = subTreePtr->getItem();
            outFile << item;
        }
    }
    else
    {
        std::cout << "Invalid input, please try again." << '\n';
    }
}

// Copy helper function.
template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType, KeyType>::copyHelper(const BinaryNode<ItemType>* subTreePtr)
{
    BinaryNode<ItemType>* newNodePtr = nullptr;

    if(subTreePtr)
    {
        newNodePtr = new BinaryNode<ItemType>(subTreePtr->getItem());
        newNodePtr->setLeftChildPtr(copyHelper(subTreePtr->getLeftChildPtr()));
        newNodePtr->setRightChildPtr(copyHelper(subTreePtr->getRightChildPtr()));
    }

    return newNodePtr;
}

// Removal Helper Functions
template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType, KeyType>::removeHelper(BinaryNode<ItemType>* subTreePtr, const KeyType target, bool& isRemoved)
{
    if(!subTreePtr)
    {
        isRemoved = false;
        return nullptr;
    }
    else if(subTreePtr->getItem() == target)
    {
        subTreePtr = removeNode(subTreePtr);
        isRemoved = true;
        return subTreePtr;
    }
    else if (subTreePtr->getItem() > target)
    {
        BinaryNode<ItemType>* newNodePtr = removeHelper(subTreePtr->getLeftChildPtr(), target, isRemoved);
        subTreePtr->setLeftChildPtr(newNodePtr);
        return subTreePtr;
    }
    else
    {
        BinaryNode<ItemType>* newNodePtr = removeHelper(subTreePtr->getRightChildPtr(), target, isRemoved);
        subTreePtr->setRightChildPtr(newNodePtr);
        return subTreePtr;
    }
}

template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType, KeyType>::removeNode(BinaryNode<ItemType>* deletePtr)
{
    // No children.
    if(deletePtr->isLeaf())
    {
        delete deletePtr;
        deletePtr = nullptr;
    }
    // Exactly one child - connect previous node to smallest child node.
    else if(!(deletePtr->getLeftChildPtr() && deletePtr->getRightChildPtr()))
    {
        BinaryNode<ItemType>* connectPtr;
        if(deletePtr->getLeftChildPtr())
        {
            connectPtr = deletePtr->getLeftChildPtr();
        }
        else
        {
            connectPtr = deletePtr->getRightChildPtr();
        }
        delete deletePtr;
        deletePtr = nullptr;
        return connectPtr;
    }
    // Two children - find smallest node in right subtree, replace desired node.
    else
    {
        ItemType inorderSuccessor;
        BinaryNode<ItemType>* tempPtr = findSuccessor(deletePtr->getRightChildPtr(), inorderSuccessor);
        deletePtr->setRightChildPtr(tempPtr);
        deletePtr->setItem(inorderSuccessor);
    }

    return deletePtr;
}

template<typename ItemType, typename KeyType>
BinaryNode<ItemType>* BinarySearchTree<ItemType, KeyType>::findSuccessor(BinaryNode<ItemType>* deletePtr, ItemType& inorderSuccessor)
{
    if(!deletePtr->getLeftChildPtr())
    {
        // Must be smallest node.
        inorderSuccessor = deletePtr->getItem();
        return removeNode(deletePtr);
    }

    deletePtr->setLeftChildPtr(findSuccessor(deletePtr->getLeftChildPtr(), inorderSuccessor));
    return deletePtr;
}

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

template<typename ItemType, typename KeyType>
BinarySearchTree<ItemType, KeyType>::BinarySearchTree() : rootPtr(nullptr)
{
}

template<typename ItemType, typename KeyType>
BinarySearchTree<ItemType, KeyType>::BinarySearchTree(const BinarySearchTree<ItemType, KeyType>& tree)
{
    rootPtr = copyHelper(tree.rootPtr);
}

template<typename ItemType, typename KeyType>
BinarySearchTree<ItemType, KeyType>::~BinarySearchTree()
{
   destroyTree(rootPtr);
}  // end destructor


//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section - IMPLEMENT THESE
//////////////////////////////////////////////////////////////

template<typename ItemType, typename KeyType>
bool BinarySearchTree<ItemType, KeyType>::add(const ItemType& newData)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
    rootPtr = insertInorder(rootPtr,newNodePtr);
	return true;
}

template<typename ItemType, typename KeyType>
ItemType BinarySearchTree<ItemType, KeyType>::getEntry(const KeyType& aKey) const throw(NotFoundException)
{
    BinaryNode<ItemType>* newNodePtr = findNode(rootPtr,aKey);
    if(!newNodePtr)
    {
        throw NotFoundException("Item not found.");
    }
    return newNodePtr->getItem();
}

template<typename ItemType, typename KeyType>
bool BinarySearchTree<ItemType, KeyType>::contains(const KeyType& aKey) const
{
    if(!findNode(rootPtr,aKey))
    {
        return false;
    }
    return true;
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::save(ofstream& outFile, std::string order)
{
    saveHelper(rootPtr, outFile, order);
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::removeEntry(const KeyType& aKey) throw(NotFoundException)
{
    bool isRemoved = false;
    rootPtr = removeHelper(rootPtr, aKey, isRemoved);
    if (!isRemoved)
    {
        throw NotFoundException("Item not found.");
    }
}

//////////////////////////////////////////////////////////////
//      Public Traversals Section - IMPLEMENT THESE
//////////////////////////////////////////////////////////////

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::inorderTraverse(void visit(ItemType&)) const
{
    inorderHelper(visit, rootPtr);
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::preorderTraverse(void visit(ItemType&)) const
{
    preorderHelper(visit, rootPtr);
}

template<typename ItemType, typename KeyType>
void BinarySearchTree<ItemType, KeyType>::postorderTraverse(void visit(ItemType&)) const
{
    postorderHelper(visit, rootPtr);
}
