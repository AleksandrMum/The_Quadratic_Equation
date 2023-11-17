#pragma once

#include <stdio.h>
#include <string.h>

// Принимает уравнение, возвращает структуру, содержащую его значения a, b, c, имя переменной
struct equation get_equation_values(char*);

// Парсирует слагаемое и возвращает структуру, содержащую переменную, число, степень переменной и ошибку (если такова есть)
struct summand parsing_summand(char*); 