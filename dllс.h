#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef DLLC_H
#define DLLC_H

typedef struct dllc *dllc_t;

struct dllc {
    char item;
    dllc_t previous;
    dllc_t next;
};

void dllc_add_last(dllc_t *head, char element) {
    if (!head) return;
    dllc_t new = malloc(sizeof(struct dllc));
    new->item = element;
    new->previous = NULL;
    new->next = NULL;
    if (!(*head)) {
        (*head) = new;
        return;
    }

    dllc_t it = *head;
    while (it->next) {
        it = it->next;
    }
    new->previous = it;
    it->next = new;
}

bool dllc_add_after(dllc_t head, const char element) {
    if (!head) return false;
    dllc_t new = malloc(sizeof(struct dllc));
    new->item = element;
    new->previous = head;
    new->next = head->next;
    if (head->next)
        head->next->previous = new;
    head->next = new;
    return true;
}

bool dllc_insert(dllc_t *const head, const size_t index, const char element) {
    if (!head) return false;
    const dllc_t new = malloc(sizeof(struct dllc));
    new->item = element;
    new->previous = NULL;
    new->next = NULL;
    if (index == 0) {
        (*head) = new;
        return true;
    }

    if (!(*head)) return false;
    dllc_t it = *head;
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

dllc_t dllc_find(dllc_t head, char item) {
    while (head) {
        if (head->item == item)
            return head;
        head = head->next;
    }
    return NULL;
}

// 1 - node is closer to the tail, -1 - node is closer to the head, 0 - node at middle
short dllc_closest_border(dllc_t node) {
    size_t dright = 0, dleft = 0;
    dllc_t tail = node;
    while (tail) {
        dright++;
        tail = tail->next;
    }
    dllc_t head = node;
    while (head) {
        dleft++;
        head = head->previous;
    }
    if (dright < dleft) return 1;
    if (dright == dleft) return 0;
    return -1;
}

void dllc_print(dllc_t head) {
    do {
        putchar(head->item);
        head = (head)->next;
    } while (head);
    putchar('\n');
}

void dllc_remove(dllc_t *node) {
    if (!node) return;
    dllc_t elem = *node;
    if (!elem) return;
    if (elem->previous) {
        elem->previous->next = elem->next;
    }
    if (elem->next) {
        elem->next->previous = elem->previous;
    }
    free(elem);
    *node = NULL;
}

size_t dllc_count(const dllc_t head) {
    dllc_t temp = head;
    size_t result = 0;
    if (head) {
        do {
            temp = temp->next;
            result++;
        } while (temp && temp != head);
    }
    return result;
}

void dllc_remove_key(dllc_t head, const char key) {
    while (head) {
        dllc_t next = head->next;
        if (key == head->item) {
            dllc_remove(&head);
        }
        head = next;
    }
}

void dllc_free(dllc_t *head) {
    do {
        dllc_t old = *head;
        *head = old->next;
        free(old);
    } while (*head);
    *head = NULL;
}
#endif
