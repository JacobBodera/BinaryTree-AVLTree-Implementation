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
    if (n == NULL)
        return 0;

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

int AVLTree::balanceFactor(Node *node) { // good

    if (node == NULL)
        return 0;

    return AVLTree::depthBelow(node->left) - AVLTree::depthBelow(node->right);
}

bool AVLTree::singleLeftRotation(Node *parentNode, bool isLeftChild)
{
    Node* root;

    if (parentNode == NULL)
        root = getRootNode();
    else
        if (isLeftChild)
             root = parentNode->left;
        else
            root = parentNode->right;

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
    else{
        replaceRoot(x);
    }

    return true;
}

bool AVLTree::singleRightRotation(Node *parentNode, bool isLeftChild)
{
    Node* root;

    if (parentNode == NULL)
        root = getRootNode();
    else
    if (isLeftChild)
        root = parentNode->left;
    else
        root = parentNode->right;

    Node* x = root->left;
    Node* treeX = x->right;

    root->left = treeX;
    x->right = root;

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
    //singleLeftRotation(parentNode->left, isLeftChild);
    isLeftChild = temp;
    //singleRightRotation(parentNode, isLeftChild);
}

bool AVLTree::rightLeftRotation(Node *parentNode, bool isLeftChild)
{
    bool temp = isLeftChild;
    isLeftChild = false;
    //singleRightRotation(parentNode->right, isLeftChild);
    isLeftChild = temp;
    //singleLeftRotation(parentNode, isLeftChild);
    
}

std::stack<BinarySearchTree::Node*> *AVLTree::pathToNodeStack(DataType val)
{
    stack<Node*> *stk = new stack<Node*> ;

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
        if (balanceFactor(current) < -1 && balanceFactor(current->right) < 0)
            singleLeftRotation(parent, isLeft);
        // SINGLE RIGHT
        /*
        if (balanceFactor(current) > 1 && balanceFactor(current->left) > 0)
            singleRightRotation(parent, isLeft);
        // LEFT RIGHT
        if (balanceFactor(current) > 1 && balanceFactor(current->left) < 0)
            leftRightRotation(parent, isLeft);
        // RIGHT LEFT
        if (balanceFactor(current) < -1 && balanceFactor(current->right) > 0)
            rightLeftRotation(parent, isLeft);
            */
    }
    delete pathToNode;
    return true;
}

bool AVLTree::insert(DataType val) // good
{
    BinarySearchTree::insert(val);

    return updateNodeBalance(pathToNodeStack(val), val);
}

bool AVLTree::remove(DataType val) // good
{
    BinarySearchTree::remove(val);

    return updateNodeBalance(pathToNodeStack(val), val);
}
