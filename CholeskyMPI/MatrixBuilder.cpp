#include "stdafx.h"
#include "MatrixBuilder.h"

MatrixBuilder::MatrixBuilder()
{
}


MatrixBuilder::~MatrixBuilder()
{
}

std::vector<std::vector<double>> MatrixBuilder::transpositionMatrix(std::vector<std::vector<double>> matrix)
{
	int rowsMatrix = matrix.size();
	int columnsMatrix = matrix.size();

	std::vector<std::vector<double>> newMatrix;

	newMatrix.resize(rowsMatrix);
	for (int i = 0; i < rowsMatrix; i++)
		newMatrix[i].resize(columnsMatrix);

	for (int i = 0; i < rowsMatrix; i++) 
	{
		for (int j = 0; j < columnsMatrix; j++) 
		{
			newMatrix[j][i] = matrix[i][j];
		}
	}

	return newMatrix;
}

std::vector<std::vector<double>> MatrixBuilder::createSymmetricMatrix(int n)
{
	std::vector<std::vector<double>> outputMatrix;

	outputMatrix.resize(n);
	for (int i = 0; i < n; i++)
		outputMatrix[i].resize(n);

	int rangeMin = 1;
	int rangeMax = 100;

	for (int i = 0; i < n; i++) 
	{
		for (int j = i; j < n; j++) 
		{
			outputMatrix[i][j] = rangeMin + rand() % (rangeMax - rangeMin + 1);
		}
	}

	for (int i = 1; i < n; i++) 
	{
		for (int j = 0; j < i; j++) 
		{
			outputMatrix[i][j] = outputMatrix[j][i];
		}
	}

	return outputMatrix;
}
