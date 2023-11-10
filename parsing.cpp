#include "func.h"

void parsing(char* buff, char equation_variable) {
    int buff_index = 0;
    char summand_variable = 'N';
    char summand_sign = '+';
    int summand_number = 0;
    int summand_degree = 0;
    const int char_to_digit_ratio = 48;
    bool degree_error = false;

    // Начало парсинга. Пытаемся прочиать знак - (по умолчанию уже +, но все равно проверяем).
    if (buff[buff_index] == '+' || buff[buff_index] == '-') {
        if (buff[buff_index] == '-') summand_sign = '-';
        buff_index++;
    }
    // Пытаемся прочитать число.
    // Если идет сразу переменная, то число = 1.
    if ('a' <= buff[buff_index] && buff[buff_index] <= 'z') summand_number = 1;
    else {
        // Иначе начинаем читать число
        while ('0' <= buff[buff_index] && buff[buff_index] <= '9') {
            summand_number = summand_number * 10 + ((int) buff[buff_index] - char_to_digit_ratio);
            buff_index++;
        }
        if (summand_sign == '-') summand_number = 0 - summand_number;
    }
    // Пытаемся прочитать переменную.
    if ('a' <= buff[buff_index] && buff[buff_index] <= 'z') {
        summand_variable = buff[buff_index];
        buff_index++;
        summand_degree = 1;
        // Если еще не встречалось переменной, то записываем ее.
        if (equation_variable == ' ') equation_variable = summand_variable;
    }
    // Иначе продолжаем читать число
    if (buff[buff_index != '\0']) {
        // Пытаемся прочитать степень переменной.
        if (buff[buff_index] == '^') {
            buff_index++;
            if ('0' <= buff[buff_index] && buff[buff_index] <= '9') {
                summand_degree = (int) buff[buff_index] - char_to_digit_ratio;
                buff_index++;
            }
            else degree_error = true;
        }
    }

    // Вывод значение парсинга.
    printf("---------\n");
    printf("NUMBER:    %i \n", summand_number);
    if (summand_variable == 'N') printf("VARIABLE_FREE \n"); 
    else {
        printf("VARIABLE:  %c \n", summand_variable);
        if (summand_variable != equation_variable) printf("SUMMAND VARIABLE != EQUATION VARIABLE \n");
    }                                         
    printf("DEGREE:    %i \n", summand_degree);
    if (degree_error) printf("ERROR - UNCORRECT DEGREE \n");
    else if (not(0 <= summand_degree && summand_degree <= 2)) {
        printf("DEGREE DOESN'T FIT THE QUADRATIC EQUATION \n");
    }
    // Если что-то после парсинга осталось.
    if (buff[buff_index] != '\0') {
        printf("ERROR - INAPPROPRIATE INPUT \n");
    }
    printf("---------\n");

    // Чистка после парсинга
    while (buff[buff_index] != '\0') {
        buff[buff_index] = '\0';
        buff_index++;
    }
}