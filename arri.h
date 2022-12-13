#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*Сортировка пузырьком*/
void arri_bubble_sort(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    for (size_t i = 0; i < N - 1; ++i) {
        for (size_t j = 0; j < N - 1 - i; ++j) {
            if (arr[j + 1] < arr[j]) {
                swap(arr + j + 1, arr + j);
            }
        }
    }
}

/*Сортировка перемешиванием (шейкер) sort*/
void arri_shaker_sort(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    size_t leftIndex = 0;
    size_t rightIndex = N - 1;
    while (leftIndex <= rightIndex) {
        for (size_t i = rightIndex; i > leftIndex; --i) {
            if (arr[i - 1] > arr[i])
                swap(arr + i - 1, arr + i);
        }
        ++leftIndex;

        for (size_t i = leftIndex; i < rightIndex; ++i) {
            if (arr[i] > arr[i + 1])
                swap(arr + i, arr + i + 1);
        }
        --rightIndex;
    }
}

/*Сортировка расческой*/
void arri_comb_sort(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    double decreaseVal = 1.247;
    double compareStep = N - 1;

    while (compareStep >= 1) {
        for (size_t i = 0; i < N - compareStep; ++i) {
            if (arr[i] > arr[i + (size_t) compareStep])
                swap(arr + i, arr + (size_t) compareStep);
        }

        compareStep = compareStep / decreaseVal;
    }

    arri_bubble_sort(arr, N);
}

/*Сортировка вставками*/
void arri_insertion_sort(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    for (size_t i = 1; i < N; ++i) {
        int currentElem = arr[i];
        size_t rightBorder = i;

        /* 10 9 8 7 4 3 2*/
        while (rightBorder > 0 && arr[rightBorder - 1] > currentElem) {
            arr[rightBorder] = arr[rightBorder - 1];
            --rightBorder;
        }
        arr[rightBorder] = currentElem;
    }
}

int arri_min_beginning(int *arr, int startNumber, size_t N) {
    if (!arr || N <= 0) return startNumber;
    int minElem = arr[startNumber];
    size_t minElemPosition = startNumber;
    for (size_t i = startNumber + 1; i < N; ++i) {
        if (arr[i] < minElem) {
            minElem = arr[i];
            minElemPosition = i;
        }
    }

    return minElemPosition;
}

/*Сортировка выбором*/
void arri_selection_sort(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    for (size_t i = 0; i < N; ++i) {
        size_t currentMinPos = arri_min_beginning(arr, i, N);
        swap(arr + i, arr + currentMinPos);
    }
}

/*Быстрая сортировка*/
size_t arri_quick_sort_partition(int *arr, size_t low, size_t high) {
    int x = arr[high];
    size_t less = low;

    for (size_t k = low; k < high; ++k) {
        if (arr[k] <= x) {
            swap(arr + k, arr + less);
            ++less;
        }
    }
    swap(arr + less, arr + high);
    /*arr[] = {10, 9, 7, 6, 4, -3, -6, 10, 11, 15, 12};
    less = 7  */
    return less;
}

void arri_quick_sort_impl(int *arr, size_t N, size_t low, size_t high) {
    if (low < high) {
        size_t foundIndex = arri_quick_sort_partition(arr, low, high);
        arri_quick_sort_impl(arr, N, low, min(foundIndex - 1, N));
        arri_quick_sort_impl(arr, N, max(foundIndex + 1, 0), high);
    }
}

void arri_quick_sort(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    arri_quick_sort_impl(arr, N, 0, N - 1);
}

void arri_create_heap(int *arr, size_t N, size_t iNode) {
    if (!arr || N <= 0) return;
    size_t root = iNode;
    size_t left = 2 * iNode + 1;
    size_t right = 2 * iNode + 2;
    if (left < N && arr[left] > arr[root])
        root = left;

    if (right < N && arr[right] > arr[root])
        root = right;

    if (root != iNode) {
        swap(arr + iNode, arr + root);
        arri_create_heap(arr, N, root);
    }
}

void arri_heap_sort(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    for (size_t i = N / 2; i >= 1; --i) {
        arri_create_heap(arr, N, i - 1);
    }

    for (size_t i = N; i >= 1; --i) {
        swap(arr + 0, arr + i - 1);
        arri_create_heap(arr, i - 1, 0);
    }
}

enum {
    MAX_NUMBER = 50
};

void arri_count_sort(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    size_t count[MAX_NUMBER] = {0};

    for (size_t i = 0; i < N; ++i)
        ++count[arr[i]];

    for (size_t i = 0, j = 0; i < MAX_NUMBER; ++i)
        for (size_t k = 0; k < count[i]; ++k)
            arr[j++] = i;
}

void arri_bead_sort(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    int max = arr[0];
    for (size_t i = 1; i < N; ++i)
        if (arr[i] > max)
            max = arr[i];

    int *beads = calloc(max * N, sizeof(int));
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < arr[i]; ++j)
            beads[i * max + j] = 1;


    int sum;
    for (int j = 0; j < max; ++j) {
        for (size_t i = sum = 0; i < N; ++i) {
            sum += beads[i * max + j];
            beads[i * max + j] = 0;
        }

        for (size_t i = N - sum; i < N; ++i)
            beads[i * max + j] = 1;
    }

    for (size_t i = 0; i < N; ++i) {
        size_t j;
        for (j = 0; j < max && beads[i * max + j]; ++j);
        arr[i] = j;
    }

    free(beads);
}

void arri_print(int *arr, size_t N) {
    if (!arr || N <= 0) return;
    for (size_t i = 0; i < N - 1; ++i)
        printf("%i ", arr[i]);
    printf("%i\n", arr[N - 1]);
}
