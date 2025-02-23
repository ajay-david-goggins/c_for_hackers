#include <stdio.h>
#include <stdlib.h>

int* bubbleSort(int arr[], int n) {

    int swapped = 0; // swapped count 
    int lC = 0; // loop count 
    int* result = (int *) malloc(2 * sizeof(int));

    if (!result) {
        fprintf(stderr, "Memory allcation failed");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        int swap = 0;
        for(int j = 0; j < n - 1 - i; j++) {
            ++lC;
            if (arr[j] > arr[j + 1]) {
                swapped += 1;
                ++swap;
                arr[j] = arr[j] ^ arr[j + 1];
                arr[j + 1] = arr[j] ^ arr[j + 1];
                arr[j] = arr[j] ^ arr[j + 1];
            }
        }

        if (swap == 0) break; // break if the inner loop does not swap
    }

    result[0] = lC;
    result[1] = swapped;
    return result;
}

void printArr(int arr[], int n) {
    printf("\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {8, 9, 6, 2, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int *result = bubbleSort(arr, n);
    printArr(arr, n);

    printf("Actally loop runed : %d and swapped : %d",result[0], result[1]);
    free(result);
    return 0;
}
