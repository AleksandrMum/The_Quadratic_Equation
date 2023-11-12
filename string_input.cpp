#include "functions.h"

struct equation get_values_of_equation() {
    // Объявляю значения уравнения, которые буду потом возвращать
    char equation_variable = ' ';
    int equation_a = 0;
    int equation_b = 0;
    int equation_c = 0;
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
        if (char_input == '\n') {
            string_input[string_input_len] = '\0';
            break;
        }
        else if (char_input == ' ') continue;
        else if (char_input == '+' || char_input == '-') {
            if (string_input[string_input_len - 1] != ' ') {
                string_input[string_input_len] = ' ';
                string_input_len++;
            }
            string_input[string_input_len] = char_input;
        }
        else if (char_input == '=') {
            string_input[string_input_len] = ' ';
            string_input_len++;
            string_input[string_input_len] = char_input;
            string_input_len++;
            string_input[string_input_len] = ' ';
        }
        else string_input[string_input_len] = char_input;
        string_input_len++;
        is_summand_in_equation = true;
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
            if (temp_summand.error == 3) {
                equation_variable = ' ';
                equation_a = 0;
                equation_b = 0;
                equation_c = 0;
                critical_error = true;
                print_warning_error(temp_summand.error);
                break;
            } 
            else if (temp_summand.error != 0) {
                print_warning_error(temp_summand.error);
                continue;
            }
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

    // Если введено не квадратное уравнение (a == 0 -> kx + b) то ошибка №7
    if (equation_a == 0) {
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

void clean_array(char* array) {
    size_t index = 0;
    while (array[index] != '\0') {
        array[index] = '\0';
        index++;
    }
}

void print_warning_error(int error) {
    if (error == 0) printf("UNEXPECTED BEHAVIOR - Function is called without detecting an error \n");

    else if (error == 1) printf("WARNING - Inappropriate input of a summand \n");
    else if (error == 2) printf("WARNING - The summand was implied but not introduced \n");
    else if (error == 3) printf("ERROR - There are two variables in the equation \n");
    else if (error == 4) printf("WARNING - Uncorrect degree \n");
    else if (error == 5) printf("WARNING - The degree does not fit the quadratic equation \n");
    else if (error == 6) printf("ERROR - There are no summands in the equation \n");
    else if (error == 7) printf("WARNING - A linear equation is introduced (max degree is 1) \n");
    
    else printf("UNEXPECTED BEHAVIOR - An unknown error has occurred \n");
}