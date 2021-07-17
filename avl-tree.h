#ifndef MTE140_A3_AVL_TREE_H
#define MTE140_A3_AVL_TREE_H

#include "binary-search-tree.h"
#include <stack>

class AVLTree: public BinarySearchTree
{
public:
    // Overriden insert and remove functions
    // Do not modify these definitions

    //The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);

    // Define additional functions and attributes below if you need
    int depthBelow(Node *n);
    std::stack<BinarySearchTree::Node*> *pathToNodeStack(DataType val);
    bool updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val);
    bool singleLeftRotation(Node *parentNode, bool isLeftChild);
    bool singleRightRotation(Node *parentNode, bool isLeftChild);
    bool leftRightRotation(Node *parentNode, bool isLeftChild);
    bool rightLeftRotation(Node *parentNode, bool isLeftChild);
    int balanceFactor(Node *node);

};

#endif //MTE140_A3_AVL_TREE_H
