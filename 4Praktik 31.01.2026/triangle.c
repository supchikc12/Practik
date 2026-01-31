#include <math.h>
#include "triangle.h"

bool is_triangle_valid(double a, double b, double c) {
    return (a > 0 && b > 0 && c > 0 &&
            a + b > c &&
            a + c > b &&
            b + c > a);
}

void calculate_triangle(double a, double b, double c, double result[2]) {
    result[0] = a + b + c;
    double p = result[0] / 2.0;
    result[1] = sqrt(p * (p - a) * (p - b) * (p - c));
}