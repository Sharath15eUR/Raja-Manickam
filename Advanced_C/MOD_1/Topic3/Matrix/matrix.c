#include <stdio.h>
#include <stdbool.h>

bool searchMatrix(int matrix[][100], int n, int key) {
    int row = 0, col = n - 1;

    while (row < n && col >= 0) {
        if (matrix[row][col] == key) {
            printf("Key %d found at position (%d, %d)\n", key, row, col);
            return true;
        } else if (matrix[row][col] > key) {
            col--;
        } else {
            row++;
        }
    }
    printf("Key %d not found in the matrix.\n", key);
    return false;
}

int main() {
    int n;
    int matrix[100][100];

    printf("Enter matrix size n: ");
    scanf("%d", &n);

    printf("Enter sorted matrix (each row and column increasing):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);

    int key;
    printf("Enter key to search: ");
    scanf("%d", &key);

    searchMatrix(matrix, n, key);

    return 0;
} 