#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>

// #define NDEBUG

const size_t max_len_of_user_input = 100;
const int char_to_digit_ratio = 48;

// Перечисление кодов предупреждений и ошибок
enum warning_numbers {
    W_UNEXPECTED_SYMBOL = 1,      // Введен неразрешенный символ
    E_EMPTY_EQUATION = 2,         // Пустой ввод вместо уравнения
    W_INCORRECT_DEGREE = 3,       // Неправильная степень
};

struct equation {
        char variable = NAN;
        double a = NAN;
        double b = NAN;
        double c = NAN;
        // bool critical_error;
        };

struct summand {
        char variable = NAN;
        double number = NAN;
        int degree = NAN;
        int error = NAN;
};

struct answer {
        double discriminant = NAN;
        double root_1 = NAN;
        double root_2 = NAN;
};