#pragma once

#include <assert.h>
#define NDEBUG

const size_t max_len_of_user_input = 100;
const int char_to_digit_ratio = 48;

// Перечисление кодов предупреждений и ошибок
enum warning_numbers {
    W_UNEXPECTED_SYMBOL = 1,            // Введен неразрешенный символ
    E_EMPTY_EQUATION = 2,               // Пустой ввод вместо уравнения
    W_IRRELEVANT_SUMMAND = 3,           // Слагаемое не соответствует критериям (после чтения остался 'хвост') 
    W_INCORRECT_DEGREE = 4,             // Неправильная степень
    W_DEGREE_NOT_FIT_EQUATION = 5,      // Степень не 0-2
    E_TWO_VARIABLES = 6,                // В уравнении два неизвестных
    E_ZERO_VARIABLES = 7                // В уравнении нет переменных
};

struct equation {
        char variable;
        double a;
        double b;
        double c;
        bool eq_error;
        };

struct summand {
        char variable;
        double number;
        int degree;
        int error;
};

struct roots {
        bool linear_equation;
        bool negative_discriminant;
        double discriminant;
        double root_1;
        double root_2;
};