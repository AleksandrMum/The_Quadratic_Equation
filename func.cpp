#include "func.h"
#define MAX_LEN_OF_USER_INPUT 100


struct equation scan_string_with_equation() {
    char user_input[MAX_LEN_OF_USER_INPUT] = {};

    int len_of_user_input = 0;
    char buff_input = 'B';
    while (len_of_user_input < MAX_LEN_OF_USER_INPUT) {
        buff_input = getchar();
        if (buff_input == '\n') break;
        if (buff_input == ' ') continue;
        user_input[len_of_user_input] = buff_input;
        len_of_user_input++;
    }

    struct equation curr_equation = process_equation(user_input, len_of_user_input);

    return curr_equation;
}

struct equation process_equation(char* user_input, int len_of_user_input) {
    // Пришло ли вообще что-то функции
    assert(user_input && "Функции не пришел адрес строки.\n");
    assert(len_of_user_input && "Длина строки равна 0");

    // Переменная для чтения по общему списку символов user_input
    char curr_symbol = ' ';
    
    // Переменные для хранения данных об уравнении.
    char equation_variable = ' ';
    int equation_a = 0;
    int equation_b = 0;
    int equation_c = 0;

    // Переменные для временного хранения данных о слагаемом
    char buff[MAX_LEN_OF_USER_INPUT] = {};
    int buff_len = 0;
    int buff_index = 0;
    // По умолчанию summand_type = 0. Если найдется переменная в слагаемом, то степень переменной станет 1, а если ^2, то 2.
    char summand_variable = ' ';
    char summand_sign = '+';
    bool summand_sign_invertion = false;
    int summand_number = 0;
    int summand_degree = 0;
    const int char_to_digit_ratio = 48;

    for (int user_input_index = 0; user_input_index < len_of_user_input; user_input_index++) {
        curr_symbol = user_input[user_input_index];
        // TODO test
        printf("SYMBOL - %c \n", curr_symbol);
        // Пока не наткнулись на "управляющий" уравнением символ, читаем слагаемое из user_input
        if (curr_symbol != '+' && curr_symbol != '-' && curr_symbol != '=' && curr_symbol != '\0') {
            buff[buff_len] = curr_symbol;
            buff_len++;
        }
        else {
            // TODO test
            printf("---------\n");
            printf("EQUATION - %s \n", buff);
            printf("---------\n");
            // Если "управляющий" символ появился до слагаемого (в начале или сразу после "=")
            if (buff_len == 0) {
                // ... то либо сначала фиксируем знак слагаемого ...
                if (curr_symbol == '+' || curr_symbol == '-') summand_sign = curr_symbol;
                // ... либо сбрасываем знак до "+" и начинаем инвертировать его ...
                if (curr_symbol == '=') {
                    summand_sign = '+';
                    summand_sign_invertion = true;
                }
                // ... либо выходим из цикла ...
                if (curr_symbol == '\0') break;
                // либо просто продолжаем чтение.
                continue;
            }
            // Иначе начинаем парсировать слагаемое (число - переменная - степень)
            else {
                // Если мы сразу натыкаемся на переменную - коэффициент при ней 1.
                if ('a' <= buff[buff_index] && buff[buff_index] <= 'z') summand_number = 1;
                else {
                    // Иначе начинаем читать число
                    while ('0' <= buff[buff_index] && buff[buff_index] <= '9') {
                        summand_number = summand_number * 10 + ((int) buff[buff_index] - char_to_digit_ratio);
                        buff_index++;
                    }
                }
                // TODO test
                printf("NUMBER - %i \n", summand_number);
                // Если слагаемое закончилось, то это 0 степень.
                if (buff[buff_index] == '\0') summand_degree = 0;
                
                // Иначе продолжаем читать уравнение.
                else {
                    // Пытаемся прочитать переменную.
                    if ('a' <= buff[buff_index] && buff[buff_index] <= 'z') {
                        summand_variable = buff[buff_index];
                        buff_index++;
                        // Если еще не встречалось переменной, то записываем ее
                        if (equation_variable == ' ') equation_variable = summand_variable;
                    }
                    // Если слагаемое закончилось, то это 1 степень. Увеличиваем equation_c
                    if (buff[buff_index] == '\0') summand_degree = 1;

                    // Иначе продолжаем читать число
                    else {
                        // Пытаемся прочитать степень переменной.
                        if (buff[buff_index] == '^') {
                            buff_index++;
                            if ('0' <= buff[buff_index] && buff[buff_index] <= '9') {
                                summand_degree = (int) buff[buff_index] - char_to_digit_ratio;
                                buff_index++;
                            }
                        }
                    }
                }
                // TODO test
                printf("VARIABLE - %c \n", summand_variable);
                printf("DEGREE - %i \n", summand_degree);
                printf("---------\n");
                // Если слагаемое закончилось, начинаем обрабатывать полученные значения.
                if (buff[buff_index] == '\0') {
                    // Если переменная слагаемого не совпадает с общей переменной, Ошибка №2
                    if (summand_variable != equation_variable) {
                        struct equation curr_eq = {' ', 0, 0, 0, 2};
                        return curr_eq;
                    }
                    // Если степень слагаемого не 0-2, Ошибка №3
                    if (not(0 <= summand_degree && summand_degree <= 2)) {
                        struct equation curr_eq = {' ', 0, 0, 0, 3};
                        return curr_eq;
                    }
                }
                // Если слагаемое не закончилось, то какая-то его часть некорректно считалась. Ошибка №1.
                else {
                    struct equation curr_eq = {' ', 0, 0, 0, 1};
                    return curr_eq;
                }
            }
            // Фиксируем знак слагаемого ...
            if (curr_symbol == '+' || curr_symbol == '-') summand_sign = curr_symbol;
            // ... либо сбрасываем знак до "+" и начинаем инвертировать его ...
            if (curr_symbol == '=') {
                summand_sign = '+';
                summand_sign_invertion = true;
            }
            // Обнуление buff
            for (int i = 0; buff[i] != '\0'; i++){
                buff[i] = '\0';
            }
            buff_len = 0;
            buff_index = 0;

            summand_variable = ' ';
            summand_number = 0;
            summand_degree = 0;
        }
    }

    // Иначе, если все верно, возвращаем структуру значений уравнения
    struct equation curr_eq = {equation_variable, equation_a, equation_b, equation_c, 0};
    return curr_eq;
}