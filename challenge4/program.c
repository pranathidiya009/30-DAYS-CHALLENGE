Challenge 4
Code
#include <stdio.h>

int main() {
    int days;
    float expense, totalExpense = 0.0, averageExpense = 0.0;
    float maxExpense = 0.0;
    int maxDay = 1;
    float budgetLimit = 100.0; // Define a warning threshold for high spending

    printf("--- Daily Expense Analyzer ---\n\n");
    
    // Ask user for the tracking duration
    printf("Enter the number of days to analyze: ");
    scanf("%d", &days);

    if (days <= 0) {
        printf("Invalid number of days. Exiting program.\n");
        return 1;
    }

    // Loop to collect and analyze expenses for each day
    for (int i = 1; i <= days; i++) {
        printf("Enter expense for Day %d: $", i);
        scanf("%f", &expense);

        // Accumulate total expenses
        totalExpense += expense;

        // Conditional statement to track the highest spending day
        if (expense > maxExpense) {
            maxExpense = expense;
            maxDay = i;
        }

        // Conditional statement to check if spending exceeds the budget threshold
        if (expense > budgetLimit) {
            printf("  -> Warning: High spending detected on Day %d! (Exceeded $%.2f)\n", i, budgetLimit);
        }
    }

    // Calculate average daily expense
    averageExpense = totalExpense / days;

    // Display final analysis report
    printf("\n--- Expense Analysis Summary ---\n");
    printf("Total Expenses:        $%.2f\n", totalExpense);
    printf("Average Daily Expense: $%.2f\n", averageExpense);
    printf("Highest Spending Day:  Day %d ($%.2f)\n", maxDay, maxExpense);

    return 0;
}
