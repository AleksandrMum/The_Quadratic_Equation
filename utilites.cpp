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
    printf("You input equation: ");
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
    if (-0.00001 < number && number < 0.00001) return true;
    else return false;
}

void print_warning(int warning_code) {
    switch (warning_code)
    {
    case W_UNEXPECTED_SYMBOL:   printf("WARNING - Unresolved char detected \n");            
                                break;
    case E_EMPTY_EQUATION:      printf("ERROR - Empty input instead of an equation \n");
                                break;
    
    
    default: printf("Unknown warning/error... \n");
    }
}

int clean_string(char* string) {
    size_t index = 0;
    while (string[index] != '\0') {
        string[index] = '\0';
        index++;
    }
    return 0;
}