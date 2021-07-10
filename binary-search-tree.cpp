#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval) // good
{
    val = NULL;
    left = NULL;
    right = NULL;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    
}

BinarySearchTree::BinarySearchTree() // good
{
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() // good
{

}

unsigned int BinarySearchTree::size() const // good
{
    return size_;
}

DataType BinarySearchTree::max() const // good
{
    Node* current = root_;
    DataType max = 0;

    while (current)
    {
        max = current->val;
        current = current->right;
    }
    return max;
}

DataType BinarySearchTree::min() const // good
{
    Node* current = root_;
    DataType min = 0;

    while (current)
    {
        min = current->val;
        current = current->left;
    }
    return min;
}

unsigned int BinarySearchTree::depth() const
{
    
}

void BinarySearchTree::print() const
{
    
}

bool BinarySearchTree::exists(DataType val) const
{
    if (root_ == NULL)
        return false;

    Node* current = root_;

    for (int i = 0; i <= depth(); i++)
    {
        if (val == current->val)
            return true;
        else if (val < current->val)
        {
            if (current->left == NULL)
                return false;
            current = current->left;
        }
        else {
            if (current->right == NULL)
                return false;
            current = current->right;
        }
    }
}

Node* BinarySearchTree::getRootNode() // good
{
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress() // good
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    if (root_ = NULL) {
        root_->val = val;
        return true;
    }

    Node* current = root_;

    while (current) {
        if (val == current->val)
            return false;
        else if (val < current->val)
            current = current->left;
        else
            current = current->right;
    }
    current->val = val;
    return true;
}

Node* findPredecessor(Node* ptr) {
    
}

bool BinarySearchTree::remove(DataType val)
{
    
}
