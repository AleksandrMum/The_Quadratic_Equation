#include "common.h"
#include "utilites.h"

// Печатает пользователю инструкцию по вводу уравнений
void print_instruction() {
    printf("This program solves quadratic equations \n"
            "The equation should be in the following format: \n"
            "ax^2 + bx + c (= 0) (or = dx^2 + ex + f) \n"
            "All coefficients must be integers or decimals written through a dot \n\n"
            );
}

void print_equation(char* curr_equation) {
    printf("You input equation: \n");
    size_t index = 0;
    while (curr_equation[index] != '\0') {
        printf("%c", curr_equation[index]);
        index++;
    }
    printf(" \n");
}

// Принимает у пользователя ответ, продолжить ли ввод нового уравнения
bool is_there_new_equation() {
    bool user_ans = false;
    printf("\n" "Enter 'y' to continue - ");
    if (getchar() == 'y') 
        user_ans = true;
    else
        user_ans = false;

    while (getchar() != '\n') ;
    return user_ans;
}

bool is_double_zero(double number) {
    if (-0.00001 < number && number < 0.00001) 
        return true;
    else 
        return false;
}

int clean_string(char* string) {
    size_t index = 0;
    while (string[index] != '\0') {
        string[index] = '\0';
        index++;
    }
    return 0;
}

void print_warning(int warning_code) {
    switch (warning_code)
    {
    case W_UNEXPECTED_SYMBOL:       printf("WARNING - Unresolved char detected \n");            
                                    break;
    case E_EMPTY_EQUATION:          printf("ERROR - Empty input instead of an equation \n");
                                    break;
    case W_IRRELEVANT_SUMMAND:      printf("WARNING - Summand does not match the input conditions \n");
                                    break;
    case W_INCORRECT_DEGREE:        printf("WARNING - Summand has uncorrect degree (char instead of number) \n");
                                    break;
    case W_DEGREE_NOT_FIT_EQUATION: printf("WARNING - Summand has degree that doesn't fit quadratic equation \n");
                                    break;
    case E_TWO_VARIABLES:           printf("ERROR - Two variables in one equation \n");
                                    break;
    case E_ZERO_VARIABLES:          printf("ERROR - Equation without variables is introduced \n");
                                    break;
        
    
    default: printf("Unknown warning/error... \n");
    }
}

bool is_char_number(char curr_char) {
    if ('0' <= curr_char && curr_char <= '9')
        return true;
    else
        return false;
}

bool is_char_letter(char curr_char) {
    if ('a' <= curr_char && curr_char <= 'z')
        return true;
    else
        return false;
}

int char_to_int(char number) {
    return ((int) number - char_to_digit_ratio);
}
