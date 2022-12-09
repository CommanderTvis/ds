#include <stdbool.h>
#include <stdio.h>
#ifndef DLLI_H

typedef struct dlli *dlli_t;

struct dlli {
    int item;
    dlli_t previous;
    dlli_t next;
};

void dlli_add_last(dlli_t *head, int element) {
    if (!head) return;
    dlli_t new = malloc(sizeof(struct dlli));
    new->item = element;
    new->previous = NULL;
    new->next = NULL;
    if (!(*head)) {
        (*head) = new;
        return;
    }

    dlli_t it = *head;
    while (it->next) {
        it = it->next;
    }
    new->previous = it;
    it->next = new;
}

bool dlli_add_after(dlli_t head, int element) {
    if (!head) return false;
    dlli_t new = malloc(sizeof(struct dlli));
    new->item = element;
    new->previous = head;
    new->next = head->next;
    if (head->next)
        head->next->previous = new;
    head->next = new;
    return true;
}

bool dlli_insert(dlli_t *head, size_t index, int element) {
    if (!head) return false;
    dlli_t new = malloc(sizeof(struct dlli));
    new->item = element;
    new->previous = NULL;
    new->next = NULL;
    if (index == 0) {
        (*head) = new;
        return true;
    }

    if (!(*head)) return false;
    dlli_t it = *head;
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

dlli_t dlli_find(dlli_t head, int item) {
    while (head) {
        if (head->item == item)
            return head;
        head = head->next;
    }
    return NULL;
}

// 1 - node is closer to the tail, -1 - node is closer to the head, 0 - node at middle
short dlli_closest_border(dlli_t node) {
    size_t dright = 0, dleft = 0;
    dlli_t tail = node;
    while (tail) {
        dright++;
        tail = tail->next;
    }
    dlli_t head = node;
    while (head) {
        dleft++;
        head = head->previous;
    }
    if (dright < dleft) return 1;
    if (dright == dleft) return 0;
    return -1;
}

int dlli_delete(dlli_t *node) {
    if (!node) return 0;
    dlli_t elem = *node;
    if (!elem) return 0;
    if (elem->previous) {
        elem->previous->next = elem->next;
    }
    if (elem->next) {
        elem->next->previous = elem->previous;
    }
    int item = elem->item;
    free(elem);
    *node = NULL;
    return item;
}

void dlli_delete_multiplies_of_5(dlli_t head) {
    size_t i = 1;
    while (head) {
        dlli_t next = head->next;
        if (i % 5 == 0) {
            dlli_delete(&head);
        }
        i++;
        head = next;
    }
}

void dlli_print(dlli_t head) {
    do {
        printf("%i\n", head->item);
        head = (head)->next;
    } while (head);
}

bool dlli_is_empty(dlli_t head) {
    return !head;
}

void dlli_free(dlli_t *head) {
    do {
        dlli_t old = *head;
        *head = old->next;
        free(old);
    } while (*head);
    *head = NULL;
}
#endif
