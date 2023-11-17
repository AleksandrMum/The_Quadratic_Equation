#include "common.h"
#include "utilites.h"
#include "solve_equation.h"

struct roots get_equation_roots(struct equation* curr_equation) {
    bool linear_equation = false;
    bool negative_discriminant = false;
    double discriminant = 0;
    double root_1 = 0;
    double root_2 = 0;

    double curr_a = curr_equation->a;
    double curr_b = curr_equation->b;
    double curr_c = curr_equation->c;

    if (is_double_zero(curr_a)) {
        root_1 = root_2 = (- curr_c) / (curr_b);
        linear_equation = true;
    }
    else {
        discriminant = (curr_b * curr_b) - 4 * curr_a * curr_c;
        if (discriminant < 0) {
            negative_discriminant = true;
        }
        else if (is_double_zero(discriminant)) {
            root_1 = root_2 =  (- curr_b) / (2 * curr_a);
        }
        else {
            root_1 = (- curr_b + sqrt(discriminant)) / (2 * curr_a);
            root_2 = (- curr_b - sqrt(discriminant)) / (2 * curr_a);
        }
    }
    return {
        linear_equation,
        negative_discriminant,
        discriminant,
        root_1,
        root_2
    };
}