#pragma once

#include <stdio.h>

// Печатает инструкцию по вводу уравнения пользователем
void print_instruction();

// Печатает введенное уравнение
void print_equation(char*);

// Возвращает истинну, если пользователь ввел 'y' (хочет продолжить ввод уравнений)
bool is_there_new_equation();

// Возвращает истинну, если действительное число равно 0
bool is_double_zero(double);

// Принимает код предупреждения/ошибки и печатает соответственное сообщение
void print_warning(int);

// Чистит строку в массиве char и возвращает 0 - длину пустой строки
int clean_string(char*);

// Возвращает истину, если символ это цифра
bool is_char_number(char);

// Возвращает истину, если символ это буква
bool is_char_letter(char);

// Принимает символ цифры, возвращает число
int char_to_int(char);