#pragma once

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