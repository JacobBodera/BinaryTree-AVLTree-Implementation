#include "avl-tree.h";
#include <cmath>
#include <stack>
#include <iostream>

using namespace std;

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

// check height of the node
int AVLTree::depthBelow(Node *n)
{
    if (n->left == NULL && n->right == NULL)
        return 1;

    int leftSub = 0;
    int rightSub = 0;

    if (n->left != NULL)
        leftSub = depthBelow(n->left);
    if (n->right != NULL)
        rightSub = depthBelow(n->right);

    if (leftSub > rightSub)
        return leftSub + 1;
    else
        return rightSub + 1;
}

int AVLTree::balanceFactor(Node *node) {
    if (node == NULL)
        return 0;

    return AVLTree::depthBelow(node->left) - AVLTree::depthBelow(node->right);
}

bool AVLTree::singleLeftRotation(Node *parentNode, bool isLeftChild)
{
        Node* root = BinarySearchTree::getRootNode();
    if (parentNode != NULL)
        Node* root = parentNode->right;
    Node* x = root->right;
    Node* treeX = x->left;

    x->left = root;
    root->right = treeX;
    if (parentNode != NULL) {
        if (isLeftChild)
            parentNode->left = x;
        else
            parentNode->right = x;
    }
    return true;
}

bool AVLTree::singleRightRotation(Node *parentNode, bool isLeftChild)
{
    Node* root = BinarySearchTree::getRootNode();
    if (parentNode != NULL)
        Node* root = parentNode->left;
    Node* x = root->left;
    Node* treeX = x->right;

    x->right = root;
    root->left = treeX;

    if (parentNode != NULL) {
        if (isLeftChild)
            parentNode->left = x;
        else
            parentNode->right = x;
    }
    return true;
}

bool AVLTree::leftRightRotation(Node *parentNode, bool isLeftChild)
{
    bool temp = isLeftChild;
    isLeftChild = true;
    AVLTree::singleLeftRotation(parentNode->left, isLeftChild);
    isLeftChild = temp;
    AVLTree::singleRightRotation(parentNode, isLeftChild);
}

bool AVLTree::rightLeftRotation(Node *parentNode, bool isLeftChild)
{
    bool temp = isLeftChild;
    isLeftChild = false;
    AVLTree::singleRightRotation(parentNode->right, isLeftChild);
    isLeftChild = temp;
    AVLTree::singleLeftRotation(parentNode, isLeftChild);
    
}

std::stack<BinarySearchTree::Node*> *AVLTree::pathToNodeStack(DataType val)
{
    stack<Node *> *stk;

    Node* current = getRootNode();

    while (current && current->val != val) {
         if (val < current->val) {
             stk->push(current);
             current = current->left;
         }
         else {
             stk->push(current);
             current = current->right;
         }
    }
    return stk;
}


bool AVLTree::updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val)
{
    bool isLeft;
    Node* parent;

    while (pathToNode->size() != 0) {
        Node* current = pathToNode->top();
        pathToNode->pop();

        if (current == getRootNode()) {
            isLeft = false;
            parent = NULL;
        }
        else {
            if (pathToNode->top()->left == current) {
                isLeft = true;
                parent = pathToNode->top();
            }
            else {
                isLeft = false;
                parent = pathToNode->top();
            }
        }

        // SINGLE LEFT
        if (balanceFactor(current) > 1 && balanceFactor(current->left) > 0)
            singleLeftRotation(parent, isLeft);
        // SINGLE RIGHT
        if (balanceFactor(current) < -1 && balanceFactor(current->left) < 0)
            singleRightRotation(parent, isLeft);
        // LEFT RIGHT
        if (balanceFactor(current) > 1 && balanceFactor(current->left) < 0)
            leftRightRotation(parent, isLeft);
        // RIGHT LEFT
        if (balanceFactor(current) < -1 && balanceFactor(current->left) > 0)
            rightLeftRotation(parent, isLeft);
    }
    return true;
}

bool AVLTree::insert(DataType val)
{
    BinarySearchTree::insert(val);

    updateNodeBalance(pathToNodeStack(val), val);

    return true;
}

bool AVLTree::remove(DataType val)
{
    BinarySearchTree::remove(val);

    updateNodeBalance(pathToNodeStack(val), val);

    return true;
}
