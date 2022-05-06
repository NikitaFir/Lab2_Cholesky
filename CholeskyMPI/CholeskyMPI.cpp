// CholeskyMPI.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "MatrixBuilder.h"
#include "SolveByCholesky.h"
#include <omp.h>

#include <stdlib.h>

int main()
{
	setlocale(LC_ALL, "rus");

	std::vector<int> threadsNum = { 1, 2, 4, 6, 8 };
	std::vector<int> matrixDimension = { 10, 100, 1000, 3000, 6000 };

	for (int i : matrixDimension)
	{

		std::cout << "Размерность матрицы: " << i << std::endl;

		std::vector<std::vector<double>> matrixA = MatrixBuilder::createSymmetricMatrix(i);
		std::vector<double> vectorB = matrixA[0];

		double startTime;

		for (int j : threadsNum)
		{
			startTime = omp_get_wtime();
			std::vector<double> result = SolveByCholesky::solveLinearSystem(matrixA, vectorB, j);
			std::cout << "Время выполнения параллельного алгоритма при " << j 
				<< " потоках(е): " << omp_get_wtime() - startTime << std::endl;
		}
		std::cout << std::endl;
	}

	system("pause");

    return 0;
}

