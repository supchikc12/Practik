#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

// Функция сложения двух матриц
// Возвращает новую матрицу - результат сложения
double** addMatrices(double** matrix1, double** matrix2, int n);

// Функция вычитания двух матриц
// Возвращает новую матрицу - результат вычитания (matrix1 - matrix2)
double** subtractMatrices(double** matrix1, double** matrix2, int n);

// Функция умножения двух матриц
// Возвращает новую матрицу - результат умножения
double** multiplyMatrices(double** matrix1, double** matrix2, int n);

/*
// Функция создания нулевой матрицы (все элементы = 0)
double** createZeroMatrix(int n);
*/
// Функция копирования матрицы
double** copyMatrix(double** source, int n);

#endif