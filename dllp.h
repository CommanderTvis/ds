#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef DLLP_H
#define DLLP_H

typedef struct dllp *dllp_t;

#define dllp_empty NULL

struct dllp {
    void *item;
    dllp_t previous;
    dllp_t next;
};

void dllp_add_last(dllp_t *head, void *element) {
    if (!head) return;
    dllp_t new = malloc(sizeof(struct dllp));
    new->item = element;
    new->previous = NULL;
    new->next = NULL;
    if (!(*head)) {
        (*head) = new;
        return;
    }

    dllp_t it = *head;
    while (it->next) {
        it = it->next;
    }
    new->previous = it;
    it->next = new;
}

bool dllp_add_after(const dllp_t head, void *element) {
    if (!head) return false;
    dllp_t new = malloc(sizeof(struct dllp));
    new->item = element;
    new->previous = head;
    new->next = head->next;
    if (head->next)
        head->next->previous = new;
    head->next = new;
    return true;
}

bool dllp_insert(dllp_t *const head, const size_t index, void *const element) {
    if (!head) return false;
    dllp_t new = malloc(sizeof(struct dllp));
    new->item = element;
    new->previous = NULL;
    new->next = NULL;
    if (index == 0) {
        (*head) = new;
        return true;
    }

    if (!(*head)) return false;
    dllp_t it = *head;
    size_t cnt = 0;
    while (it->next && cnt != index) {
        it = it->next;
        cnt++;
    }
    if (cnt != index) return false;
    it->previous->next = new;
    new->previous = it->previous;
    it->previous = new;
    new->next = it;
    return true;
}

dllp_t dllp_find(dllp_t head, void *item) {
    while (head) {
        if (head->item == item)
            return head;
        head = head->next;
    }
    return NULL;
}

void *dllp_delete(dllp_t *node) {
    if (!node) return NULL;
    if (!(*node)) return NULL;
    if ((*node)->previous) {
        (*node)->previous->next = (*node)->next;
    }
    if ((*node)->next) {
        (*node)->next->previous = (*node)->previous;
    }
    void *item = (*node)->item;
    dllp_t next = (*node)->next;
    free((*node));
    *node = next;
    return item;
}

size_t dllp_count(dllp_t head) {
    if (!head) return 0;
    dllp_t temp = head;
    size_t result = 0;
    do {
        temp = temp->next;
        result++;
    } while (temp && temp != head);
    return result;
}

static inline bool dllp_is_empty(dllp_t head) {
    return !head;
}

void dllp_free(dllp_t *head) {
    do {
        dllp_t old = *head;
        *head = old->next;
        free(old);
    } while (*head);
    *head = NULL;
}

#endif
