#include "ll.h"
#include "dlli.h"
#include "dllс.h"
#include "bst.h"
#include "avl.h"
#include "arri.h"

int main() {
    int arr[] = {
            9, 7, 8, 3, 5, 4, 1, 2, 6, 0};
    size_t N = 10;
    arri_print(arr, N);
    arri_shaker_sort(arr, N);
    arri_print(arr, N);
    return 0;
}
