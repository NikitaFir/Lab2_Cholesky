#include "stdafx.h"
#include "SolveByCholesky.h"
#include <omp.h>


SolveByCholesky::SolveByCholesky()
{
}


SolveByCholesky::~SolveByCholesky()
{
}

std::vector<double> SolveByCholesky::solveLinearSystem(std::vector<std::vector<double>> matrixA, 
														std::vector<double> vectorB, int numThreds)
{

	int matrixDimension = matrixA.size();
	std::vector<std::vector<double>> matrixL;

	matrixL.resize(matrixDimension);

	for (int i = 0; i < matrixL.size(); i++)
		matrixL[i].resize(matrixDimension);

	matrixL[0][0] = sqrt(matrixA[0][0]);

	int i = 0;
	int p1, p2, j;
	double sum; 

	for (int j = 1; j < matrixDimension; j++)
	{		
		matrixL[j][i] = matrixA[j][i] / matrixL[0][0];
	}

	#pragma omp parallel for shared(matrixDimension, matrixL) num_threads(numThreds) private(i, j, sum, p1, p2)
	for (i = 1; i < matrixDimension; i++)
	{
		sum = 0.0;

		for (p1 = 0; p1 <= i - 1; p1++)
		{
			sum = sum + matrixL[i][p1] * matrixL[i][p1];
		}

		matrixL[i][i] = sqrt(abs(matrixA[i][i] - sum));

		for (j = i + 1; j < matrixDimension; j++)
		{
			sum = 0.0;
			for (p2 = 0; p2 <= i - 1; p2++)
			{
				sum = sum + matrixL[i][p2] * matrixL[j][p2];
			}

			matrixL[j][i] = (matrixA[j][i] - sum) / matrixL[i][i];
		}
	}

	std::vector<std::vector<double>>  transMatrixL = MatrixBuilder::transpositionMatrix(matrixL);

	std::vector<double> vectorX;
	vectorX.resize(matrixDimension);

	std::vector<double> vectorY; 
	vectorY.resize(matrixDimension); 

	double sum1;
	double sum2;

	for (int i = 0; i < matrixDimension; i++) 
	{
		sum1 = 0;
		for (int j = 0; j < i; j++) 
		{
			sum1 += vectorY[j] * matrixL[i][j];
		}

		vectorY[i] = (vectorB[i] - sum1) / matrixL[i][i];
	}

	for (int i = matrixDimension - 1; i >= 0; i--) 
	{
		sum2 = 0;
		for (int j = matrixDimension - 1; j > i; j--) {
			sum2 += vectorX[j] * transMatrixL[i][j];
		}
		vectorX[i] = (vectorY[i] - sum2) / transMatrixL[i][i];
	}

	return vectorX;
}
