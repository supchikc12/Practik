#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>  // Для функции tolower
#include "matrixOperations.h"  // Подключаем модуль

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
// Функция для создания и заполнения матрицы
double** createAndFillMatrix(int n) {
    // Выделяем память под указатели на строки
    double** matrix = (double**)malloc(n * sizeof(double*));
    if (matrix == NULL) 
	{
        printf(" Memory allocation error \n"); // Ошибка выделения памяти
        return NULL;
    }
    
    // Выделяем память под каждую строку
    for (int i = 0; i < n; i++) 
	{
        matrix[i] = (double*)malloc(n * sizeof(double));
        if (matrix[i] == NULL) 
		{
            printf("Memory allocation error for line %d \n", i);//Ошибка выделения памяти для строки %d
            // Освобождаем ранее выделенную память
            for (int j = 0; j < i; j++) 
			{
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    
    // Заполняем матрицу значениями с клавиатуры
    printf("Enter the elements of the matrix %d *%d: \n", n, n); //Введите элементы матрицы %d * %d:
    for (int i = 0; i < n; i++) 
	{
        for (int j = 0; j < n; j++) 
		{
            printf("\n Element [%d][%d]: ", i, j); //Элемент [%d][%d]: 
            scanf("%lf", &matrix[i][j]);
        }
    }
    
    return matrix;
}

// Функция для освобождения памяти
void freeMatrix(double** matrix, int n) {
    if (matrix != NULL) 
	{
        for (int i = 0; i < n; i++) 
		{
            free(matrix[i]);
        }
        free(matrix);
    }
}

// Функция для вывода матрицы
void printMatrix(double** matrix, int n, const char* name) {
    printf("Matrix %s (%d * %d):\n", name, n, n);
    for (int i = 0; i < n; i++) 
	{
        for (int j = 0; j < n; j++) 
		{
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "C");

	
	int n;
	char operation;
	
	printf("Enter the dimension of the matrix n*n \n"); //Введите размерность матрицы n*n
	scanf("%d",&n);
	printf("\n");
	
	if (n <= 0) 
	{
    	printf("The size must be a positive number \n"); //Размер должен быть положительным числом
       	return 1;
    }
	
	// Создание и заполнение первой матрицы
    printf("\n=== The first matrix ===\n"); //Первая матрица
    double** matrix1 = createAndFillMatrix(n);
    if (matrix1 == NULL) 
	{
        return 1;
    }
    
	// Создание и заполнение второй матрицы
    printf("\n=== The second matrix ===\n"); //Вторая матрица
    double** matrix2 = createAndFillMatrix(n);
    if (matrix2 == NULL) 
	{
        return 1;
    }
    
    // Вывод двух матриц
    printf("\n=== Created matrices ===\n"); //Created matrices Созданные матрицы
    printMatrix(matrix1, n, "A");
    printf("\n");
    printMatrix(matrix2, n, "B");
    
    // Ввод символа для определения операции
    printf("Enter the operation execution symbol +, -, * \n");
    
    while(getchar() != '\n');
	operation = getchar();
	//scanf("%с \n", &operation);
	//printf("%с \n", &operation);
	if (operation != '+' && operation != '-' && operation != '*') 
    {
        printf("Error: incorrect operation Acceptable operations: +, -, *\n"); //Ошибка: некорректная операция Допустимые операции: +, -, *
        freeMatrix(matrix1, n);
        freeMatrix(matrix2, n);
        return 1;
    }
    
    printf("\nOperation selected: %c\n", operation); //Выбранная операция операцию:
    printf("%d \n", n);
	// Выполнение выбранной операции
    double** result = NULL;
    
    
    switch (operation) 
	{
        case '+':
            result = addMatrices(matrix1, matrix2, n); 
            printf("\n The result of the addition of matrices A + B: \n"); //Результат сложения матриц A + B:
            break;
            
        case '-':
            result = subtractMatrices(matrix1, matrix2, n);
            printf("\n The result of matrix A - B subtraction: \n"); //Результат вычитания матриц A - B:
            break;
            
        case '*':
            result = multiplyMatrices(matrix1, matrix2, n);
            printf("\n The result of matrix multiplication A * B: \n"); //Результат умножения матриц A * B:
            break;
    }
    
    // Проверяем успешность выполнения операции
    if (result == NULL) {
        printf("Error when performing the operation \n"); //Ошибка при выполнении операции!
    } else {
        // Выводим результат
        printMatrix(result, n, "Result");
        
        // Освобождаем память результата
        freeMatrix(result, n);
    }
    
    // Освобождаем память исходных матриц
    freeMatrix(matrix1, n);
    freeMatrix(matrix2, n);
    
	return 0;
}