#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

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

struct equation scan_string_with_equation();

struct equation process_equation(char*, int);

void parsing(char*, char);