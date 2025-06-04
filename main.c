#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLEAR_CONSOLE "\033[H\033[J"

int checkIfValid(char* input, char validInputs[][20], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(input, validInputs[i]) == 0) {
            return 1; // Valid input
        }
    }
    return 0; // Invalid input
}

void printStrArr(char arr[][20], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf(CLEAR_CONSOLE);
    char symbol[20];
    char period[20];
    char interval[20];
    char command[200];
    char validPeriods[][20] = {"1d", "5d", "1mo", "3mo", "6mo", "1y", "2y", "5y", "10y", "ytd", "max"};
    char validIntervals[][20] = {"1m", "2m", "5m", "15m", "30m", "60m", "90m", "1h", "1d", "5d", "1wk", "1mo", "3mo"};
    // Get user input
    printf("Enter stock symbol (e.g., AAPL): ");
    scanf("%s", symbol);
    
    do
    {
        printf("Enter period (e.g., 1mo, 3mo, 1y): ");
        scanf("%s", period);
        if (!checkIfValid(period, validPeriods, sizeof(validPeriods) / sizeof(validPeriods[0]))) {
            printf("Invalid period\n");
            printf("Valid periods are: ");
            printStrArr(validPeriods, sizeof(validPeriods) / sizeof(validPeriods[0]));
        }
    } while(!checkIfValid(period, validPeriods, sizeof(validPeriods) / sizeof(validPeriods[0])));

    
    
    
    do
    {
        printf("Enter Interval (e.g., 1m, 1h, 1d): ");
        scanf("%s", interval);
        if (!checkIfValid(interval, validIntervals, sizeof(validIntervals) / sizeof(validIntervals[0]))) {
            printf("Invalid Interval\n");
            printf("Valid intervals are: ");
            printStrArr(validIntervals, sizeof(validIntervals) / sizeof(validIntervals[0]));
        }
    } while(!checkIfValid(interval, validIntervals, sizeof(validIntervals) / sizeof(validIntervals[0])));
    
    // Create command to call Python script
    sprintf(command, "python3 API/fetch_data.py %s %s %s", symbol, period, interval);
    
    // Execute Python script
    printf("\nFetching stock data...\n");
    printf(CLEAR_CONSOLE);
    system(command);
    
    return 0;
}