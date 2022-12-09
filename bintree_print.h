#include "bintree.h"
#include "dllp.h"
#ifndef BINTREE_PRINT_H
#define BINTREE_PRINT_H

void print_offset(size_t n, bnode_t removed) {
    for (; n > 0; n--) {
        putchar(' ');
    }
    if (!removed) {
        putchar(' ');
    } else {
        printf("%i", removed->data);
    }
}


void bnode_print_vertical(bnode_t root) {
    dllp_t treeLevel = NULL;
    dllp_add_last(&treeLevel, root);
    dllp_t temp = NULL;
    size_t counter = 0;
    size_t height = bnode_height(root) - 1;
    size_t n_elements = (1uL << (height + 1)) - 1;
    while (counter <= height) {
        bnode_t removed = dllp_delete(&treeLevel);
        if (dllp_is_empty(temp)) {
            print_offset(n_elements / (1uL << (counter + 1)), removed);
        } else {
            print_offset(n_elements / (1uL << counter), removed);
        }
        if (removed) {
            dllp_add_last(&temp, removed->left);
            dllp_add_last(&temp, removed->right);
        } else {
            dllp_add_last(&temp, NULL);
            dllp_add_last(&temp, NULL);
        }

        if (dllp_is_empty(treeLevel)) {
            puts("\n");
            treeLevel = temp;
            temp = NULL;
            counter++;
        }
    }
}
#endif
