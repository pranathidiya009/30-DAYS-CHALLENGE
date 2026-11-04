#include <stdio.h>
#define ROWS 5
#define COLS 8

void initializeSeats(int seats[ROWS][COLS]);
void displaySeats(int seats[ROWS][COLS]);
int bookSeat(int seats[ROWS][COLS], int row, int col);
int cancelSeat(int seats[ROWS][COLS], int row, int col);
int reserveGroup(int seats[ROWS][COLS], int groupSize);
void displayReport(int seats[ROWS][COLS]);
int isValidSeat(int row, int col);

int main(void) {
    int seats[ROWS][COLS];
    int choice = 0, row, col, groupSize;

    initializeSeats(seats);

    while (choice != 6) {
        printf("\n--- SEATSMART ---\n");
        printf("1. Display seats\n");
        printf("2. Book one seat\n");
        printf("3. Cancel booking\n");
        printf("4. Group reservation\n");
        printf("5. Occupancy report\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            displaySeats(seats);
        }
        else if (choice == 2) {
            printf("Enter row and seat: ");
            scanf("%d %d", &row, &col);
            if (bookSeat(seats, row, col)) {
                displaySeats(seats);
            } else {
                printf("Cannot book this seat.\n");
            }
        }
        else if (choice == 3) {
            printf("Enter row and seat: ");
            scanf("%d %d", &row, &col);
            if (cancelSeat(seats, row, col)) {
                displaySeats(seats);
            } else {
                printf("Cannot cancel this seat.\n");
            }
        }
        else if (choice == 4) {
            printf("Enter group size: ");
            scanf("%d", &groupSize);
            if (reserveGroup(seats, groupSize)) {
                displaySeats(seats);
            } else {
                printf("Cannot reserve group.\n");
            }
        }
        else if (choice == 5) {
            displayReport(seats);
        }
        else if (choice == 6) {
            printf("Goodbye!\n");
        }
        else {
            printf("Invalid choice. Enter 1-6.\n");
        }
    }

    return 0;
}

// Row must be 1-5 and seat must be 1-8
int isValidSeat(int row, int col) {
    return row >= 1 && row <= ROWS && col >= 1 && col <= COLS;
}

// Set every seat to 0 (available)
void initializeSeats(int seats[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            seats[i][j] = 0;
        }
    }
}

// Print the seat grid with a legend
void displaySeats(int seats[ROWS][COLS]) {
    printf("\n0 = Available, 1 = Booked\n");
    for (int i = 0; i < ROWS; i++) {
        printf("Row %d: ", i + 1);
        for (int j = 0; j < COLS; j++) {
            printf("%d ", seats[i][j]);
        }
        printf("\n");
    }
}

// Book one seat (1-based row and col)
int bookSeat(int seats[ROWS][COLS], int row, int col) {
    if (!isValidSeat(row, col) || seats[row - 1][col - 1] == 1) {
        return 0;
    }
    seats[row - 1][col - 1] = 1;
    return 1;
}

// Cancel one seat (1-based row and col)
int cancelSeat(int seats[ROWS][COLS], int row, int col) {
    if (!isValidSeat(row, col) || seats[row - 1][col - 1] == 0) {
        return 0;
    }
    seats[row - 1][col - 1] = 0;
    return 1;
}

// Book the first block of consecutive free seats in one row
int reserveGroup(int seats[ROWS][COLS], int groupSize) {
    if (groupSize < 2 || groupSize > COLS) {
        return 0;
    }

    for (int i = 0; i < ROWS; i++) {
        for (int start = 0; start <= COLS - groupSize; start++) {

            // Check the whole block first
            int blockFree = 1;
            for (int k = 0; k < groupSize; k++) {
                if (seats[i][start + k] == 1) {
                    blockFree = 0;
                }
            }

            // Book it only if every seat is free
            if (blockFree) {
                for (int k = 0; k < groupSize; k++) {
                    seats[i][start + k] = 1;
                }
                printf("Booked Row %d, first seat %d\n", i + 1, start + 1);
                return 1;
            }
        }
    }
    return 0;
}

// Show totals, occupancy and all busiest rows
void displayReport(int seats[ROWS][COLS]) {
    int rowCount[ROWS] = {0};
    int total = 0;
    int max = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            rowCount[i] += seats[i][j];
        }
        total += rowCount[i];
        if (rowCount[i] > max) {
            max = rowCount[i];
        }
    }

    printf("Booked: %d\n", total);
    printf("Free: %d\n", ROWS * COLS - total);
    printf("Occupancy: %.1f%%\n", total * 100.0 / (ROWS * COLS));
    printf("Busiest row(s): ");
    for (int i = 0; i < ROWS; i++) {
        if (rowCount[i] == max) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}
