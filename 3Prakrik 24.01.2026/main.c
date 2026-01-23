#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a,b, **matrix;
	char *str =  malloc(80);
	bool magicSquare = true;
	
	printf("Enter up to 80 characters \n");
	for (int i=0; i<80;i++)
	{
		str[i] = getchar();
		if (str[i] == '\n') break;
	}
	
	
	printf("Your line: ");
	
	for (int i=0; i < 80; i++)
	{
		putchar(str[i]);
	}
	
	for (int i=0; i < 80; i++)
	{
		if (str[i] == 'a' || str[i] == 'b')
		{
			if (str[i] == 'a') str[i] = 'A';
			if (str[i] == 'b') str[i] = 'B';
		}
	}
	printf("\n");
	printf("Your new line: ");
	
	for (int i=0; i < 80; i++)
	{
		putchar(str[i]);
	}
	
	printf("\n");

	printf("Enter the size of the matrix \n");
	scanf("%d %d", &a, &b);
	
	matrix = (int **)malloc(a*sizeof(int*));
	for (int i = 0; i < a; i++) matrix[i] = (int**)malloc(b*sizeof(int*));
	
	printf("Enter the elements of the matrix \n");
	
	for(int i = 0; i < a; i++)
	{
		for(int j = 0; j < b; j++) 
		{
			printf("[%d] [%d]\n", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
	
	for(int i = 0; i < a; i++)
	{
		for(int j = 0; j < b; j++) 
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	
	int diag1 = 0, diag2 = 0;
	for(int i = 0; i < a; i++) diag1 += matrix[i][i];
	printf("The sum of the main diagonal of the matrix = %d \n", diag1);
	

	for(int i = 0; i < a; i++) diag2 += matrix[i][a - 1 - i];
	printf("The sum of the side diagonal of the matrix = %d \n", diag2);
	
	int targetSum = 0;
	if (diag1 == diag2)
	{
		for (int i = 0; i < a; i++) targetSum += matrix[0][i];
		
		
		for (int i = 0; i < a; i++)
		{	
			int sumRow = 0, sumCol = 0;				
			for (int j = 0; j < b; j++) 
			{
				sumRow += matrix[i][j];
				sumCol += matrix[j][i];
			}
			
			if (sumRow != targetSum || sumCol != targetSum) 
			{
				magicSquare = false;
				break;
			}
		}	
	}
	else magicSquare = false;
	
	if (magicSquare) printf("The matrix is a magic square \n");
	else printf("The matrix is not a magic square \n");
	
	//Освобождение памяти
	for(i=0;i<m;i++)
	{
		free(matrix[i]);
	}
	free(matrix);
	return 0;
	
}