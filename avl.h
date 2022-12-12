#ifndef AVL_H
#define AVL_H

#include "bintree.h"

void bnode_right_rotate(bnode_t *a) {
    //    a         b
    //   /           \
    //  b     ->      a
    //  \            /
    //   c          c
    if (!a) return;
    if (!(*a)) return;
    bnode_t b = (*a)->left;
    bnode_t c = b->right;
    b->right = *a;
    (*a)->left = c;
    *a = b;
}

void bnode_left_rotate(bnode_t *a) {
    //    a            b
    //     \          /
    //      b   ->   a
    //     /          \
    //    c            c
    if (!a) return;
    if (!(*a)) return;
    bnode_t b = (*a)->right;
    bnode_t c = b->left;
    b->left = *a;
    (*a)->right = c;
    *a = b;
}

void avl_insert(bnode_t *node, int data) {
    if (!(*node)) *node = bnode_new_leaf(data);

    if (data < (*node)->data)
        avl_insert(&((*node)->left), data);
    else if (data > (*node)->data)
        avl_insert(&((*node)->right), data);
    else
        return;

    long long balance = bnode_height((*node)->left) - bnode_height((*node)->right);

    if (balance > 1 && data < (*node)->left->data)
        bnode_right_rotate(node);

    if (balance < -1 && data > (*node)->right->data)
        bnode_left_rotate(node);

    if (balance > 1 && data > (*node)->left->data) {
        bnode_left_rotate(&((*node)->left));
        bnode_right_rotate(node);
    }

    if (balance < -1 && data < (*node)->right->data) {
        bnode_right_rotate(&((*node)->right));
        bnode_left_rotate(node);
    }
}

#endif // AVL_H
