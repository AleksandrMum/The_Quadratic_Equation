#include <stdio.h>

#include "common.h"
#include "utilites.h"

#include "input_equation.h"
#include "parsing_equation.h"

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
        }

    } while (is_there_new_equation()); 

    return 0;
}
