#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

// Constructor to make a tree with a head node of val newval
BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    left = NULL;
    right = NULL;
}
// returns the depth of a node in the tree. The head node is at a depth of zero
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

BinarySearchTree::BinarySearchTree()
{
    root_ = NULL;
    size_ = 0;
}
// Destructor to delete all nodes in a tree
BinarySearchTree::~BinarySearchTree()
{
    recursiveDelete(root_);
}
// returns the number of nodes in a tree
unsigned int BinarySearchTree::size() const
{
    return size_;
}
// returns the maximum value in a tree
DataType BinarySearchTree::max() const
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
// returns the minimum value in a tree
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
// returns the maximum depth
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
// returns whether or not a value exists in the tree
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
// returns the root node of the tree
Node* BinarySearchTree::getRootNode()
{
    return root_;
}
// returns the memory adress of the root node
Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}
// inserts a value into the tree
bool BinarySearchTree::insert(DataType val)
{
    // checks to see if the tree is empty, if it is, it makes the root equal to val
    if (root_ == NULL) {
        Node* newNode = new Node(val);
        root_ = newNode;
        ++size_;
        return true;
    }

    Node* current = root_;
    Node* parent = root_;
    bool isLeft = true;

    // traverses through the tree to determine where to put the new value
    while (current) {
        // if the value already exists in the tree, return false
        if (val == current->val)
            return false;
        // if val is less than the current node, traverses to left
        else if (val < current->val) {
            parent = current;
            current = current->left;
            isLeft = true;
        }
        // if val is greater than the current node, traverses to right
        else {
            parent = current;
            current = current->right;
            isLeft = false;
        }
    }
    // adds the new value by checking whether it is the left or right child of its parent
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
// removes a value from the tree
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
// recursively deletes the tree
void BinarySearchTree::recursiveDelete(Node *node) {
    if (node != NULL) {
        if (node->left != NULL)
            recursiveDelete(node->left);
        if (node->right != NULL)
            recursiveDelete(node->right);
        delete node;
    }
}
// replaces the root node with a new node
void BinarySearchTree::replaceRoot(Node* node) {
    root_ = node;
}
