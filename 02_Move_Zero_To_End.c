#include <stdio.h>

int* MoveZeroToEnd(int *arr, int n) {
    int j = 0;
    for (int i = 1; i < n; i++) {
        if (arr[j] == 0 && arr[j] != arr[i]) {
            arr[i] = arr[i] ^ arr[j];
            arr[j] = arr[i] ^ arr[j];
            arr[i] = arr[i] ^ arr[j];
            j++;
        }
    }
    return arr;
} 

int main () {
    int n;
    printf("Enter the size of an Array  : ");
    scanf ("%d", &n);

    int arr[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter the value of arr[%d]  : ", i);
        scanf ("%d", &arr[i]);
    }
    int *newArr = MoveZeroToEnd (arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d  ", newArr[i]);
    }

    return 0;
}
