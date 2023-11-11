#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

struct equation {
        char variable;
        int a;
        int b;
        int c;
        int error;
        };

// Ошибка 1 - одна из переменных неполная или отсутствует, хотя подразумевалась при вводе.
// Ошибка 2 - введено уравнение с двумя неизвестными
// Ошибка 3 - введено уравнение с некорректной степенью (не 0-2)

struct equation get_values_of_equation();
void parsing(char*, char);
void clean_array(char*);