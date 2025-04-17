#include "binary_search_tree.h"
#include "tree_node.h"
#include <iostream>
#include <queue>
#include <functional>

// Helper declarations (file-local)
static TreeNode* removeNodeHelper(TreeNode* node, int key, bool& removed);
static int countNodes(TreeNode* node);

// Constructor: initialize empty tree
BinarySearchTree::BinarySearchTree()
    : root(nullptr) {}

// Destructor: delete entire tree
BinarySearchTree::~BinarySearchTree() {
    deleteTree(root);
}

// 1. addToTree - Insert a key into the BST
void BinarySearchTree::addToTree(int key) {
    if (!root) {
        root = new TreeNode(key);
        return;
    }
    TreeNode* parent = nullptr;
    TreeNode* curr = root;
    while (curr) {
        parent = curr;
        if (key < curr->key)
            curr = curr->left;
        else if (key > curr->key)
            curr = curr->right;
        else
            return; // no duplicates
    }
    if (key < parent->key)
        parent->left = new TreeNode(key);
    else
        parent->right = new TreeNode(key);
}

// 2. removeNode - Remove a specific key from the BST
bool BinarySearchTree::removeNode(int key) {
    bool removed = false;
    root = removeNodeHelper(root, key, removed);
    return removed;
}

// 3. getHeightOfTree - Get the height of the tree
int BinarySearchTree::getHeightOfTree() const {
    return getHeight(root);
}

// 4. getNumberOfTreeNodes - Get the total number of nodes in the tree
int BinarySearchTree::getNumberOfTreeNodes() const {
    return countNodes(root);
}

// 5. contains - Check if a key is in the BST
bool BinarySearchTree::contains(int key) const {
    TreeNode* curr = root;
    while (curr) {
        if (key == curr->key)
            return true;
        else if (key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return false;
}

// 6. getRoot - Getter for the root node of the tree
TreeNode* BinarySearchTree::getRoot() const {
    return root;
}

// 7. isEmpty - Check if a BST is empty
bool BinarySearchTree::isEmpty() const {
    return root == nullptr;
}

// 8. clear – Removes tree
void BinarySearchTree::clear() {
    deleteTree(root);
    root = nullptr;
}

// 9. printNodeFromTree- print the node from the binary search tree
void BinarySearchTree::printNodeFromTree(TreeNode* node) const {
    if (!node) {
        std::cout << "Node is null" << std::endl;
        return;
    }
    int subtreeCount = countNodes(node);
    int subtreeHeight = getHeight(node);
    std::cout << "Node key: " << node->key
              << ", Subtree size: " << subtreeCount
              << ", Height: " << subtreeHeight
              << std::endl;
}

// 10. printInorder- print the BST in an in-order traversal
void BinarySearchTree::printInOrder() const {
    std::cout << "Performing In-order traversal" << std::endl;
    printInOrderHelper(root);
}

// 11. printPreOrder– print the BST in a Pre-order traversal
void BinarySearchTree::printPreOrder() const {
    std::cout << "Performing Pre-order traversal" << std::endl;
    printPreOrderHelper(root);
}

// 12. printPostOrder - print the BST in a Post-order traversal
void BinarySearchTree::printPostOrder() const {
    std::cout << "Performing Post-order traversal" << std::endl;
    printPostOrderHelper(root);
}

// 13. printDepthFirst - print the BST in a depth-first-order traversal
void BinarySearchTree::printDepthFirst() const {
    std::cout << "Performing Depth First traversal" << std::endl;
    printPreOrderHelper(root);
}

// 14. printBreadthFirst- print the BST in a breadth-first-order traversal
void BinarySearchTree::printBreadthFirst() const {
    std::cout << "Performing Breadth First traversal" << std::endl;
    if (!root) return;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front(); q.pop();
        std::cout << "Node key: " << n->key << std::endl;
        if (n->left)  q.push(n->left);
        if (n->right) q.push(n->right);
    }
}

// 15. deleteTree - deletes the tree starting from the specified node
void BinarySearchTree::deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// 16. getHeight - helper function to calculate the height of a node
int BinarySearchTree::getHeight(TreeNode* node) const {
    if (!node) return 0;
    int lh = getHeight(node->left);
    int rh = getHeight(node->right);
    return 1 + (lh > rh ? lh : rh);
}

// 17. printInOrderHelper - helper function for recursive in-order traversal
void BinarySearchTree::printInOrderHelper(TreeNode* node) const {
    if (!node) return;
    printInOrderHelper(node->left);
    std::cout << "Node key: " << node->key << std::endl;
    printInOrderHelper(node->right);
}

// 18. printPreOrderHelper - helper function for recursive pre-order traversal
void BinarySearchTree::printPreOrderHelper(TreeNode* node) const {
    if (!node) return;
    std::cout << "Node key: " << node->key << std::endl;
    printPreOrderHelper(node->left);
    printPreOrderHelper(node->right);
}

// 19. printPostOrderHelper - helper function for recursive post-order traversal
void BinarySearchTree::printPostOrderHelper(TreeNode* node) const {
    if (!node) return;
    printPostOrderHelper(node->left);
    printPostOrderHelper(node->right);
    std::cout << "Node key: " << node->key << std::endl;
}

// File-local helper to remove a node
static TreeNode* removeNodeHelper(TreeNode* node, int key, bool& removed) {
    if (!node) return nullptr;
    if (key < node->key) {
        node->left = removeNodeHelper(node->left, key, removed);
    } else if (key > node->key) {
        node->right = removeNodeHelper(node->right, key, removed);
    } else {
        removed = true;
        // No child or single child cases
        if (!node->left) {
            TreeNode* tmp = node->right;
            delete node;
            return tmp;
        }
        if (!node->right) {
            TreeNode* tmp = node->left;
            delete node;
            return tmp;
        }
        // Two children: find in-order successor
        TreeNode* succ = node->right;
        while (succ->left) succ = succ->left;
        node->key = succ->key;
        node->right = removeNodeHelper(node->right, succ->key, removed);
    }
    return node;
}

// File-local helper to count nodes in a subtree
static int countNodes(TreeNode* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}
