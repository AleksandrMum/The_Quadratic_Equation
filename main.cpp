#include <stdio.h>
#include "func.h"

// #define NDEBUG

int main() {
    // printf("Input equation like ax^2 + bx + c = d: \n");
    // struct equation introdused_equation = scan_string_with_equation();
    // printf("%i - %i - %i - %i\n", introdused_equation.a, introdused_equation.b, introdused_equation.c, introdused_equation.error);

    printf("Test of parsing. Enter summand.\n");
    char summand[10] = {'\0'};
    while (true) {
        scanf("%s", &summand);
        parsing(summand, 'x');
    } 
    //TODO - Сделать ввод так, чтобы автоматически парсилась строка на слагаемые, а слагаемые отсылались parsing()
}
