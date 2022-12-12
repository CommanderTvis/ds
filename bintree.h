#include <stdlib.h>
#include <printf.h>
#include "util.h"
#include "dllp.h"

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

bnode_t bnode_find(bnode_t root, int item) {
    if (!root) return NULL;
    if (root->data == item) return root;
    bnode_t p1 = bnode_find(root->left, item);
    if (p1) return p1;
    return bnode_find(root->right, item);
}

bool bnode_free(bnode_t *root) {
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

void bnode_print_impl(bnode_t root, size_t depth) {
    if (!root) return;
    for (size_t i = 0; i < depth; i++) {
        putchar('>');
    }
    printf("%i\n", root->data);
    bnode_print_impl(root->left, depth + 1);
    bnode_print_impl(root->right, depth + 1);
}

void bnode_print_horizontal(bnode_t root) {
    bnode_print_impl(root, 0);
}

void bnode_print_vertical(bnode_t root) {
    dllp_t tree_level = dllp_empty;
    dllp_add_last(&tree_level, root);
    dllp_t temp = dllp_empty;
    size_t counter = 0;
    size_t height = bnode_height(root) - 1;
    size_t n_elements = (1uL << (height + 1)) - 1;
    while (counter <= height) {
        bnode_t removed = dllp_delete(&tree_level);
        size_t n_spaces;
        if (dllp_is_empty(temp))
            n_spaces = n_elements / (1uL << (counter + 1));
        else
            n_spaces = n_elements / (1uL << counter);

        for (; n_spaces > 0; n_spaces--)
            putchar(' ');

        if (!removed)
            putchar(' ');
        else
            printf("%i", removed->data);

        if (removed) {
            dllp_add_last(&temp, removed->left);
            dllp_add_last(&temp, removed->right);
        } else {
            dllp_add_last(&temp, NULL);
            dllp_add_last(&temp, NULL);
        }

        if (dllp_is_empty(tree_level)) {
            puts("\n");
            tree_level = temp;
            temp = dllp_empty;
            counter++;
        }
    }
}

#endif // BINTREE_H
