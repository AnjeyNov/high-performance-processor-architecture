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


// ��������� ������
T**** allocation(int H, int W, int h, int w);

// ���������� �������
bool generateValues(T**** matrix, int H, int W, int h, int w);

// ������������ ���������� ������� � �������������� �������������
T** multiply(T** matrixA, T** matrixB, T** matrixC);

// ������������ ���������� ������� ��� �����������
T** multiplyNotVectorized(T** matrixA, T** matrixB, T** matrixC);

// ������� ������������
T** multiplySSE(T** matrixA, T** matrixB, T** matrixC);

// �������� c �������������� �������������
T** addition(T** matrixA, T** matrixB);

// �������� ��� �������������� ������������
T** additionNotVectorized(T** matrixA, T** matrixB);

// ������� ��������
T** additionSSE(T** matrixA, T** matrixB);

// ������ ������������
T**** fullMultiply(T**** matrixA, T**** matrixB, T**** matrixC , T** (*mul)(T**, T**, T**), T** (*add)(T**, T**));

// ���������
bool equals(T** matrixA, T** matrixB);

// ���������
bool equals(T**** matrixA, T**** matrixB);

// ������������ ������
bool destroy(T**** matrix, int H, int W, int h, int w);