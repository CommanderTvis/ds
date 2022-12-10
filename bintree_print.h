#include "bintree.h"
#include "dllp.h"

#ifndef BINTREE_PRINT_H
#define BINTREE_PRINT_H˚


void bnode_print_vertical(bnode_t root) {
    dllp_t treeLevel = NULL;
    dllp_add_last(&treeLevel, root);
    dllp_t temp = NULL;
    size_t counter = 0;
    size_t height = bnode_height(root) - 1;
    size_t n_elements = (1uL << (height + 1)) - 1;
    while (counter <= height) {
        bnode_t removed = dllp_delete(&treeLevel);
        size_t n;
        if (dllp_is_empty(temp))
            n = n_elements / (1uL << (counter + 1));
        else
            n = n_elements / (1uL << counter);

        for (; n > 0; n--)
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

        if (dllp_is_empty(treeLevel)) {
            puts("\n");
            treeLevel = temp;
            temp = NULL;
            counter++;
        }
    }
}

#endif
