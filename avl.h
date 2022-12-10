#ifndef AVL_H
#define AVL_H

#include "bintree.h"

void bnode_right_rotate(bnode_t *const y) {
    if (!y) return;
    bnode_t x = (*y)->left;
    bnode_t t2 = x->right;
    x->right = *y;
    (*y)->left = t2;
    *y = x;
}

void bnode_left_rotate(bnode_t *const x) {
    if (!x) return;
    bnode_t y = (*x)->right;
    bnode_t t2 = y->left;
    y->left = *x;
    (*x)->right = t2;
    *x = y;
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
