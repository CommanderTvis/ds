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

bnode_t bnode_new_leaf(const int data) {
    bnode_t new = malloc(sizeof(struct bnode));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void bnode_print_deep_impl(const bnode_t root, const size_t depth) {
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

bnode_t bnode_find(const bnode_t root, const int item) {
    if (!root) return NULL;
    if (root->data == item) return root;
    bnode_t p1 = bnode_find(root->left, item);
    if (p1) return p1;
    return bnode_find(root->right, item);
}

bool bnode_free(bnode_t *const root) {
    if (!root) return false;
    if (!(*root)) return false;
    if ((*root)->left) {
        bnode_free(&(*root)->left);
    }
    if ((*root)->right) {
        bnode_free(&(*root)->right);
    }
    free(*root);
    *root = NULL;
    return true;
}

size_t bnode_height(const bnode_t root) {
    if (!root) return 0;
    return max(bnode_height(root->left), bnode_height(root->right)) + 1;
}

size_t bnode_count_leaves(const bnode_t root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return bnode_count_leaves(root->left) + bnode_count_leaves(root->right);
}

size_t bnode_count_nodes(const bnode_t root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return bnode_count_nodes(root->left) + bnode_count_nodes(root->right) + 1;
}

bool bnode_is_balanced(const bnode_t root) {
    if (!root) return true;
    size_t lh = bnode_height(root->left);
    size_t rh = bnode_height(root->right);
    return distance(lh, rh) <= 1 && bnode_is_balanced(root->left) && bnode_is_balanced(root->right);
}

#endif
