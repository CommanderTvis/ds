#include <stdlib.h>
#include <printf.h>

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

void bnode_print_deep_impl(bnode_t root, size_t depth) {
    if (!root) return;
    for (size_t i = 0; i < depth; i++) {
        putchar('>');
    }
    printf("%i\n", root->data);
    bnode_print_deep_impl(root->left, depth+1);
    bnode_print_deep_impl(root->right, depth+1);
}

void bnode_print_deep(bnode_t root) {
    bnode_print_deep_impl(root, 0);
}



