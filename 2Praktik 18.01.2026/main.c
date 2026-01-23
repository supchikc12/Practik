#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int m, n, i,j,k, **sqare, **ipa;
	double a,**pa, sum = 0;

	printf("Enter the size of the double type matrix \n"); //Введите размер матрицы типа double
	scanf("%d %d", &m, &n);
	
	//Выделение памяти под матрицу
	pa = (int**)malloc(m*sizeof(int*));
	for (i=0;i<m;i++)
	{
		pa[i] = (int**)malloc(n*sizeof(int*));
	}
	
	//Запись матрицы произвольного размера
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("[%d][%d]\n", i, j);
			scanf("%if", &pa[i][j]);
		}
	}
	
	//Вывод матрицы на консоль
	printf("\n");//Ваша матрица
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%if ", pa[i][j]);
		}
		printf("\n");
	}
	
	//Сумма элементов на главной диагонали матрицы
	for(i=0;i<m;i++)
	{
		sum += pa[i][i];
	}
	printf("The sum of the elements on the main diagonal of a square matrix\n");//Сумма элементов на главной диагонали квадратной матрицы
	printf("%if \n", sum);
		
	sum=0;
		
	//Сумма элементов на побочной диагонали матрицы
	for(i=0;i<m;i++)
	{
		sum += pa[i][m - 1 - i];
	}
		
	printf("The sum of the elements on the side diagonal of a square matrix\n");//Сумма элементов на побочной диагонали квадратной матрицы
	printf("%if \n", sum);	
	
	//Освобождение памяти
	for(i=0;i<m;i++)
	{
		free(pa[i]);
	}
	free(pa);
	
	printf("Enter the size of the int type matrix \n"); //Введите размер матрицы типа int
	scanf("%d %d", &m, &n);
	
	//Выделение памяти под исходной матрицы и матрицы результата
	ipa = (int**)malloc(m*sizeof(int*));
	sqare = (int**)malloc(m*sizeof(int*));
	for (i=0;i<m;i++)
	{
		ipa[i] = (int**)malloc(n*sizeof(int*));
		sqare[i] = (int**)malloc(n*sizeof(int*));
	}
	
	//Запись матрицы произвольного размера
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("[%d][%d]\n", i, j);
			scanf("%d", &ipa[i][j]);
		}
	}
	
	//Вывод матрицы на консоль
	printf("\n");//Ваша матрица
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ", ipa[i][j]);
		}
		printf("\n");
	}
	
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			sqare[i][j] = 0;
			for(k=0;k<n;k++)
			{
				sqare[i][j] += ipa[i][k] * ipa[k][j];				
			}		
		}
	}
	
	//Вывод матрицы на консоль
	printf("\n");//Ваша матрица
	for (i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ", sqare[i][j]);
		}
		printf("\n");
	}
	
	//Освобождение памяти 
	for(i=0;i<m;i++)
	{
		free(sqare[i]);
		free(ipa[i]);
	}
	free(sqare);
	free(ipa);
	
	return 0;
}