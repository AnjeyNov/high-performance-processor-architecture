#pragma once
#include <stdlib.h>
#include <time.h>
#include <emmintrin.h>
#include <Windows.h>
#include <iostream>

#define L 500
#define M 500
#define N 500

#define l 4
#define m 4
#define n 4

typedef float T;


// веделение памяти
T**** allocation(int H, int W, int h, int w);

// заполнение матрицы
bool generateValues(T**** matrix, int H, int W, int h, int w);

// перемножение внутренней матрицы с автоматической векторизацией
T** multiply(T** matrixA, T** matrixB, T** matrixC);

// перемножение внутренней матрицы без веторизации
T** multiplyNotVectorized(T** matrixA, T** matrixB, T** matrixC);

// хардкор перемножение
T** multiplySSE(T** matrixA, T** matrixB, T** matrixC);

// сложение c автоматической векторизацией
T** addition(T** matrixA, T** matrixB);

// сложение без автоматической векторизации
T** additionNotVectorized(T** matrixA, T** matrixB);

// хардкор сложение
T** additionSSE(T** matrixA, T** matrixB);

// полное перемножение
T**** fullMultiply(T**** matrixA, T**** matrixB, T**** matrixC , T** (*mul)(T**, T**, T**), T** (*add)(T**, T**));

// сравнение
bool equals(T** matrixA, T** matrixB);

// сравнение
bool equals(T**** matrixA, T**** matrixB);

// освобождение памяти
bool destroy(T**** matrix, int H, int W, int h, int w);