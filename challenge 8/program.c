#include <stdio.h>

int main() {
    int grid[6][6];         
    int rowTotal[6] = {0};  
    int colTotal[6] = {0};  
    int n, t, i, j;

    printf("===== GRIDWATCH: Campus Risk Scanner =====\n\n");

    //Step 1: take the grid size
    printf("How big is the grid? Enter N (3 to 6): ");
    scanf("%d", &n);
    while (n < 3 || n > 6) {
        printf("Oops, N must be between 3 and 6. Try again: ");
        scanf("%d", &n);
    }

    //Step 2: take the risk scores
  printf("\nNow enter the risk scores (0 to 100).\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Row %d, Column %d: ", i + 1, j + 1);
            scanf("%d", &grid[i][j]);
            while (grid[i][j] < 0 || grid[i][j] > 100) {
                printf("Score must be between 0 and 100. Try again: ");
                scanf("%d", &grid[i][j]);
            }
        }
    }

    //Step 3: take the warning threshold
    printf("\nEnter the warning threshold T (1 to 100): ");
    scanf("%d", &t);
    while (t < 1 || t > 100) {
        printf("T must be between 1 and 100. Try again: ");
        scanf("%d", &t);
    }

    printf("\n========== RESULTS ==========\n");

    //Row and column totals
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            rowTotal[i] = rowTotal[i] + grid[i][j];
            colTotal[j] = colTotal[j] + grid[i][j];
        }
    }

    // find the biggest row total and biggest column total
    int maxRow = rowTotal[0];
    int maxCol = colTotal[0];
    for (i = 1; i < n; i++) {
        if (rowTotal[i] > maxRow) {
            maxRow = rowTotal[i];
        }
        if (colTotal[i] > maxCol) {
            maxCol = colTotal[i];
        }
    }

    // print every row/column that matches the max 
    printf("\nHighest row total is %d -> row(s):", maxRow);
    for (i = 0; i < n; i++) {
        if (rowTotal[i] == maxRow) {
            printf(" %d", i + 1);
        }
    }

    printf("\nHighest column total is %d -> column(s):", maxCol);
    for (j = 0; j < n; j++) {
        if (colTotal[j] == maxCol) {
            printf(" %d", j + 1);
        }
    }
    printf("\n");

    //Highest score and cells at or above the threshold
    int maxScore = grid[0][0];
    int countAboveT = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (grid[i][j] > maxScore) {
                maxScore = grid[i][j];
            }
            if (grid[i][j] >= t) {
                countAboveT++;
            }
        }
    }

    printf("\nHighest risk score is %d, found at:\n", maxScore);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (grid[i][j] == maxScore) {
                printf("  Row %d, Column %d\n", i + 1, j + 1);
            }
        }
    }
    printf("Number of cells with score >= %d: %d\n", t, countAboveT);

    // Diagonals
    int mainDiagonal = 0;
    int secondDiagonal = 0;
    for (i = 0; i < n; i++) {
        mainDiagonal = mainDiagonal + grid[i][i];             // top-left to bottom-right
        secondDiagonal = secondDiagonal + grid[i][n - 1 - i]; // top-right to bottom-left
    }
    printf("\nMain diagonal sum      : %d\n", mainDiagonal);
    printf("Secondary diagonal sum : %d\n", secondDiagonal);
    if (mainDiagonal == secondDiagonal) {
        printf("The diagonal totals are balanced.\n");
    }

    //Boundary cells 
    int boundaryTotal = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
                boundaryTotal = boundaryTotal + grid[i][j];
            }
        }
    }
    printf("Boundary total         : %d\n", boundaryTotal);

    //Local hotspots
    int hotspots = 0;
    printf("\nLocal hotspots:\n");
    for (i = 1; i < n - 1; i++) {
        for (j = 1; j < n - 1; j++) {
            if (grid[i][j] > grid[i - 1][j] &&   // top
                grid[i][j] > grid[i + 1][j] &&   // bottom
                grid[i][j] > grid[i][j - 1] &&   // left
                grid[i][j] > grid[i][j + 1] &&   // right
                grid[i][j] >= t) {
                printf("  Row %d, Column %d (score %d)\n", i + 1, j + 1, grid[i][j]);
                hotspots++;
            }
        }
    }
    if (hotspots == 0) {
        printf("  No local hotspot found.\n");
    }

    // Final decision
    printf("\nFinal status: ");
    if (hotspots > 0) {
        printf("CRITICAL\n");
    } else if (countAboveT >= n) {
        printf("WARNING\n");
    } else {
        printf("NORMAL\n");
    }

    return 0;
}
