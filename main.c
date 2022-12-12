#include "ll.h"
#include "dlli.h"
#include "dllс.h"
#include "bintree_print.h"
#include "bst.h"
#include "avl.h"

int main() {
//    bnode_t r = bnode_new_leaf(1);
//    r->left = bnode_new_leaf(2);
//    r->left->left = bnode_new_leaf(3);
//    r->left->right = bnode_new_leaf(4);
//    r->right = bnode_new_leaf(4);
    bnode_t r = NULL;
    avl_insert(&r, 5);
    avl_insert(&r, 2);
    avl_insert(&r, 3);
    avl_insert(&r, 1);
    avl_insert(&r, 4);
    puts("Tree:");
    bnode_print_vertical(r);

    printf("balanced: %i\n", bnode_is_balanced(r));

    dlli_t ls = bst_to_list(r);
    puts("list:");
    dlli_print(ls);
    return 0;
}
