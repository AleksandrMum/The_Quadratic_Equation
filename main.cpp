#include <stdio.h>
#include "func.h"

int main() {
    printf("Input equation like ax^2 + bx + c = d: \n");
    struct equation introdused_equation = scan_string_with_equation();
    // printf("%i - %i - %i - %i\n", introdused_equation.a, introdused_equation.b, introdused_equation.c, introdused_equation.error);
}
