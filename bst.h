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

int bst_max_impl(bnode_t root, int max) {
    if (!root) return max;
    if (root->right) {
        return max(max, bst_max_impl(root->right, max));
    }
    return max(root->data, max);
}
#endif
