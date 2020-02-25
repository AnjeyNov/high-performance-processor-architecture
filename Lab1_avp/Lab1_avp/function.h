#pragma once
#include <stdlib.h>
#include <time.h>
#include <emmintrin.h>
#include <Windows.h>
#include <iostream>

#define L 20
#define M 20
#define N 20

#define l 64
#define m 64
#define n 64

typedef float T;


// веделение памяти
T**** allocation(int H, int W, int h, int w);

// заполнение матрицы
bool generateValues(T**** matrix, int H, int W, int h, int w);

// перемножение внутренней матрицы с автоматической векторизацией
T** multiply(T** matrixA, T** matrixB);

// перемножение внутренней матрицы без веторизации
T** multiplyNotVectorized(T** matrixA, T** matrixB);

// хардкор перемножение
T** multiplySSE(T** matrixA, T** matrixB);

// сложение c автоматической векторизацией
T** addition(T** matrixA, T** matrixB);

// сложение без автоматической векторизации
T** additionNotVectorized(T** matrixA, T** matrixB);

// хардкор сложение
T** additionSSE(T** matrixA, T** matrixB);

// полное перемножение
T**** fullMultiply(T**** matrixA, T**** matrixB, T** (*mul)(T**, T**), T** (*add)(T**, T**));

// сравнение
bool equals(T** matrixA, T** matrixB);

// сравнение
bool equals(T**** matrixA, T**** matrixB);

// освобождение памяти
bool destroy(T**** matrix, int H, int W, int h, int w);