// include/avl.hpp
#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "user.hpp"
#include <iostream>
#include <algorithm>
#include <string>

using value_type = long long;

struct AVLNode {
    value_type key;
    User data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(value_type k, const User& user_data);
};

using TreeAvlNodePtr = AVLNode*;

class AVLTree {
public:
    TreeAvlNodePtr root;

    AVLTree();
    ~AVLTree();

    void insert(value_type key, const User& data);
    void remove(value_type key);
    User* search(value_type key);
    void print();

private:
    int height(TreeAvlNodePtr node);
    int balanceFactor(TreeAvlNodePtr node);
    TreeAvlNodePtr rightRotate(TreeAvlNodePtr y);
    TreeAvlNodePtr leftRotate(TreeAvlNodePtr x);
    TreeAvlNodePtr insertRecursive(TreeAvlNodePtr node, value_type key, const User& data);
    TreeAvlNodePtr minValueNode(TreeAvlNodePtr node);
    TreeAvlNodePtr deleteRecursive(TreeAvlNodePtr root_node, value_type key);
    User* searchRecursive(TreeAvlNodePtr node, value_type key);
    void printRecursive(TreeAvlNodePtr node, const std::string& prefix, bool isLeft);
    void destroyRecursive(TreeAvlNodePtr node);
};

value_type create_key(const User& user);

#endif // AVL_TREE_HPP
