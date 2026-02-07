#include <stdio.h>
#include <stdlib.h>
#include "matrixOperations.h"



// Создание нулевой матрицы
double** createZeroMatrix(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    if (matrix == NULL) return NULL;
    
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
		malloc(n * sizeof(double));
        if (matrix[i] == NULL) {
            // Освобождаем ранее выделенную память
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
        
        // Инициализируем нулями
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0.0;
        }
    }
    
    return matrix;
}

// Копирование матрицы
double** copyMatrix(double** source, int n) {
    double** copy = createZeroMatrix(n);
    if (copy == NULL) return NULL;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            copy[i][j] = source[i][j];
        }
    }
    
    return copy;
}

// Сложение матриц
double** addMatrices(double** matrix1, double** matrix2, int n) {
	
    double** result = createZeroMatrix(n);
    if (result == NULL) return NULL;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

// Вычитание матриц (matrix1 - matrix2)
double** subtractMatrices(double** matrix1, double** matrix2, int n) {
    double** result = createZeroMatrix(n);
    if (result == NULL) return NULL;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    
    return result;
}

// Умножение матриц
double** multiplyMatrices(double** matrix1, double** matrix2, int n) {
    double** result = createZeroMatrix(n);
    if (result == NULL) return NULL;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    
    return result;
}