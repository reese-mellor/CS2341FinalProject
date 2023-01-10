#ifndef AVL_TREE_H
#define AVL_TREE_H

#define DEBUG

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <queue> // for level-order traversal

using namespace std;

// AvlTree class

template <typename Comparable>
class AvlTree
{
private:
    size_t totalNodes = 0;
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ele}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;

public:
    /**
     * @brief Default constructor
     */
    AvlTree() : root{nullptr}
    {
    }

    /**
     * @brief Rule-of-3 Part 1: Copy constructor uses internal function clone().
     *
     */
    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    /**
     * @brief Rule-of-3 Part 2: Destroy the Binary Search Tree object using the internal
     *   function makeEmpty().
     */
    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * @brief Rule-of-3 Part 1: Copy constructor uses internal function clone().
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    Comparable* containsReturnPointer(const Comparable &x) const
    {
        return containsReturnPointer(x, root);
    }
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTreeSort(ostream &out = cout) const
    {
        printTreeSort(root, out);
    }

    void printTreeByLevel(ostream &out = cout) const
    {
        printTreeByLevel(root, out);
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const
    {
        prettyPrintTree("", root, false);
    }

    /**
     * Make the tree empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    Comparable *insertReturnPointer(const Comparable &x)
    {
        return insertReturnPointer(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

    size_t getTotalNodes(){
        return totalNodes;
    }

private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{x, nullptr, nullptr, 0};
            totalNodes++;
            return; // a single node is always balanced
        }

        if (t->element > x)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
        {
        } // Duplicate; do nothing

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook)
        // and update the height all the way back up the tree.
        balance(t);
    }

    Comparable *insertReturnPointer(const Comparable &x, AvlNode *&t)
    {
        Comparable *toReturn;
        if (t == nullptr)
        {
            t = new AvlNode{x, nullptr, nullptr, 0};
            totalNodes++;
            return nullptr;
        }

        if (t->element > x)
            toReturn = insertReturnPointer(x, t->left);
        else if (t->element < x)
            toReturn = insertReturnPointer(x, t->right);
        else
        {
            toReturn = &t->element;
        }

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook)
        // and update the height all the way back up the tree.
        balance(t);
        return toReturn;
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, AvlNode *&t)
    {
        throw std::runtime_error("Not implemented yet!");
        // same as in a binary search tree

        // don't forget to balance
        balance(t);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        if (t->left == nullptr)
            return t;

        return findMin(t->left);
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Comparable &x, AvlNode *t) const
    {
        if (t == nullptr)
            return false;

        else if (t->element > x)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
    }

    Comparable* containsReturnPointer(const Comparable &x, AvlNode *t) const
    {
        while (t != nullptr)
            if (t->element > x)
                t = t->left;
            else if (t->element < x)
                t = t->right;
            else
                return &t->element; // Match
        return nullptr;   // No match
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
    }

    /**
     * Internal recursive method to print a subtree rooted at t in sorted order.
     * This is inorder traversal (LNR)
     */
    void printTreeSort(AvlNode *t, ostream &out) const
    {
        if (t == nullptr)
            return;

        // recursion
        printTreeSort(t->left, out);
        out << t->element << " ";
        printTreeSort(t->right, out);
    }

    /**
     * Internal method to print a subtree rooted.
     * This is level-order traversal.
     * We use a loop and a queue an auxiliary data structure to remember what node to process next.
     */
    void printTreeByLevel(AvlNode *t, ostream &out) const
    {
        if (t == nullptr)
            return;

        AvlNode *current;
        queue<AvlNode *> q;

        // start with the root node in the queue
        q.push(t);

        while (!q.empty())
        {
            // take the next node from the front of the queue
            current = q.front();
            q.pop();
            out << current->element << " ";

            // add children to the end of the queue
            if (current->left != nullptr)
                q.push(current->left);

            if (current->right != nullptr)
                q.push(current->right);
        }
    }

    /**
     * Pretty print the tree structure
     * Uses preorder traversal with R and L swapped (NRL)
     *
     * Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
     */
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const
    {
        if (node == nullptr)
            return;

        std::cout << prefix;
        // Note: this uses unicode characters for the tree structure. They might not print correctly on
        // all systems (Windows!?!) and all types of output devices.
        std::cout << (isRight ? "├──" : "└──");
        // print the value of the node
        std::cout << node->element << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    // Avl manipulations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    static const int ALLOWED_IMBALANCE = 3; // 1 is the default; more will make balancing cheaper
                                            // but the search less efficient.

    // Assume t is balanced or within one of being balanced since we check this after each manipulation
    // t represents alpha in the textbook
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {

        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1)
    {

        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif