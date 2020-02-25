#include "function.h"

// веделение памяти
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

// заполнение матрицы
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

// перемножение внутренней матрицы с автоматической векторизацией
T** multiply(T** matrixA, T** matrixB) {
	T** matrixC = nullptr;
	T* __restrict tempС = nullptr;
	T* __restrict tempB = nullptr;

	matrixC = new T * [l];
	for (int i = 0; i < l; i++) {
		matrixC[i] = new T[n];
		ZeroMemory(matrixC[i], sizeof(T) * n);
	}

	// непосредственно перемножение 
	for (int i = 0; i < l; i++) {
		tempС = matrixC[i];

		for (int j = 0; j < m; j++) {
			tempB = matrixB[j];
			
			//#pragma(hint_parallel(n))
			#pragma loop(ivdep)
			for (int k = 0; k < n; k++) {
				tempС[k] += matrixA[i][j] * tempB[k];
			}

		}
	}
	return matrixC;
}

// перемножение внутренней матрицы без веторизации
T** multiplyNotVectorized(T** matrixA, T** matrixB) {
	T** matrixC = nullptr;
	T* __restrict tempС = nullptr;
	T* __restrict tempB = nullptr;

	matrixC = new T * [l];
	for (int i = 0; i < l; i++) {
		matrixC[i] = new T[n];
		ZeroMemory(matrixC[i], sizeof(T) * n);
	}

	for (int i = 0; i < l; i++) {
		tempС = matrixC[i];

		for (int j = 0; j < m; j++) {
			tempB = matrixB[j];
			#pragma loop(no_vector)
			for (int k = 0; k < n; k++) {
				tempС[k] += matrixA[i][j] * tempB[k];
			}

		}
	}

	return matrixC;
}

// хардкор перемножение
T** multiplySSE(T** matrixA, T** matrixB){
	T** matrixC = nullptr;
	T tempA = 0;
	T* tempB = nullptr;
	T* tempC = nullptr;

	__m128 reg0;
	__m128 reg1;
	__m128 reg2;

	matrixC = new T * [l];
	for (int i = 0; i < l; i++) {
		matrixC[i] = new T[n];
		ZeroMemory(matrixC[i], sizeof(T) * n);
	}

	for (int i = 0; i < l; i++)
	{
		tempC = matrixC[i];

		for (int j = 0; j < m; j++)
		{
			tempA = matrixA[i][j];
			tempB = matrixB[j];
			reg1 = _mm_set1_ps(tempA);

			for (int k = 0; k < n; k += 4) {
				reg0 = _mm_load_ps(tempC+k);
				reg2 = _mm_load_ps(tempB+k);
				reg0 = _mm_add_ps(reg0, _mm_mul_ps(reg1, reg2));
				_mm_store_ps(tempC+k, reg0);
			}
		}
	}
	return matrixC;
}

// хардкор сложение
T** additionSSE(T** matrixA, T** matrixB) {
	
	T* tempA = nullptr;
	T* tempB = nullptr;

	__m128 reg0;
	__m128 reg1;


	for (int i = 0; i < l; i++)
	{
		tempA = matrixA[i];
		tempB = matrixB[i];
		for (int j = 0; j < n; j+=4)
		{
			reg0 = _mm_load_ps(tempA+j);
			reg1 = _mm_load_ps(tempB+j);
			reg0 = _mm_add_ps(reg0, reg1);
			_mm_store_ps(tempA + j, reg0);
		}
	}
	return matrixA;
}

// сложение с автоматической векторизацией
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

// сложение без автоматической веторизации
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

// полное перемножение
T**** fullMultiply(T**** matrixA, T**** matrixB, T** (*mul)(T**, T**), T** (*add)(T**, T**))
{
	T**** matrixC = nullptr;
	T*** __restrict tempС = nullptr;
	T*** __restrict tempB = nullptr;

	matrixC = new T*** [L];
	for (int i = 0; i < L; i++) {

		matrixC[i] = new T * *[N];
		for (int j = 0; j < N; j++) {

			matrixC[i][j] = new T * [l];
			for (int k = 0; k < l; k++) {

				matrixC[i][j][k] = new T[n];
				ZeroMemory(matrixC[i][j][k], sizeof(T) * n);
			}
		}
	}


	for (int i = 0; i < L; i++) {
		tempС = matrixC[i];
		for (int j = 0; j < M; j++)
		{
			tempB = matrixB[j];
			for (int k = 0; k < N; k++) {
				add(tempС[k], mul(matrixA[i][j], tempB[k]));
			}
		}

	}

	return matrixC;
}

// сравнение
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

// сравнение
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

// освобождение памяти
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
