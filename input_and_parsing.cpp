#include "functions.h"


// Функция, считывающая уравнение и возвращающая значения a, b, c уравнения
struct equation get_values_of_equation() {

    // Объявляю значения уравнения, которые буду потом возвращать
    char equation_variable = ' ';
    double equation_a = 0;
    double equation_b = 0;
    double equation_c = 0;
    bool critical_error = false;

    // Число слагаемых. По нему смотрю пустой ввод (если вводятся управляющие символы - ошибка №6)
    bool is_summand_in_equation = false;

    // После знака равно инвертируем числа
    bool equation_reverse = false;

    // Объявляю строку, в которой будет лежать принятое уравнение
    //NOTE - в будущем реализовать через calloc
    char string_input[MAX_LEN_OF_USER_INPUT] = {'\0'};
    size_t string_input_len = 0;

    // Чтение строки и запись в определенном формате.
    char char_input = ' ';
    while (string_input_len < MAX_LEN_OF_USER_INPUT - 1) {
        char_input = (unsigned char) getchar();
        // Если ввод уравнения завершен, вставляем \0 и выходим из цикла
        if (char_input == '\n') {
            string_input[string_input_len] = '\0';
            break;
        }
        // Если введен пробел, игнорируем его, программа сама расставляет в нужных местах пробелы
        else if (char_input == ' ') continue;
        // Если введен +/-, то смотрим на предыдущие символы
        else if (char_input == '+' || char_input == '-') {
            // Если предыдущий символ также является знаком +/- то сокращаем их по правилам математики
            if (string_input[string_input_len - 1] == '+' || string_input[string_input_len - 1] == '-') {
                if (string_input[string_input_len - 1] == char_input) string_input[string_input_len - 1] = '+';
                else string_input[string_input_len - 1] = '-';
                continue;
            }
            // Иначе если предыдущий символ не пробел (разделяющий слагаемые), добавляем его
            else if (string_input[string_input_len - 1] != ' ') {
                string_input[string_input_len] = ' ';
                string_input_len++;
            }
            // 
            string_input[string_input_len] = char_input;
            string_input_len++;
        }
        // Если введен знак "=", то проставляем пробелы вокруг него 
        else if (char_input == '=') {
            string_input[string_input_len] = ' ';
            string_input_len++;
            string_input[string_input_len] = char_input;
            string_input_len++;
            string_input[string_input_len] = ' ';
            string_input_len++;
        }
        else {
            string_input[string_input_len] = char_input;
            string_input_len++;
            is_summand_in_equation = true;
        }
    }

    // Если в уравнении нет ни одного полноценного слагаемого, возвращаем ошибку №6
    if (not(is_summand_in_equation)) {
        print_warning_error(6);
        struct equation curr_equation = {' ', 0, 0, 0, true};
        return curr_equation;
    }

    // Работа со слагаемыми
    char buff_char = '0';
    char summand_buff[MAX_LEN_OF_USER_INPUT] = {'\0'};
    size_t summand_buff_len = 0;
    for (size_t index = 0; index <= string_input_len; index++) {
        // Текущий символ по строке с уравнением
        buff_char = string_input[index];

        // Если не наткнулись на "управляющий" символ (по которому отслеживаю слагаемые), записываю слагаемое
        if (buff_char != '\0' && buff_char != ' ' && buff_char != '=') {
            summand_buff[summand_buff_len] = buff_char;
            summand_buff_len++;
        }

        // Если наткнулись на +/-, подготавливаю передачу слагаемого в parcing()
        else if (buff_char == ' ' || buff_char == '\0') {

            // Проверить на попытку передачи пустого summand_buff
            if (buff_char == ' ' && summand_buff_len == 0) continue;
            else if (buff_char == '\0' && summand_buff_len == 0) break;

            // Получаю значения слагаемого, чищу за ним summand_buff
            struct summand temp_summand = parsing(summand_buff, equation_variable);
            clean_array(summand_buff);
            summand_buff_len = 0;

            // Если еще не встречалась переменная, единожды записываю ее (только если не вернулось "N")
            if (equation_variable == ' ' && temp_summand.variable != 'N') {
                equation_variable = temp_summand.variable;
            }
            // Если случилась ошибка №3, уведомляем об этом и прекращаем сканирование уравнения
            if (temp_summand.error == 3) {
                equation_variable = ' ';
                equation_a = 0;
                equation_b = 0;
                equation_c = 0;
                critical_error = true;
                print_warning_error(temp_summand.error);
                break;
            }
            // Если случились warning, то уведомляю, но продолжаю сканирование
            else if (temp_summand.error != 0) {
                print_warning_error(temp_summand.error);
                continue;
            }
            // Если слагаемое корректно отсканировано, увеличиваю соответствующий коэффициент на значение слагаемого
            else {
                if (temp_summand.degree == 2) {
                    if (equation_reverse) equation_a -= temp_summand.number;
                    else equation_a += temp_summand.number;
                }
                else if (temp_summand.degree == 1) {
                    if (equation_reverse) equation_b -= temp_summand.number;
                    else equation_b += temp_summand.number;
                }
                else if (temp_summand.degree == 0) {
                    if (equation_reverse) equation_c -= temp_summand.number;
                    else equation_c += temp_summand.number;
                }
                else printf("\n --- \n UNEXPECTED BEHAVIOR \n --- \n");
            }
        }
        // Если наткнулись на = начинаем инвертировать знак числа
        else if (buff_char == '=') {
            equation_reverse = true; 
        }
        // Я не уверен, когда это может быть вызвано, но на всякий случай оставил
        else printf("\n --- \n UNEXPECTED BEHAVIOR \n --- \n");
    }

