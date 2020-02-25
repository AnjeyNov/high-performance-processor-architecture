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


// ��������� ������
T**** allocation(int H, int W, int h, int w);

// ���������� �������
bool generateValues(T**** matrix, int H, int W, int h, int w);

// ������������ ���������� ������� � �������������� �������������
T** multiply(T** matrixA, T** matrixB);

// ������������ ���������� ������� ��� �����������
T** multiplyNotVectorized(T** matrixA, T** matrixB);

// ������� ������������
T** multiplySSE(T** matrixA, T** matrixB);

// �������� c �������������� �������������
T** addition(T** matrixA, T** matrixB);

// �������� ��� �������������� ������������
T** additionNotVectorized(T** matrixA, T** matrixB);

// ������� ��������
T** additionSSE(T** matrixA, T** matrixB);

// ������ ������������
T**** fullMultiply(T**** matrixA, T**** matrixB, T** (*mul)(T**, T**), T** (*add)(T**, T**));

// ���������
bool equals(T** matrixA, T** matrixB);

// ���������
bool equals(T**** matrixA, T**** matrixB);

// ������������ ������
bool destroy(T**** matrix, int H, int W, int h, int w);