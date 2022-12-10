#include "ll.h"
#include "dlli.h"
#include "dllс.h"
#include "bintree_print.h"
#include "bst.h"

int main() {
//    bnode_t r = bnode_new_leaf(1);
//    r->left = bnode_new_leaf(2);
//    r->left->left = bnode_new_leaf(3);
//    r->left->right = bnode_new_leaf(4);
//    r->right = bnode_new_leaf(4);
    bnode_t r = avl_insert(NULL, 5);
    r = avl_insert(r, 2);
    r = avl_insert(r, 3);
    r = avl_insert(r, 1);
    r = avl_insert(r, 4);
    puts("AVL tree:");
    bnode_print_vertical(r);
    dlli_t ls = bst_to_list(r);
    puts("list:");
    dlli_print(ls);
    return 0;
}
