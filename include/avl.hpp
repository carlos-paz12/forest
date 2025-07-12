#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "user.hpp"
#include <iostream>
#include <algorithm>
#include <string>

using value_type = std::size_t;

struct AVLNode {
    value_type key;
    User data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(value_type k, const User& user_data)
        : key(k), data(user_data), left(nullptr), right(nullptr), height(1) {}
};

using TreeAvlNodePtr = AVLNode*;

class AVLTree {
public:
    TreeAvlNodePtr root;

    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroyRecursive(root);
    }

    void insert(value_type key, const User& data) {
        root = insertRecursive(root, key, data);
    }

    void remove(value_type key) {
        root = deleteRecursive(root, key);
    }

    User* search(value_type key) {
        return searchRecursive(root, key);
    }

    void print() {
        printRecursive(root, "", true);
    }

private:
    int height(TreeAvlNodePtr node) {
        return node ? node->height : 0;
    }

    int balanceFactor(TreeAvlNodePtr node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    TreeAvlNodePtr rightRotate(TreeAvlNodePtr y) {
        TreeAvlNodePtr x = y->left;
        TreeAvlNodePtr T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    TreeAvlNodePtr leftRotate(TreeAvlNodePtr x) {
        TreeAvlNodePtr y = x->right;
        TreeAvlNodePtr T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    TreeAvlNodePtr insertRecursive(TreeAvlNodePtr node, value_type key, const User& data) {
        if (!node)
            return new AVLNode(key, data);

        if (key < node->key)
            node->left = insertRecursive(node->left, key, data);
        else if (key > node->key)
            node->right = insertRecursive(node->right, key, data);
        else
            return node; // No duplicates allowed

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        // Balancing cases
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    TreeAvlNodePtr minValueNode(TreeAvlNodePtr node) {
        TreeAvlNodePtr current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    TreeAvlNodePtr deleteRecursive(TreeAvlNodePtr root_node, value_type key) {
        if (!root_node)
            return root_node;

        if (key < root_node->key)
            root_node->left = deleteRecursive(root_node->left, key);
        else if (key > root_node->key)
            root_node->right = deleteRecursive(root_node->right, key);
        else {
            if (!root_node->left || !root_node->right) {
                TreeAvlNodePtr temp = root_node->left ? root_node->left : root_node->right;

                if (!temp) {
                    temp = root_node;
                    root_node = nullptr;
                } else {
                    *root_node = *temp;
                }

                delete temp;
            } else {
                TreeAvlNodePtr temp = minValueNode(root_node->right);
                root_node->key = temp->key;
                root_node->data = temp->data;
                root_node->right = deleteRecursive(root_node->right, temp->key);
            }
        }

        if (!root_node)
            return root_node;

        root_node->height = 1 + std::max(height(root_node->left), height(root_node->right));
        int balance = balanceFactor(root_node);

        // Balancing
        if (balance > 1 && balanceFactor(root_node->left) >= 0)
            return rightRotate(root_node);

        if (balance > 1 && balanceFactor(root_node->left) < 0) {
            root_node->left = leftRotate(root_node->left);
            return rightRotate(root_node);
        }

        if (balance < -1 && balanceFactor(root_node->right) <= 0)
            return leftRotate(root_node);

        if (balance < -1 && balanceFactor(root_node->right) > 0) {
            root_node->right = rightRotate(root_node->right);
            return leftRotate(root_node);
        }

        return root_node;
    }

    User* searchRecursive(TreeAvlNodePtr node, value_type key) {
        if (!node)
            return nullptr;
        if (key == node->key)
            return &node->data;
        if (key < node->key)
            return searchRecursive(node->left, key);
        else
            return searchRecursive(node->right, key);
    }

  /*   void printRecursive(TreeAvlNodePtr node, const std::string& prefix, bool isLeft) {
        if (!node)
            return;
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        std::cout << node->key << "\n";
        printRecursive(node->left, prefix + (isLeft ? "│   " : "    "), true);
        printRecursive(node->right, prefix + (isLeft ? "│   " : "    "), false);
    } */
    void printRecursive(TreeAvlNodePtr node, const std::string& prefix, bool isLeft) {
    std::cout << prefix;

    std::cout << (isLeft ? "├──" : "└──");

    if (node != nullptr) {
        std::cout << "\033[32m[ key: " << node->key << " ] { \"name\": \"" << node->data.login
                  << "\", \"userid\": " << node->data.userid
                  << ", \"region\": \"" << node->data.region
                  << "\", \"password\": \"" << node->data.password << "\" }\033[0m\n";

        std::string newPrefix = prefix + (isLeft ? "│   " : "    ");

        // Ordem: direita primeiro, depois esquerda
        printRecursive(node->right, newPrefix, true);
        printRecursive(node->left, newPrefix, false);
    } else {
        std::cout << "\033[31mx\033[0m\n";
    }
}


    void destroyRecursive(TreeAvlNodePtr node) {
        if (!node)
            return;
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
};

inline value_type create_key(const User& user) {
    return static_cast<value_type>(user.userid);
}

#endif // AVL_TREE_HPP
//:) I love my life