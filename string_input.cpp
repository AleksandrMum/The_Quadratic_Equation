#include "functions.h"
#define MAX_LEN_OF_USER_INPUT 100

struct equation get_values_of_equation() {
    int equation_a = 0;
    int equation_b = 0;
    int equation_c = 0;
    char equation_variable = ' ';
    int equation_error = 0;

    bool equation_reverse = false;

    printf("Enter an equation (up to 100 characters): \n");
    char string_input[MAX_LEN_OF_USER_INPUT] = {'\0'};
    size_t string_input_len = 0;

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
    }

    printf("%s \n", string_input);
    printf("---------\n");

    char buff_char = '0';
    char summand_buff[MAX_LEN_OF_USER_INPUT] = {'\0'};
    size_t summand_buff_len = 0;
    for (size_t index = 0; index <= string_input_len; index++) {
        buff_char = string_input[index];
        if (buff_char != '\0' && buff_char != ' ' && buff_char != '=') {
            summand_buff[summand_buff_len] = buff_char;
            summand_buff_len++;
        }
        else if (buff_char == ' ') {
            if (summand_buff_len == 0) continue;
            parsing(summand_buff, equation_variable);
            clean_array(summand_buff);
            summand_buff_len = 0;
        }
        else if (buff_char == '\0') {
            if (summand_buff_len == 0) break;
            parsing(summand_buff, equation_variable);
            clean_array(summand_buff);
            summand_buff_len = 0;
        }
        else if (buff_char == '=') equation_reverse = true;
        else printf("UNEXPECTED BEHAVIOR");
    }
    

    struct equation curr_eq = {
        equation_variable,
        equation_a,
        equation_b,
        equation_c,
        equation_error
        };
    return curr_eq;
}

void clean_array(char* array) {
    size_t index = 0;
    while (array[index] != '\0') {
        array[index] = '\0';
        index++;
    }
}