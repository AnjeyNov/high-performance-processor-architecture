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


// ��������� ������ 
T**** allocation(int H, int W, int h, int w);

// ���������� �������
bool generateValues(T**** matrix, int H, int W, int h, int w);

// ������������ ���������� ������� � �������������� �������������
T** multiply(T** matrixA, T** matrixB, T** matrixC);

// ������������ ���������� ������� ��� �����������
T** multiplyNotVectorized(T** matrixA, T** matrixB, T** matrixC);

// ������� ������������
float** multiplySSE(float** matrixA, float** matrixB, float** matrixC);

// ������� ������������ 
double** multiplySSE(double** matrixA, double** matrixB, double** matrixC);

// �������� c �������������� �������������
T** addition(T** matrixA, T** matrixB);

// �������� ��� �������������� ������������
T** additionNotVectorized(T** matrixA, T** matrixB);

// ������� ��������
float** additionSSE(float** matrixA, float** matrixB);

// ������� ��������
double** additionSSE(double** matrixA, double** matrixB);

// ������ ������������
T**** fullMultiply(T**** matrixA, T**** matrixB, T**** matrixC , T** (*mul)(T**, T**, T**), T** (*add)(T**, T**));

// ���������
bool equals(T** matrixA, T** matrixB);

// ���������
bool equals(T**** matrixA, T**** matrixB);

// ������������ ������
bool destroy(T**** matrix, int H, int W, int h, int w);