#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool is_positive_integer(char *str) {
    // Check if the string is empty
    if (str == NULL || strlen(str) == 0) {
        return false; // empty string
    }

    // Check if the string is a digit
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false; 
        }
    }
    return true; // positive integer
}

int main(int argc, char *argv[]) {

    // initialize random number generator
    srand(time(NULL));

    // check only 2 arguments are given
    if (argc != 3) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc-1);
        return 0;
    }

    // Convert arguments to integers
    int digits[2];   
    for(int i = 1; i < argc; i++) {
        if(!is_positive_integer(argv[i])) {
            printf("Incorrect usage. The parameters you provided are not positive integers\n");
            return 0;
        }
        digits[i-1] = strtol(argv[i], NULL, 10);  // convert string to integer
    }

    int rows = digits[0];
    int columns = digits[1];
    
    srand(time(NULL)); // seed the random number generator

    // Create and populate the matrix with random numbers
    int matrix[rows][columns];
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            int random_number = (rand() % 100) + 1;
            matrix[i][j] = random_number;
        }
    }

    // Open file for writing
    FILE *file = fopen("matrix.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 0;
    }

    // Write the matrix to the file
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j < columns - 1) {
                fprintf(file, " ");  // Print space between numbers, except after the last number
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);

    return 0;
}