#include "functions.h"

struct summand parsing(char* summand, char equation_variable) {
    int buff_index = 0;
    char summand_variable = 'N';
    char summand_sign = '+';
    int summand_number = 0;
    int summand_degree = 0;
    char summand_degree_err = ' ';
    int summand_error = 0;
    const int char_to_digit_ratio = 48;

    // Начало парсинга. Пытаемся прочиать знак - (по умолчанию уже +, но все равно проверяем).
    if (summand[buff_index] == '+' || summand[buff_index] == '-') {
        if (summand[buff_index] == '-') summand_sign = '-';
        buff_index++;
    }
    // Пытаемся прочитать число.
    // Если идет сразу переменная, то число = 1.
    if ('a' <= summand[buff_index] && summand[buff_index] <= 'z') {
        if (summand_sign == '+') summand_number = 1;
        else summand_number = -1;
    }
    else {
        // Иначе начинаем читать число
        while ('0' <= summand[buff_index] && summand[buff_index] <= '9') {
            summand_number = summand_number * 10 + ((int) summand[buff_index] - char_to_digit_ratio);
            buff_index++;
        }
        if (summand_sign == '-') summand_number = 0 - summand_number;
    }
    // Пытаемся прочитать переменную.
    if ('a' <= summand[buff_index] && summand[buff_index] <= 'z') {
        summand_variable = summand[buff_index];
        buff_index++;
        summand_degree = 1;
        // Если еще не встречалось переменной, то записываем ее.
        if (equation_variable == ' ') equation_variable = summand_variable; 
    }
    // Иначе продолжаем читать число
    if (summand[buff_index != '\0']) {
        // Пытаемся прочитать степень переменной.
        if (summand[buff_index] == '^') {
            buff_index++;
            if ('0' <= summand[buff_index] && summand[buff_index] <= '9') {
                summand_degree = (int) summand[buff_index] - char_to_digit_ratio;
                buff_index++;
            }
            else {
                summand_degree_err = summand[buff_index];
                buff_index++;
            }
        }
    }

    // Вывод слагаемого. ФУНКЦИЯ ОТЛАДКИ
    if (DEBUG_FUNC) {
        printf("---------\n");
        printf("%s \n", summand);
    }
    
    // Вывод значение парсинга. ФУНКЦИЯ ОТЛАДКИ
    if (DEBUG_FUNC) {
        printf("---------\n");
        printf("NUMBER:    %i \n", summand_number);
        if (summand_variable == 'N') 
            printf("VARIABLE_FREE \n"); 
        else printf("VARIABLE:  %c \n", summand_variable);                                     
        printf("DEGREE:    %i \n", summand_degree);
    }

    // Обработка ошибок
    if (summand[buff_index] != '\0') {
        summand_error = 1;          // Ошибка №1 (не критичная)
    }
    if ((summand[0] == '+' || summand[0] == '-') && summand[1] == '\0') {
        summand_error = 2;          // Ошибка №2 (не критичная)
    }
    if (summand_variable != 'N' && summand_variable != equation_variable) {
        summand_error = 3;          // Ошибка №3 (критичная)
    }
    if (summand_degree_err != ' ') {
        summand_error = 4;          // Ошибка №4 (не критичная)
    }
    if (not(0 <= summand_degree && summand_degree <= 2)) {
        summand_error = 5;          // Ошибка №5 (не критичная)
    }

    // Чистка после парсинга
    // while (buff[buff_index] != '\0') {
    //     buff[buff_index] = '\0';
    //     buff_index++;
    // }

    struct summand curr_summand = {
        summand_variable,
        summand_number,
        summand_degree,
        summand_error
    };
    return curr_summand;
}