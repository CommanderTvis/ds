#include <stdio.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#ifndef LL_H
#define LL_H

typedef struct ll *ll_t;

#define ll_empty NULL

struct ll {
    int item;
    ll_t next;
};

void ll_add_last(ll_t *head, int element) {
    ll_t new = malloc(sizeof(struct ll));
    new->item = element;
    new->next = NULL;
    if (!(*head)) {
        (*head) = new;
        return;
    }

    ll_t it = *head;
    while (it->next) {
        it = it->next;
    }
    it->next = new;
}

void ll_add_first(ll_t *head, int element) {
    ll_t new = malloc(sizeof(struct ll));
    new->item = element;
    new->next = *head;
    *head = new;
}

void ll_make_cycled(ll_t head) {
    ll_t cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = head;
}

size_t ll_count(ll_t head) {
    ll_t temp = head;
    size_t result = 0;
    if (head) {
        do {
            temp = temp->next;
            result++;
        } while (temp && temp != head);
    }
    return result;
}

int ll_get(ll_t head, size_t index) {
    ll_t current = head;
    size_t count = 0;
    while (current) {
        if (count == index)
            return current->item;
        count++;
        current = current->next;
    }
    return 0;
}

bool ll_delete_first(ll_t *head) {
    if (!head || !(*head)) return false;
    ll_t old_head = *head;
    ll_t new_head = (*head)->next;
    free(old_head);
    (*head) = new_head;
    return true;
}

bool ll_remove_between(ll_t previous, ll_t *head) {
    if (!previous || !head || !(*head)) return false;
    previous->next = (*head)->next;
    return ll_delete_first(head);
}

bool ll_insert_between(ll_t previous, ll_t *head) {
    if (!previous || !head || !(*head)) return false;
    previous->next = (*head)->next;
    return ll_delete_first(head);
}

void ll_set(ll_t head, size_t index, int value) {
    ll_t current = head;
    int count = 0;
    while (current) {
        if (count == index)
            current->item = value;
        count++;
        current = current->next;
    }
}

void ll_swap(ll_t a, ll_t b) {
    int temp = a->item;
    a->item = b->item;
    b->item = temp;
}


void ll_count_sort(ll_t head, int max_number) {
    size_t N = ll_count(head);
    int *count = calloc(max_number, sizeof(int));

    for (int i = 0; i < N; ++i)
        ++count[ll_get(head, i)];

    for (int i = 0, j = 0; i < max_number; ++i)
        for (int k = 0; k < count[i]; ++k)
            ll_set(head, j++, i);
    free(count);
}

int ll_most_frequent(ll_t head) {
    size_t maxcount = 0;
    int element_having_max_freq = head->item;
    ll_t external = head;
    while (external->next) {
        size_t count = 0;
        ll_t internal = head;
        while (internal->next) {
            if (external->item == internal->item)
                count++;
            internal = internal->next;
        }

        if (count > maxcount) {
            maxcount = count;
            element_having_max_freq = external->item;
        }
        external = external->next;
    }

    return element_having_max_freq;
}

void ll_delete(ll_t *head, const size_t position) {
    ll_t temp = *head;
    ll_t prev = *head;
    for (size_t i = 0; i < position; i++) {
        if (i == 0 && position == 1) {
            *head = (*head)->next;
            free(temp);
            temp = ll_empty;
        } else {
            if (i == position - 1 && temp) {
                prev->next = temp->next;
                free(temp);
                temp = ll_empty;
            } else {
                prev = temp;
                if (!prev)
                    break;
                temp = temp->next;
            }
        }
    }
}

void ll_delete_even(ll_t *head) {
    for (size_t i = 2; i <= ll_count(*head); i += 1) {
        ll_delete(head, i);
    }
}

void ll_delete_multiplies_of_5(ll_t *head) {
    for (size_t i = 5; i <= ll_count(*head); i += 4) {
        ll_delete(head, i);
    }
}

bool ll_contains(ll_t head, int element) {
    if (!head) return false;
    do {
        if (head->item == element)
            return true;
        head = head->next;
    } while (head);
    return false;
}

void ll_print(ll_t head) {
    do {
        printf("%i\n", head->item);
        head = (head)->next;
    } while (head);
}

void ll_delete_duplicates(ll_t *head) {
    if (!head) return;
    ll_t copy = NULL;
    do {
        if (!ll_contains(copy, (*head)->item))
            ll_add_last(&copy, (*head)->item);
        ll_t prev = *head;
        *head = prev->next;
        free(prev);
    } while (*head);
    *head = copy;
}
#endif
