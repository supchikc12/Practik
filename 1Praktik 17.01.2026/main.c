#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	double a, b, c, D, x1, x2;
	printf("Enter the three coefficients of the quadratic equation \n"); //сообщение о вводе 3 коффициентов
	scanf("%lf %lf %lf", &a, &b, &c);
	
	if (a==0)
	{
		printf("The coefficient 'a' cannot be equal to 0 \n"); //"Коэффициент 'a' не может быть равен 0"	
	}
	else
	{		
		D = pow(b,2) - 4 * a *c;
		printf("D = %lf\n", D);
		if (D>0)
		{
			x1 = (-b - sqrt(D)) / (2 * a);
			x2 = (-b + sqrt(D)) / (2 * a);
			
			printf("The equation has 2 roots \n");
            printf("x1 = %lf\n", x1);
            printf("x2 = %lf\n", x2);
		}
		else if (D==0)
		{
			x1 = -b / (2 * a);
			printf("The equation has 1 root \n");
            printf("x = %lf\n", x1);
		}
		else if (D < 0)
		{
			printf("there are no roots \n");
		}
	}
	return 0;
}