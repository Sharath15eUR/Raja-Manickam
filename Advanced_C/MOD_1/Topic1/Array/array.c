#include <stdio.h>
#include<stdlib.h>
void rearrangeEvenOdd(int *arr, int size) {
    int *temp = (int *)malloc(size * sizeof(int));
    int *write = temp;

    // First pass: copy even elements
    for (int *p = arr; p < arr + size; p++) {
        if (*p % 2 == 0) {
            *write++ = *p;
        }
    }

    // Second pass: copy odd elements
    for (int *p = arr; p < arr + size; p++) {
        if (*p % 2 != 0) {
            *write++ = *p;
        }
    }

    // Copy back to original array
    for (int i = 0; i < size; i++) {
        *(arr + i) = *(temp + i);
    }

    free(temp);
}

void printArray(int *arr, int size) {
    for (int *p = arr; p < arr + size; p++) {
        printf("%d ", *p);
    }
    printf("\n");
}

int main() {
    int arr[] = {3, 8, 5, 6, 7, 2, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, size);

    rearrangeEvenOdd(arr, size);

    printf("Rearranged array: ");
    printArray(arr, size);

    return 0;
}