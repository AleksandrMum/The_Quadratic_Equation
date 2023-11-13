#include "functions.h"

struct answer calculation(struct equation curr_equation) {
    double discriminant = 0;
    double root_1 = 0;
    double root_2 = 0;

    int curr_a = curr_equation.a;
    int curr_b = curr_equation.b;
    int curr_c = curr_equation.c;


    if (curr_a != 0) {
        // Если уравнение квадратное, считаем дискриминант
        discriminant = pow(curr_b, 2) - 4 * curr_a * curr_c;

        // Если дискриминант отрицательный, корней нет
        if (discriminant < 0) {
            printf("The equation has no roots \n");
            struct answer curr_answer = {discriminant, 0, 0};
            return curr_answer;
        }
        // Если дискриминант нулевой, корни одинаковы
        else if ((int) discriminant == 0) {
            root_1 = root_2 = (- curr_b) / (2 * curr_a);
            
        }
        // Если дискриминант больше 0, считаем корни
        else {
            root_1 = (- curr_b + sqrt(discriminant)) / (2 * curr_a);
            root_2 = (- curr_b - sqrt(discriminant)) / (2 * curr_a);
        }
        // Возвращаем ответ, если он был получен
        struct answer curr_answer = {discriminant, root_1, root_2};
        return curr_answer;
    }

    // Если уравнение линейное
    else if (curr_b != 0) {
        root_1 = root_2 = (- curr_c) / (curr_b);
        struct answer curr_answer = {0, root_1, root_2};
        return curr_answer;
    }
    else printf("\n --- \n UNEXPECTED BEHAVIOR \n --- \n");
}