#include <stdio.h>

#include "common.h"
#include "utilites.h"

#include "input_equation.h"
#include "parsing_equation.h"
#include "solve_equation.h"

// #define NDEBUG

int main() {
    print_instruction();

    char curr_equation[max_len_of_user_input] = {};
    bool scan_successful = true;

    do {
        printf("Enter an equation (up to %llu characters): \n", max_len_of_user_input);

        scan_successful = input_equation(curr_equation);
        if (!scan_successful) {
            printf("SCAN ERROR \n");
        }
        else {
            struct equation curr_equation_values = get_equation_values(curr_equation);
            if (curr_equation_values.eq_error) {
                printf("SOLVE IMPOSSIBLE \n");
            }
            else {
                printf("---------\n");
                printf("Value A: %lf \n", curr_equation_values.a);
                printf("Value B: %lf \n", curr_equation_values.b);
                printf("Value C: %lf \n", curr_equation_values.c);
                printf("---------\n");
                struct roots curr_roots = get_equation_roots(&curr_equation_values);
                if (curr_roots.linear_equation)
                    printf("Linear equation \nRoot: %lf \n", curr_roots.root_1);
                else if (curr_roots.negative_discriminant)
                    printf("Discriminant is negative \nNo roots \n");
                else {
                    printf("Discriminant: %lf \n", curr_roots.discriminant);
                    printf("Root 1: %lf \n", curr_roots.root_1);
                    printf("Root 2: %lf \n", curr_roots.root_2); 
                }
            }
        }

    } while (is_there_new_equation()); 

    return 0;
}
