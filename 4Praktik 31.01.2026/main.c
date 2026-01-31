#include <stdio.h>
#include "triangle.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {

    double a, b, c, results[2];
    
    printf("Vvedite dliny trekh storon treugolnika: \n");
    printf("Storona a: ");
    scanf("%lf", &a);
    printf("Storona b: ");
    scanf("%lf", &b);
    printf("Storona c: ");
    scanf("%lf", &c);
    
    if (!is_triangle_valid(a, b, c)) {
        printf("Oshibka: takie storony ne obrazuyut treugolnik \n");
        return 1;
    }
    
    calculate_triangle(a, b, c, results);
    
    printf("Rezultaty:\n");
    printf("Perimetr treugolnika: %if\n", results[0]);
    printf("Ploshchad' treugolnika: %if\n", results[1]);

	return 0;
}