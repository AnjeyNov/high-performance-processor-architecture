#include "function.h"

int main() {
	setlocale(LC_ALL, "Russian");

	T**** matrixA = allocation(L, M, l, m);
	T**** matrixB = allocation(M, N, m, n);

	generateValues(matrixA, L, M, l, m);
	generateValues(matrixB, M, N, m, n);

	ULONGLONG startTime;
	ULONGLONG endTime;

	ULONGLONG resultWithVectrorized;
	ULONGLONG resultNotVectorized;
	ULONGLONG resultSSE;

	T**** matrixC1 = allocation(L, N, l, n);
	T**** matrixC2 = allocation(L, N, l, n);
	T**** matrixC3 = allocation(L, N, l, n);
	
	startTime = GetTickCount64();
	fullMultiply(matrixA, matrixB, matrixC1, multiply, addition);
	endTime = GetTickCount64();

	resultWithVectrorized = endTime - startTime;
	
	startTime = GetTickCount64();
	fullMultiply(matrixA, matrixB, matrixC2, multiplyNotVectorized, additionNotVectorized);
	endTime = GetTickCount64();

	resultNotVectorized = endTime - startTime;

	startTime = GetTickCount64();
	fullMultiply(matrixA, matrixB, matrixC3, multiplySSE, additionSSE);
	endTime = GetTickCount64();

	resultSSE = endTime - startTime;

	if (equals(matrixC2, matrixC3)) {
		std::cout << "Матрицы равны" << std::endl;
	}
	else {
		std::cout << "Матрицы не равны"<< std::endl;
	}

	std::cout << "Время с векторизацией: " << resultWithVectrorized << "." << std::endl;
	std::cout << "Время без векторизации: " << resultNotVectorized << "." << std::endl;
	std::cout << "Время  SSE: " << resultSSE << "." << std::endl;

	destroy(matrixA, L, M, l, m);
	destroy(matrixB, M, N, m, n);
	destroy(matrixC1, L, N, l, n);
	destroy(matrixC2, L, N, l, n);
	destroy(matrixC3, L, N, l, n);
	
	system("pause");
}