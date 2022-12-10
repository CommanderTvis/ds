#include <stdbool.h>
#include "bintree.h"

#ifndef BST_H
#define BST_H


bnode_t bst_insert(bnode_t root, int data) {
    if (!root) return bnode_new_leaf(data);

    if (data < root->data)
        root->left = bst_insert(root->left, data);
    else if (data > root->data)
        root->right = bst_insert(root->right, data);

    return root;
}

void bst_convert_to_impl(bnode_t root, bnode_t *bst) {
    if (!root) return;
    *bst = bst_insert(*bst, root->data);
    bst_convert_to_impl(root->left, bst);
    bst_convert_to_impl(root->right, bst);
}

bnode_t bst_find(bnode_t root, int data) {
    if (!root || root->data == data)
        return root;
    if (root->data < data)
        return bst_find(root->right, data);
    return bst_find(root->left, data);
}

int bst_max_impl(const bnode_t root, const int max) {
    if (!root) return max;
    if (root->right) {
        return max(max, bst_max_impl(root->right, max));
    }
    return max(root->data, max);
}

void bnode_inorder(const bnode_t curr, bnode_t *prev) {
    if (!curr) return;
    bnode_inorder(curr->left, prev);
    (*prev)->left = NULL;
    (*prev)->right = curr;
    *prev = curr;
    bnode_inorder(curr->right, prev);
}

dlli_t bst_to_list(const bnode_t root) {
    bnode_t dummy = bnode_new_leaf(-1);
    bnode_t prev = dummy;
    bnode_inorder(root, &prev);
    prev->left = NULL;
    prev->right = NULL;
    bnode_t ret = dummy->right;
    bnode_t flat = ret;
    dlli_t list = dlli_empty;
    while (flat) {
        dlli_add_last(&list, flat->data);
        flat = flat->right;
    }
    bnode_free(&dummy);
    return list;
}

bnode_t bnode_right_rotate(bnode_t y) {
    if (!y) return NULL;
    bnode_t x = y->left;
    bnode_t t2 = x->right;
    x->right = y;
    y->left = t2;
    return x;
}

bnode_t bnode_left_rotate(bnode_t x) {
    if (!x) return NULL;
    bnode_t y = x->right;
    bnode_t t2 = y->left;
    y->left = x;
    x->right = t2;
    return y;
}

bnode_t avl_insert(bnode_t node, int key) {
    if (!node) return bnode_new_leaf(key);

    if (key < node->data)
        node->left = avl_insert(node->left, key);
    else if (key > node->data)
        node->right = avl_insert(node->right, key);
    else
        return node;

    long long balance = bnode_height(node->left) - bnode_height(node->right);

    if (balance > 1 && key < node->left->data)
        return bnode_right_rotate(node);

    if (balance < -1 && key > node->right->data)
        return bnode_left_rotate(node);

    if (balance > 1 && key > node->left->data) {
        node->left = bnode_left_rotate(node->left);
        return bnode_right_rotate(node);
    }

    if (balance < -1 && key < node->right->data) {
        node->right = bnode_right_rotate(node->right);
        return bnode_left_rotate(node);
    }

    return node;
}

#endif
