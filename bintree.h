#include <stdlib.h>
#include <printf.h>
#include "util.h"

#ifndef BINTREE_H
#define BINTREE_H

typedef struct bnode *bnode_t;

struct bnode {
    int data;
    bnode_t left;
    bnode_t right;
};

bnode_t bnode_new_leaf(int data) {
    bnode_t new = malloc(sizeof(struct bnode));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void bnode_print_deep_impl(bnode_t root, size_t depth) {
    if (!root) return;
    for (size_t i = 0; i < depth; i++) {
        putchar('>');
    }
    printf("%i\n", root->data);
    bnode_print_deep_impl(root->left, depth + 1);
    bnode_print_deep_impl(root->right, depth + 1);
}

void bnode_print_deep(bnode_t root) {
    bnode_print_deep_impl(root, 0);
}

bnode_t bnode_find(bnode_t root, int item) {
    if (!root) return NULL;
    if (root->data == item) return root;
    bnode_t p1 = bnode_find(root->left, item);
    if (p1) return p1;
    return bnode_find(root->right, item);
}

void bnode_delete(bnode_t *root) {
    if ((*root)->left) {
        bnode_delete(&(*root)->left);
    }
    if ((*root)->right) {
        bnode_delete(&(*root)->right);
    }
    free(*root);
    *root = NULL;
}

size_t bnode_height(bnode_t root) {
    if (!root) return 0;
    return max(bnode_height(root->left), bnode_height(root->right)) + 1;
}

size_t bnode_count_leaves(bnode_t root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return bnode_count_leaves(root->left) + bnode_count_leaves(root->right);
}

size_t bnode_count_nodes(bnode_t root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return bnode_count_nodes(root->left) + bnode_count_nodes(root->right) + 1;
}

bool bnode_is_balanced(bnode_t root) {
    if (!root) return true;
    size_t lh = bnode_height(root->left);
    size_t rh = bnode_height(root->right);
    return distance(lh, rh) <= 1 && bnode_is_balanced(root->left) && bnode_is_balanced(root->right);
}

#endif
