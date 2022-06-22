// CholeskyMPI.cpp: определ¤ет точку входа дл¤ консольного приложени¤.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "MatrixBuilder.h"
#include "SolveByCholesky.h"
#include <omp.h>
#include "mpi.h"

#include <stdlib.h>

int main()
{
	setlocale(LC_ALL, "rus");

	int n;
	std::cout << "¬ведите размерность матрицы";
	std::cin >> n;

	std::vector<std::vector<double>> matrixA = MatrixBuilder::createSymmetricMatrix(n);
	std::vector<double> vectorB = matrixA[0];

	std::vector<std::vector<double>> L;

	L.resize(n);

	for (int i = 0; i < L.size(); i++)
		L[i].resize(n);

	int rank;
	int size;
	double startTime = omp_get_wtime();

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int kol = n / size;
	double sum = 0.0;

	for (int i = 1; i <n; i++)
	{

		for (int h = rank * kol; h < (rank + 1)*kol; h++)
		{
			if (h >= i)
			{
				sum = 0.0;
				for (int p = 0; p <= i - 1; p++)
				{
					sum = sum + L[i][p] * L[i][p];
				}

				L[i][i] = sqrt(fabs(matrixA[n*i][i] - sum));

				MPI_Bcast(&L[i][i], 1, MPI_DOUBLE, rank, MPI_COMM_WORLD);

				sum = 0.0;

				for (int p = 0; p <= i - 1; p++)
				{
					sum = sum + L[i][p] * L[h][p];
				}

				L[h][i] = (matrixA[n*h][i] - sum) / L[i][i];

				MPI_Bcast(&L[h][i], 1, MPI_DOUBLE, rank, MPI_COMM_WORLD);
			}
		}
	}

	MPI_Finalize();

	std::vector<std::vector<double>>  transMatrixL = MatrixBuilder::transpositionMatrix(L);

	std::vector<double> vectorX;
	vectorX.resize(n);

	std::vector<double> vectorY;
	vectorY.resize(n);

	double sum1;
	double sum2;

	for (int i = 0; i < n; i++)
	{
		sum1 = 0;
		for (int j = 0; j < i; j++)
		{
			sum1 += vectorY[j] * L[i][j];
		}

		vectorY[i] = (vectorB[i] - sum1) / L[i][i];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		sum2 = 0;
		for (int j = n - 1; j > i; j--) {
			sum2 += vectorX[j] * transMatrixL[i][j];
		}
		vectorX[i] = (vectorY[i] - sum2) / transMatrixL[i][i];
	}

	std::cout << "¬рем¤ выполнени¤ параллельного алгоритма" << omp_get_wtime() - startTime << std::endl;
	system("pause");

    return 0;
}
