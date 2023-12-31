#include "common.h"
#include "utilites.h"
#include "parsing_equation.h"


struct equation get_equation_values(char* curr_equation) {
    assert(curr_equation && "get_equation_values() didn't receive an address");
    
    size_t curr_equation_len = strlen(curr_equation);
    char curr_equation_variable = ' ';
    double curr_equation_A = 0;
    double curr_equation_B = 0;
    double curr_equation_C = 0;
    bool equation_error = false;

    char curr_summand[max_len_of_user_input] = {'\0'};
    char summand_buff_char = '0';
    bool summand_num_reverse = false;

    size_t summand_buff_len = 0;
    for (size_t curr_equation_index = 0; curr_equation_index <= curr_equation_len; curr_equation_index++) {
        summand_buff_char = curr_equation[curr_equation_index];

        if (summand_buff_char != '\0' && summand_buff_char != ' ' && summand_buff_char != '=') {
            curr_summand[summand_buff_len] = summand_buff_char;
            summand_buff_len++;
        }
        else if (summand_buff_char == '=') 
                summand_num_reverse = true;
        else if (summand_buff_char == ' ' || summand_buff_char == '\0') {
            if (summand_buff_char == ' ' && summand_buff_len == 0) 
                continue;
            else if (summand_buff_char == '\0' && summand_buff_len == 0) 
                break;
            // Работа со значениями 
            struct summand temp_summand = parsing_summand(curr_summand);
            summand_buff_len = clean_string(curr_summand);
            if (curr_equation_variable == ' ' && temp_summand.variable != 'N') 
                curr_equation_variable = temp_summand.variable;
            if (temp_summand.variable != 'N' && temp_summand.variable != curr_equation_variable) {
                equation_error = true;
                printf("---------\n");
                print_warning(E_TWO_VARIABLES);
                return {' ', 0, 0, 0, equation_error};
            }
            if (summand_num_reverse) 
                temp_summand.number = 0 - temp_summand.number;

            if (temp_summand.degree == 2) 
                curr_equation_A += temp_summand.number;
            else if (temp_summand.degree == 1)
                curr_equation_B += temp_summand.number;
            else if (temp_summand.degree == 0)
                curr_equation_C += temp_summand.number;
        } 
        else printf("\n --- \n UNEXPECTED BEHAVIOR \n --- \n");
    }
    if (curr_equation_variable == ' ') {
        equation_error = true;
        printf("---------\n");
        print_warning(E_ZERO_VARIABLES);
        return {' ', 0, 0, 0, equation_error};
    }
    return {
        curr_equation_variable,
        curr_equation_A,
        curr_equation_B,
        curr_equation_C,
        equation_error
    };
}



struct summand parsing_summand(char* curr_summand) {
    char summand_variable = 'N';
    char summand_sign = '+';
    double summand_number = 0;
    int summand_degree = 0;
    int summand_decimal_len = 0;
    int summand_error = 0;

    int curr_summand_index = 0;
    if (curr_summand[curr_summand_index] == '+' || curr_summand[curr_summand_index] == '-') {       // Проверка знака
        if (curr_summand[curr_summand_index] == '+') 
            summand_sign = '+';
        else 
            summand_sign = '-';
        curr_summand_index++;
    }
    if (is_char_letter(curr_summand[curr_summand_index])) {                         // Проверка переменную без числа
        if (summand_sign == '+') 
            summand_number = 1;
        else 
            summand_number = -1;
        summand_degree = 1;
    }
    else {                                                                          // Проверка число
        while (is_char_number(curr_summand[curr_summand_index])) {
            summand_number = summand_number * 10 + (char_to_int(curr_summand[curr_summand_index]));
            curr_summand_index++;
        }
        if (summand_sign == '-') 
            summand_number = 0 - summand_number;
    }
    if (curr_summand[curr_summand_index] == '.') {                                  // Проверка десятичную часть
        curr_summand_index++;
        summand_decimal_len++;
        while (is_char_number(curr_summand[curr_summand_index])) {
            summand_number += (double) (char_to_int(curr_summand[curr_summand_index])) / (10 * summand_decimal_len);
            curr_summand_index++;
            summand_decimal_len++;
        }
    }
    if (is_char_letter(curr_summand[curr_summand_index])) {                         // Проверка переменную после числа
        summand_variable = curr_summand[curr_summand_index];
        curr_summand_index++;
        summand_degree = 1;
    }
    if (curr_summand[curr_summand_index] == '^') {                                  // Проверка степени
        curr_summand_index++;
        if (is_char_number(curr_summand[curr_summand_index])) {
            summand_degree = char_to_int(curr_summand[curr_summand_index]);
            curr_summand_index++;
        }
        else {
            print_warning(W_INCORRECT_DEGREE);
            curr_summand_index++;
        }
    }
    // Уведомление о возможных несоответствиях
    if (curr_summand[curr_summand_index] != '\0') {
        print_warning(W_IRRELEVANT_SUMMAND);
    }
    if (!(0 <= summand_degree && summand_degree <= 2)) {
        print_warning(W_DEGREE_NOT_FIT_EQUATION);
    }

// В дебагге просмотр значения слагаемого перед их возвратом
#ifndef NDEBUG
    printf("---------\n");
    printf("SUMMAND:   %s \n", curr_summand);
    printf("NUMBER:    %lf \n", summand_number);
    if (summand_variable == 'N') 
        printf("VARIABLE_FREE \n"); 
    else 
        printf("VARIABLE:  %c \n", summand_variable);                                     
    printf("DEGREE:    %i \n", summand_degree);
#endif

    return {
        summand_variable,
        summand_number,
        summand_degree,
        summand_error
        };
}