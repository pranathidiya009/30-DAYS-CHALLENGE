#include <stdio.h>

int main() {
    int ticket[15];
    int n, r, i, j, id;
    int count, duplicate = 0, missing = 0;
    int duplicateCount = 0, missingCount = 0;
    int inversions = 0, target, occurrences = 0;

    /* Input N with validation */
    printf("Enter N (5 to 15): ");
    scanf("%d", &n);
    while (n < 5 || n > 15) {
        printf("Invalid! Enter N (5 to 15): ");
        scanf("%d", &n);
    }

    /* Input ticket IDs with validation */
    for (i = 0; i < n; i++) {
        printf("Enter ticket %d (1 to %d): ", i + 1, n);
        scanf("%d", &ticket[i]);
        while (ticket[i] < 1 || ticket[i] > n) {
            printf("Invalid! Enter ticket %d (1 to %d): ", i + 1, n);
            scanf("%d", &ticket[i]);
        }
    }

    /* 1. Display original sequence */
    printf("\nScan sequence: ");
    for (i = 0; i < n; i++) {
        printf("%d ", ticket[i]);
    }
    printf("\n");

    /* 2. Find missing and duplicate IDs (compare each ID with every entry) */
    for (id = 1; id <= n; id++) {
        count = 0;
        for (i = 0; i < n; i++) {
            if (ticket[i] == id) {
                count++;
            }
        }
        if (count == 0) {
            missing = id;
            missingCount++;
        } else if (count == 2) {
            duplicate = id;
            duplicateCount++;
        }
    }

    if (missingCount != 1 || duplicateCount != 1) {
        printf("Invalid scan log!\n");
        return 0;
    }

    printf("Duplicate ID: %d\n", duplicate);
    printf("Missing ID: %d\n", missing);

    /* 3. Count out-of-order pairs */
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (ticket[i] > ticket[j]) {
                inversions++;
            }
        }
    }
    printf("Out-of-order pairs: %d\n", inversions);

    /* 4. Personalised target */
    printf("Enter last two digits of your registration number: ");
    scanf("%d", &r);
    target = (r % n) + 1;

    printf("Target ID: %d\n", target);
    printf("Positions: ");
    for (i = 0; i < n; i++) {
        if (ticket[i] == target) {
            printf("%d ", i + 1);
            occurrences++;
        }
    }
    if (occurrences == 0) {
        printf("(none)");
    }
    printf("\nOccurrence count: %d\n", occurrences);

    return 0;
}
