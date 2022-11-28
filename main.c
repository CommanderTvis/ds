#include "ll.h"
#include "dlli.h"
#include "dllс.h"
#include "bintree_print.h"

int main(int argc, char **argv) {
    bnode_t r = bnode_new_leaf(1);
    bnode_t q = bnode_new_leaf(1);
    q->left = bnode_new_leaf(4);
    q->right = bnode_new_leaf(5);
    bnode_t s = bnode_new_leaf(4);
    s->left = bnode_new_leaf(6);
    s->right = bnode_new_leaf(7);
    r->left = s;
    r->right = q;
    bnode_print_vertical(r);
    return 0;
}
