#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval) // good
{
    val = newval;
    left = NULL;
    right = NULL;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    int count = 0;

    if (n == root_)
        return count;

    Node* current = root_;

    while (current && current != n) {
        if (current->val < n->val)
            current = current->left;
        else
            current = current->right;
        ++count;
    }
    return count;
}

BinarySearchTree::BinarySearchTree() // good
{
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
    recursiveDelete(root_);
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
    if (root_->left == NULL && root_->right == NULL)
        return 0;

    queue<Node*> que;
    int depth = -1;

    que.push(root_);

    while (true) {
        int count = que.size();

        if (count == 0)
            return depth;
        depth++;

        while (count > 0) {
            Node* temp = que.front();
            que.pop();
            if (temp->left)
                que.push(temp->left);
            if (temp->right)
                que.push(temp->right);
            --count;
        }
    }
}

void BinarySearchTree::print(Node* node) const
{
    if (node->left != NULL)
        print(node->left);

    std::cout << node->val << " ";

    if (node->right != NULL)
        print(node->right);
}

bool BinarySearchTree::exists(DataType val) const
{
    if (root_ == NULL)
        return false;

    Node* current = root_;

    while (current) {
        if (val == current->val)
            return true;
        else if (val < current->val)
            current = current->left;
        else
            current = current->right;
    }
    return false;
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
    if (root_ == NULL) {
        Node* newNode = new Node(val);
        root_ = newNode;
        ++size_;
        return true;
    }

    Node* current = root_;
    Node* parent = root_;
    bool isLeft = true;

    while (current) {
        if (val == current->val)
            return false;
        else if (val < current->val) {
            parent = current;
            current = current->left;
            isLeft = true;
        }
        else {
            parent = current;
            current = current->right;
            isLeft = false;
        }
    }
    Node* newNode = new Node(val);
    if (isLeft)
        parent->left = newNode;
    else
        parent->right = newNode;

    ++size_;
    return true;
}

Node* findPredecessor(Node* ptr) {
    Node* pred = ptr;
    Node* parentOfPred = ptr;
    Node* current = ptr->left;

    while (current) {
        parentOfPred = pred;
        pred = current;
        current = current->right;
    }

    if (pred != ptr->left) {
        parentOfPred->right = pred->left;
        pred->left = ptr->left;
    }

    pred->right = ptr->right;
    return pred;
}

bool BinarySearchTree::remove(DataType val)
{
    Node* current = root_;
    Node* parent = root_;
    bool isLeft = false;

    if (!current)
        return false;

    // finding the node to be removed
    while (current && current->val != val) {
        parent = current;

        if (val < current->val) {
            current = current->left;
            isLeft = true;
        }
        else {
            current = current->right;
            isLeft = false;
        }
    }
    // if the node is not found
    if (!current)
        return false;
    // if the node is a leaf node
    if (current->left == NULL && current->right == NULL) {
        if (current == root_) {
            root_ = NULL;
        }
        else {
            if (isLeft)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        --size_;
        return true;
    }
    // doesn't have right child but has left
    else if (current->right == NULL) {
        if (current == root_)
            root_ = current->left;
        else {
            if (isLeft)
                parent->left = current->left;
            else
                parent->right = current->left;
        }
        --size_;
        return true;
    }
    // doesn't have left child but has right
    else if (current->left == NULL){
        if (current == root_)
            root_ = current->right;
        else {
            if (isLeft)
                parent->left = current->right;
            else
                parent->right = current->right;
        }
        --size_;
        return true;
    }

    else {
        Node* predecessor = findPredecessor(current);

        if (current == root_)
            root_ = predecessor;
        else if (isLeft)
            parent->left = predecessor;
        else
            parent->right = predecessor;
    }
    --size_;
    return true;
}

void BinarySearchTree::recursiveDelete(Node *node) {
    if (node != NULL) {
        if (node->left != NULL)
            recursiveDelete(node->left);
        if (node->right != NULL)
            recursiveDelete(node->right);
        delete node;
    }
}
