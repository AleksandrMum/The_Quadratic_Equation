#include <stdio.h>
#include "functions.h"

// #define NDEBUG

int main() {
    printf("This program solves quadratic equations \n");
    printf("The equation should be in the following format: \n");
    printf("ax^2 + bx + c (= 0) (or = dx^2 + ex + f) \n");
    printf("All coefficients must be integers or decimals written through a dot \n\n");

    char program_work = 'y';
    do {
        printf("Enter an equation (up to %i characters): \n", MAX_LEN_OF_USER_INPUT);
        solution_of_equation();
        printf("\nEnter 'y' to continue - ");
        program_work = (char) getchar();
        getchar(); // Костыль, чтобы можно было ввести y + \n
    } while (program_work == 'y'); 
}
