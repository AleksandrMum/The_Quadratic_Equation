#include <stdio.h>
#include "functions.h"

// #define NDEBUG

int main() {
    // Ввод уравнения, получение из него значений
    printf("Enter an equation (up to %i characters): \n", MAX_LEN_OF_USER_INPUT);
    printf("The equation should be in the following format: ax^2 + bx + c = 0 (= dx^2 + ex + f) \n");
    struct equation curr_equation = get_values_of_equation();


    if (curr_equation.critical_error) {
        printf("CRITICAL ERROR \n");
    }
    else {
        printf("Variable: %c \n", curr_equation.variable);
        printf("A: %i \n", curr_equation.a);
        printf("B: %i \n", curr_equation.b);
        printf("C: %i \n", curr_equation.c);
        printf("---------\n");
    }


    getchar();
}
