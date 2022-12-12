#include <stdbool.h>
#include <limits.h>
#include "bintree.h"

#ifndef BST_H
#define BST_H

void bst_insert(bnode_t *root, int data) {
    if (!root) return;
    if (!(*root))*root = bnode_new_leaf(data);

    if (data < (*root)->data)
        bst_insert(&(*root)->left, data);
    else if (data > (*root)->data)
        bst_insert(&(*root)->right, data);
}

void bst_convert_to_impl(bnode_t root, bnode_t *bst) {
    if (!root) return;
    bst_insert(bst, root->data);
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

int bst_max_impl(bnode_t root) {
    if (!root) return INT_MIN;
    if (root->right)
        return bst_max_impl(root->right);
    return root->data;
}

void bst_to_list_inorder(bnode_t curr, dlli_t *ls) {
    if (!curr) return;
    bst_to_list_inorder(curr->left, ls);
    dlli_add_last(ls, curr->data);
    bst_to_list_inorder(curr->right, ls);
}

dlli_t bst_to_list(bnode_t root) {
    root = bnode_copy(root);
    dlli_t list = dlli_empty;
    bst_to_list_inorder(root, &list);
    bnode_free(&root);
    return list;
}

#endif // BST_H
