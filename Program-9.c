#include <stdio.h>
#include <stdbool.h>

#define MAX_N 16 

int board[MAX_N][MAX_N];


void printSolution(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1) {
                printf("Q "); 
            } else {
                printf(". "); 
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool isSafe(int row, int col, int N) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

void solveNQueens(int N, int row) {
    if (row == N) {
        printSolution(N);
        return;
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col, N)) {
            board[row][col] = 1;
            solveNQueens(N, row + 1); 
            board[row][col] = 0;
        }
    }
}

int main() {
    int N;
    printf("Enter the value of N (size of the board): ");
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }
    printf("Solutions to the N-Queens problem:\n");
    solveNQueens(N, 0);

    return 0;
}
