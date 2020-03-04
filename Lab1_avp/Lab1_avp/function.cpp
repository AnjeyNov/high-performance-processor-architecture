#include "function.h"

// ��������� ������
T**** allocation(int H, int W, int h, int w) {
	T**** matrix = nullptr;

	matrix = new T * **[H];

	for (int i = 0; i < H; i++) {
		matrix[i] = new T * *[W];

		for (int j = 0; j < W; j++) {
			matrix[i][j] = new T * [h];

			for (int k = 0; k < h; k++) {
				matrix[i][j][k] = new T[w];

				for (int x = 0; x < w; x++) {
					matrix[i][j][k][x] = 0;
				}
			}
		}
	}

	return matrix;
}

// ���������� �������
bool generateValues(T**** matrix, int H, int W, int h, int w) {
	srand((unsigned)time(NULL));

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			for (int k = 0; k < h; k++) {
				for (int x = 0; x < w; x++) {
					matrix[i][j][k][x] = (T)(rand() % 100);
				}
			}
		}
	}

	return true;
}

// ������������ ���������� ������� � �������������� �������������
T** multiply(T** matrixA, T** matrixB, T** matrixC) {
	T* __restrict temp� = nullptr;
	T* __restrict tempB = nullptr;


	// ��������������� ������������ 
	for (int i = 0; i < l; i++) {
		temp� = matrixC[i];

		for (int j = 0; j < m; j++) {
			tempB = matrixB[j];
			
			//#pragma(hint_parallel(n))
			#pragma loop(ivdep)
			for (int k = 0; k < n; k++) {
				temp�[k] += matrixA[i][j] * tempB[k];
			}

		}
	}
	return matrixC;
}

// ������������ ���������� ������� ��� �����������
T** multiplyNotVectorized(T** matrixA, T** matrixB, T** matrixC) {
	T* __restrict temp� = nullptr;
	T* __restrict tempB = nullptr;


	for (int i = 0; i < l; i++) {
		temp� = matrixC[i];

		for (int j = 0; j < m; j++) {
			tempB = matrixB[j];
			#pragma loop(no_vector)
			for (int k = 0; k < n; k++) {
				temp�[k] += matrixA[i][j] * tempB[k];
			}

		}
	}

	return matrixC;
}

// ������� ������������
float** multiplySSE(float** matrixA, float** matrixB, float** matrixC){
	float tempA = 0;
	float* tempB = nullptr;
	float* tempC = nullptr;

	__m256 reg0;
	__m256 reg1;
	__m256 reg2;


	for (int i = 0; i < l; i++)
	{
		tempC = matrixC[i];

		for (int j = 0; j < m; j++)
		{
			tempA = matrixA[i][j];
			tempB = matrixB[j];
			reg1 = _mm256_set1_ps(tempA);

			for (int offset = 0; offset < n; offset += 8) {
				reg0 = _mm256_load_ps(tempC+offset);
				reg2 = _mm256_load_ps(tempB+offset);
				reg0 = _mm256_add_ps(reg0, _mm256_mul_ps(reg1, reg2));
				_mm256_store_ps(tempC+offset, reg0);
			}
		}
	}
	return matrixC;
}

double** multiplySSE(double** matrixA, double** matrixB, double** matrixC) {
	double tempA = 0;
	double* tempB = nullptr;
	double* tempC = nullptr;

	__m256d reg0;
	__m256d reg1;
	__m256d reg2;


	for (int i = 0; i < l; i++)
	{
		tempC = matrixC[i];

		for (int j = 0; j < m; j++)
		{
			tempA = matrixA[i][j];
			tempB = matrixB[j];
			reg1 = _mm256_set1_pd(tempA);

			for (int k = 0; k < n; k += 4) {
				reg0 = _mm256_load_pd(tempC + k);
				reg2 = _mm256_load_pd(tempB + k);
				reg0 = _mm256_add_pd(reg0, _mm256_mul_pd(reg1, reg2));
				_mm256_store_pd(tempC + k, reg0);
			}
		}
	}
	return matrixC;
}

// ������� ��������
float** additionSSE(float** matrixA, float** matrixB) {
	
	float* tempA = nullptr;
	float* tempB = nullptr;

	__m256 reg0;
	__m256 reg1;


	for (int i = 0; i < l; i++)
	{
		tempA = matrixA[i];
		tempB = matrixB[i];
		for (int j = 0; j < n; j+=8)
		{
			reg0 = _mm256_load_ps(tempA+j);
			reg1 = _mm256_load_ps(tempB+j);
			reg0 = _mm256_add_ps(reg0, reg1);
			_mm256_store_ps(tempA + j, reg0);
		}
	}
	return matrixA;
}

// ������� ��������
double** additionSSE(double** matrixA, double** matrixB) {

	double* tempA = nullptr;
	double* tempB = nullptr;

	__m256d reg0;
	__m256d reg1;


	for (int i = 0; i < l; i++)
	{
		tempA = matrixA[i];
		tempB = matrixB[i];
		for (int j = 0; j < n; j += 4)
		{
			reg0 = _mm256_load_pd(tempA + j);
			reg1 = _mm256_load_pd(tempB + j);
			reg0 = _mm256_add_pd(reg0, reg1);
			_mm256_store_pd(tempA + j, reg0);
		}
	}
	return matrixA;
}

// �������� � �������������� �������������
T** addition(T** matrixA, T** matrixB) {
	for (int i = 0; i < l; i++) {

		//#pragma(hint_parallel(n))
		#pragma loop(ivdep)
		for (int j = 0; j < n; j++) {
			matrixA[i][j] += matrixB[i][j];
		}
	}

	return matrixA;
}

// �������� ��� �������������� �����������
T** additionNotVectorized(T** matrixA, T** matrixB)
{
	for (int i = 0; i < l; i++) {

		#pragma loop(no_vector)
		for (int j = 0; j < n; j++) {
			matrixA[i][j] += matrixB[i][j];
		}
	}

	return matrixA;
}

// ������ ������������
T**** fullMultiply(T**** matrixA, T**** matrixB, T****matrixC, T** (*mul)(T**, T**, T**), T** (*add)(T**, T**))
{
	T*** __restrict temp� = nullptr;
	T*** __restrict tempB = nullptr;


	for (int i = 0; i < L; i++) {
		temp� = matrixC[i];
		for (int j = 0; j < M; j++)
		{
			tempB = matrixB[j];
			for (int k = 0; k < N; k++) {
				add(temp�[k], mul(matrixA[i][j], tempB[k], matrixC[i][j]));
			}
		}

	}

	return matrixC;
}

// ���������
bool equals(T** matrixA, T** matrixB)
{
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrixA[i][j] != matrixB[i][j])
				return false;
		}
	}

	return true;
}

// ���������
bool equals(T**** matrixA, T**** matrixB)
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < N; j++) {
			if (!equals(matrixA[i][j], matrixB[i][j]))
				return false;
		}
	}
	return true;
}

// ������������ ������
bool destroy(T**** matrix, int H, int W, int h, int w) {
	for (int i = 0; i < H; i++) {

		for (int j = 0; j < W; j++) {

			for (int k = 0; k < h; k++) {
				delete[] matrix[i][j][k];
			}
			delete[] matrix[i][j];
		}
		delete[] matrix[i];
	}


	delete[] matrix;

	return true;
}
