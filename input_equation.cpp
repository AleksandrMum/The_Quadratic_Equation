#include "common.h"
#include "utilites.h"
#include "input_equation.h"

bool input_equation(char* curr_equation) {
    assert(curr_equation && "input_equation() didn't receive an address");
    
    bool is_input_successful = true;

    size_t curr_equation_len = 0;
    bool is_equation_empty = true;
    
    char char_input = ' ';
    while (curr_equation_len < max_len_of_user_input - 1) {
        char_input = (unsigned char) getchar();

        if (!is_input_char_allowed(char_input)) {
            printf("Symbol %c \n", char_input);
            print_warning(W_UNEXPECTED_SYMBOL);
            continue;
        }
        else if (char_input == '\n') {
            curr_equation[curr_equation_len] = '\0';
            break;
        }
        else if (char_input == ' ') 
            continue;
        else if (char_input == '+' || char_input == '-') {
            if (curr_equation[curr_equation_len - 1] == '+' || curr_equation[curr_equation_len - 1] == '-') {
                if (curr_equation[curr_equation_len - 1] == char_input) 
                    curr_equation[curr_equation_len - 1] = '+';
                else 
                    curr_equation[curr_equation_len - 1] = '-';
                continue;
            }
            else if (curr_equation[curr_equation_len - 1] != ' ') {
                curr_equation[curr_equation_len] = ' ';
                curr_equation_len++;
            }
            curr_equation[curr_equation_len] = char_input;
            curr_equation_len++;
        }
        else if (char_input == '=') {
            curr_equation[curr_equation_len] = ' ';
            curr_equation_len++;
            curr_equation[curr_equation_len] = char_input;
            curr_equation_len++;
            curr_equation[curr_equation_len] = ' ';
            curr_equation_len++;
        }
        else {
            curr_equation[curr_equation_len] = char_input;
            curr_equation_len++;
            is_equation_empty = false;
        }
    }

    if (is_equation_empty) {
        print_warning(E_EMPTY_EQUATION);
        is_input_successful = false;
    }

#ifndef NDEBUG
    if (is_input_successful) {
        printf("---------\n");
        print_equation(curr_equation);
    }
#endif

    return is_input_successful;
}

bool is_input_char_allowed(char input_char) {
    if (
        ('0' <= input_char && input_char <= '9') ||
        ('a' <= input_char && input_char <= 'z') ||
         input_char == '+' || input_char == '-'  ||
         input_char == '=' || input_char == '^'  ||
         input_char == ' ' || input_char == '\n' ||
         input_char == '.'
       ) return true;
    else return false;
}