    // Если введено не уравнение (a == 0 и b == 0) то ошибка №7 
    if (is_double_zero(equation_a) && is_double_zero(equation_b) && not(critical_error)) {
        equation_variable = ' ';
        equation_a = 0;
        equation_b = 0;
        equation_c = 0;
        critical_error = true;
        print_warning_error(7);
    }
 
    // Возвращаю значения всего уравнение - a,b,c , символ переменной и состояние критической ошибки.
    struct equation curr_equation = {
        equation_variable,
        equation_a,
        equation_b,
        equation_c,
        critical_error
        };
    printf("---------\n");
    return curr_equation;
}

// Функция для очистки списка
void clean_array(char* array) {
    size_t index = 0;
    while (array[index] != '\0') {
        array[index] = '\0';
        index++;
    }
}

// Функция для вывода ошибок/предупреждений на экран
void print_warning_error(int error) {
    if (error == 0) printf("UNEXPECTED BEHAVIOR - Function is called without detecting an error \n");

    else if (error == 1) printf("WARNING - Inappropriate input of a summand \n");
    else if (error == 2) printf("WARNING - The summand was implied but not introduced \n");
    else if (error == 3) printf("ERROR - There are two variables in the equation \n");
    else if (error == 4) printf("WARNING - Uncorrect degree \n");
    else if (error == 5) printf("WARNING - The degree does not fit the quadratic equation \n");
    else if (error == 6) printf("ERROR - Blank line is entered \n");
    else if (error == 7) printf("ERROR - It's not an equation \n");
    
    else printf("UNEXPECTED BEHAVIOR - An unknown error has occurred \n");
}

// Функция парсинга слагаемого на его значение, символ переменной и степень переменной
struct summand parsing(char* summand, char equation_variable) {

    // Переменная, по которй будем читать строку
    int buff_index = 0;

    // Данные слагаемого
    char summand_variable = 'N';
    char summand_sign = '+';
    double summand_number = 0;
    int summand_degree = 0;

    // Переменная отвечает за глубину десятичной части числа (по ней прибавляется к целой)
    int summand_decimal = 0;

    // Переменная принимает степень числа, если это a-z
    char summand_degree_err = ' ';

    // Переменная отвечает за код ошибки после чтения
    int summand_error = 0;
    
    // Переменная - коэффициент перевода символа цифры в int цифру
    const int char_to_digit_ratio = 48;

    // Начало парсинга. Пытаемся прочиать знак +/-.
    if (summand[buff_index] == '+' || summand[buff_index] == '-') {
        if (summand[buff_index] == '-') summand_sign = '-';
        buff_index++;
    }
    // Пытаемся прочитать число.
    // Если идет сразу переменная, то число 1 или -1 (buff_index не увеличиваем, чтение переменной будет произведено после числа).
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
    // Если наткнулись на точку, значит число десятичное. Начинаем читать десятичную часть
    if (summand[buff_index] == '.') {
        buff_index++;
        summand_decimal++;
        while ('0' <= summand[buff_index] && summand[buff_index] <= '9') {
            summand_number += (double) ((int) summand[buff_index] - char_to_digit_ratio) / (10 * summand_decimal);
            buff_index++;
            summand_decimal++;
        }
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
        printf("NUMBER:    %lf \n", summand_number);
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