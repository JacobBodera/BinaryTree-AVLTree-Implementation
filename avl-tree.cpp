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
// returns the balance factor of a node
int AVLTree::balanceFactor(Node *node) {

    if (node == NULL)
        return 0;

    return AVLTree::depthBelow(node->left) - AVLTree::depthBelow(node->right);
}
// creates a single left rotation at a node to balance the tree
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
// creates a single right rotation at a node to balance the tree
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

    x->right = root;
    root->left = treeX;

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
// creates a left right rotation at a node to balance the tree
bool AVLTree::leftRightRotation(Node *parentNode, bool isLeftChild)
{
    Node* root;

    if (parentNode == NULL)
        root = getRootNode();
    else
    if (isLeftChild)
        root = parentNode->left;
    else
        root = parentNode->right;

    Node* a = root->left;
    Node* b = a->right;
    Node* rightB = b->right;
    Node* leftB = b->left;

    b->left = a;
    a->right = leftB;
    b->right = root;
    root->left = rightB;

    if (parentNode != NULL) {
        if (isLeftChild)
            parentNode->left = b;
        else
            parentNode->right = b;
    }
    else{
        replaceRoot(b);
    }

    return true;
}
// creates a right left rotation at a node to balance the tree
bool AVLTree::rightLeftRotation(Node *parentNode, bool isLeftChild)
{
    Node* root;

    if (parentNode == NULL)
        root = getRootNode();
    else
    if (isLeftChild)
        root = parentNode->left;
    else
        root = parentNode->right;

    Node* a = root->right;
    Node* b = a->left;
    Node* rightB = b->right;
    Node* leftB = b->left;

    b->right = a;
    a->left = rightB;
    b->left = root;
    root->right = leftB;

    if (parentNode != NULL) {
        if (isLeftChild)
            parentNode->left = b;
        else
            parentNode->right = b;
    }
    else{
        replaceRoot(b);
    }

    return true;
}
// outputs a stack with all nodes in the path from the root to the node with val
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

// function run after each insert/remove. Check balance factor and parent to determine which rotation to perform, if any
bool AVLTree::updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val)
{
    bool isLeft;
    Node* parent;
    // uses the pathToNode to determine if the node is the left or right child of its parent
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
        if (balanceFactor(current) < -1 && balanceFactor(current->right) <= 0)
            singleLeftRotation(parent, isLeft);
        // SINGLE RIGHT
        if (balanceFactor(current) > 1 && balanceFactor(current->left) >= 0)
            singleRightRotation(parent, isLeft);
        // LEFT RIGHT
        if (balanceFactor(current) > 1 && balanceFactor(current->left) < 0)
            leftRightRotation(parent, isLeft);
        // RIGHT LEFT
        if (balanceFactor(current) < -1 && balanceFactor(current->right) > 0)
            rightLeftRotation(parent, isLeft);
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
