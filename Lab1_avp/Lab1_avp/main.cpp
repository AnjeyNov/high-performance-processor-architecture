#include "function.h"

int main() {
	setlocale(LC_ALL, "Russian");

	T**** matrixA = allocation(L, M, l, m);
	T**** matrixB = allocation(M, N, m, n);

	generateValues(matrixA, L, M, l, m);
	generateValues(matrixB, M, N, m, n);

	ULONGLONG startTime;
	ULONGLONG endTime;

	ULONGLONG resultTimeWithVectorization;
	ULONGLONG resultTimeWithoutVectorization;
	ULONGLONG resultTimeUsingSSE;

	T**** matrixC1 = allocation(L, N, l, n);
	T**** matrixC2 = allocation(L, N, l, n);
	T**** matrixC3 = allocation(L, N, l, n);
	
	startTime = GetTickCount64();
	fullMultiply(matrixA, matrixB, matrixC1, multiply, addition);
	endTime = GetTickCount64();

	resultTimeWithVectorization = endTime - startTime;
	
	startTime = GetTickCount64();
	fullMultiply(matrixA, matrixB, matrixC2, multiplyNotVectorized, additionNotVectorized);
	endTime = GetTickCount64();

	resultTimeWithoutVectorization = endTime - startTime;

	startTime = GetTickCount64();
	fullMultiply(matrixA, matrixB, matrixC3, multiplySSE, additionSSE);
	endTime = GetTickCount64();

	resultTimeUsingSSE = endTime - startTime;

	if (equals(matrixC2, matrixC3)) {
		std::cout << "������� �����" << std::endl;
	}
	else {
		std::cout << "������� �� �����"<< std::endl;
	}

	std::cout << "����� � �������������: " << resultTimeWithVectorization << "." << std::endl;
	std::cout << "����� ��� ������������: " << resultTimeWithoutVectorization << "." << std::endl;
	std::cout << "�����  SSE: " << resultTimeUsingSSE << "." << std::endl;

	std::cout << "��������� � �������������� �������������: " << (double)resultTimeWithoutVectorization / resultTimeWithVectorization << std::endl;
	std::cout << "��������� � SSE: " << (double)resultTimeUsingSSE / resultTimeWithoutVectorization << std::endl;

	destroy(matrixA, L, M, l, m);
	destroy(matrixB, M, N, m, n);
	destroy(matrixC1, L, N, l, n);
	destroy(matrixC2, L, N, l, n);
	destroy(matrixC3, L, N, l, n);
	
	system("pause");
}