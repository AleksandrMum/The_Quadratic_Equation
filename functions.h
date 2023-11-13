#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <windows.h>

#define MAX_LEN_OF_USER_INPUT 100
#define DEBUG_FUNC false

struct equation {
        char variable;
        double a;
        double b;
        double c;
        bool critical_error;
        };

struct summand {
        char variable;
        double number;
        int degree;
        int error;
};

struct answer {
        double discriminant;
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
// Ошибка 7 (критичная)         - введено не уравнение (отсутствуют переменные)


// equation.cpp
void solution_of_equation();
struct answer calculation(struct equation);
bool is_double_zero(double);

// input_and_parsing.cpp
struct equation get_values_of_equation();
void clean_array(char*);
void print_warning_error(int);
struct summand parsing(char*, char);