#include "functions.h"

// Главная функкия, в нее приходят значения уравнения и ее решение
void solution_of_equation() {
    // Получаем ввод уравнения, принимаем из него значения a, b, c
    struct equation curr_equation = get_values_of_equation();
    // Если по итогу ввода решить уравнение невозможно, уведомляем
    if (curr_equation.critical_error) {
        printf("SOLUTION ERROR \n");
    }
    // Иначе решаем
    else {
        printf("Variable: %c \n", curr_equation.variable);
        printf("A: %lf \n", curr_equation.a);
        printf("B: %lf \n", curr_equation.b);
        printf("C: %lf \n", curr_equation.c);
        printf("---------\n");

        // Из значений a, b, c получаем решение(я) уравнения
        struct answer curr_answer = calculation(curr_equation);
        printf("ANSWER: \n");
        // Если дискриминант положительный, пишем его и оба корня
        if (curr_answer.discriminant > 0) {
            printf("Discriminant: %lf \n", curr_answer.discriminant);
            printf("Root 1: %lf \n", curr_answer.root_1);
            printf("Root 2: %lf \n", curr_answer.root_2);
        }
        // Если дискриминант нулевой или это линейное уравнение, пишем один корень
        else if (is_double_zero(curr_answer.discriminant) || is_double_zero(curr_equation.a)) {
            printf("Root: %lf \n", curr_answer.root_1);
        }
        // Если дискриминант отрицательный, пишем его и говорим, что корней нет
        else if (curr_answer.discriminant < 0) {
            printf("Discriminant: %lf \n", curr_answer.discriminant);
            printf("The equation has no roots \n");
        }
        // Если было введено не уравнение, пишем что корней быть не может
        else if (is_double_zero(curr_equation.a) && is_double_zero(curr_equation.b)) {
            printf("This input can't have roots \n");
        }
        printf("---------\n");
    }
}

struct answer calculation(struct equation curr_equation) {
    double discriminant = 0;
    double root_1 = 0;
    double root_2 = 0;

    double curr_a = curr_equation.a;
    double curr_b = curr_equation.b;
    double curr_c = curr_equation.c;


    // Если уравнение не квадратное и не линейное, корни остаются по нулям
    if (is_double_zero(curr_a) && is_double_zero(curr_b)) {
        // Ничего не делаем
    }
    // Если уравнение линейное
    else if (is_double_zero(curr_a)) {
        root_1 = root_2 = (- curr_c) / (curr_b);
    }
    // Если уравнение квадратное
    else {
        // Считаем дискриминант
        discriminant = pow(curr_b, 2) - 4 * curr_a * curr_c;
        // Если он отрицательный, корней нет
        if (discriminant < 0) {
            // Ничего не делаем
        }
        // Если он нулевой, то корни одинаковы и равно -b * (+/- D=0) /2a
        else if (is_double_zero(discriminant)) {
            root_1 = root_2 = (- curr_b) / (2 * curr_a); 
        }
        // Если он положительный, считаем корни
        else {
            root_1 = (- curr_b + sqrt(discriminant)) / (2 * curr_a);
            root_2 = (- curr_b - sqrt(discriminant)) / (2 * curr_a);
        }
    }
    // Возвращаем полученные результаты
    struct answer curr_answer = {discriminant, root_1, root_2};
    return curr_answer;
}

bool is_double_zero(double number) {
    if (-0.00001 < number && number < 0.0001) return true;
    else return false;
}