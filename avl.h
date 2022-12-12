#ifndef AVL_H
#define AVL_H

#include "bintree.h"

void bnode_right_rotate(bnode_t *const node) {
    if (!node) return;
    if (!(*node)) return;
    bnode_t left = (*node)->left;
    bnode_t leftRight = left->right;
    left->right = *node;
    (*node)->left = leftRight;
    *node = left;
}

void bnode_left_rotate(bnode_t *const node) {
    if (!node) return;
    if (!(*node)) return;
    bnode_t right = (*node)->right;
    bnode_t rightLeft = right->left;
    right->left = *node;
    (*node)->right = rightLeft;
    *node = right;
}

void avl_insert(bnode_t *const node, const int key) {
    if (!(*node)) *node = bnode_new_leaf(key);

    if (key < (*node)->data)
        avl_insert(&((*node)->left), key);
    else if (key > (*node)->data)
        avl_insert(&((*node)->right), key);
    else
        return;

    long long balance = bnode_height((*node)->left) - bnode_height((*node)->right);

    if (balance > 1 && key < (*node)->left->data)
        bnode_right_rotate(node);

    if (balance < -1 && key > (*node)->right->data)
        bnode_left_rotate(node);

    if (balance > 1 && key > (*node)->left->data) {
        bnode_left_rotate(&((*node)->left));
        bnode_right_rotate(node);
    }

    if (balance < -1 && key < (*node)->right->data) {
        bnode_right_rotate(&((*node)->right));
        bnode_left_rotate(node);
    }
}

#endif //AVL_H
