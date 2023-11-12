#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

#define MAX_LEN_OF_USER_INPUT 100
#define DEBUG_FUNC false

struct equation {
        char variable;
        int a; int b; int c;
        bool critical_error;
        };

struct summand {
        char variable;
        int number;
        int degree;
        int error;
};

struct answer {
        int discriminant;
        double root_1;
        double root_2;
};

// Ошибки при парсинге:
// Ошибка 1 (не критичная)      - слагаемое введено некорректно (чтение произведено не полностью)
// Ошибка 2 (не критичная)      - одна из переменных отсутствует, хотя подразумевалась
// Ошибка 3 (критичная)         - введено уравнение с двумя неизвестными
// Ошибка 4 (не критичная)      - у слагаемого некорректная степень (не число)
// Ошибка 5 (не критичная)      - введено уравнение с степенью, не соответствующей квадратному уравнению
// Ошибки при чтении уравнения
// Ошибка 6 (критичная)         - уравнение не было введено
// Ошибка 7 (не критичная)      - введено уравнение типа kx + b

// string_input.cpp
struct equation get_values_of_equation();
void clean_array(char*);
void print_warning_error(int);

// parsing.cpp
struct summand parsing(char*, char);

// calculation.cpp
struct answer calculation(struct equarton *curr_equation);