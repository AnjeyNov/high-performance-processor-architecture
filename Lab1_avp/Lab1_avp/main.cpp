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

	startTime = GetTickCount64();
	T**** matrixC1 = fullMultiply(matrixA, matrixB, multiply, addition);
	endTime = GetTickCount64();

	resultWithVectrorized = endTime - startTime;
	
	startTime = GetTickCount64();
	T**** matrixC2 = fullMultiply(matrixA, matrixB, multiplyNotVectorized, additionNotVectorized);
	endTime = GetTickCount64();

	resultNotVectorized = endTime - startTime;

	startTime = GetTickCount64();
	T**** matrixC3 = fullMultiply(matrixA, matrixB, multiplySSE, additionSSE);
	endTime = GetTickCount64();

	resultSSE = endTime - startTime;

	if (equals(matrixC2, matrixC3)) {
		std::cout << true << std::endl;
	}
	else {
		std::cout << false << std::endl;
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