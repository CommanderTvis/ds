#include "ll.h"
#include "dlli.h"
#include "dllс.h"
#include "bintree_print.h"
#include "bst.h"

int main() {
    bnode_t r = bnode_new_leaf(1);
    r->left = bnode_new_leaf(2);
    r->left->left = bnode_new_leaf(3);
    r->left->right = bnode_new_leaf(4);
    r->right = bnode_new_leaf(4);
    puts("tree:");
    bnode_print_vertical(r);
    return 0;
}
