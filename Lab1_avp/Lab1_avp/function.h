#pragma once
#include <stdlib.h>
#include <time.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <Windows.h>
#include <iostream>

#define L 200
#define M 200
#define N 200

#define l 16
#define m 16
#define n 16

typedef float T;


// выделение памяти 
T**** allocation(int H, int W, int h, int w);

// заполнение матрицы
bool generateValues(T**** matrix, int H, int W, int h, int w);

// перемножение внутренней матрицы с автоматической векторизацией
T** multiply(T** matrixA, T** matrixB, T** matrixC);

// перемножение внутренней матрицы без веторизации
T** multiplyNotVectorized(T** matrixA, T** matrixB, T** matrixC);

// хардкор перемножение
float** multiplySSE(float** matrixA, float** matrixB, float** matrixC);

// хардкор перемножение 
double** multiplySSE(double** matrixA, double** matrixB, double** matrixC);

// сложение c автоматической векторизацией
T** addition(T** matrixA, T** matrixB);

// сложение без автоматической векторизации
T** additionNotVectorized(T** matrixA, T** matrixB);

// хардкор сложение
float** additionSSE(float** matrixA, float** matrixB);

// хардкор сложение
double** additionSSE(double** matrixA, double** matrixB);

// полное перемножение
T**** fullMultiply(T**** matrixA, T**** matrixB, T**** matrixC , T** (*mul)(T**, T**, T**), T** (*add)(T**, T**));

// сравнение
bool equals(T** matrixA, T** matrixB);

// сравнение
bool equals(T**** matrixA, T**** matrixB);

// освобождение памяти
bool destroy(T**** matrix, int H, int W, int h, int w);