#include <vector>

#pragma once
class MatrixBuilder
{
public:
	MatrixBuilder();
	~MatrixBuilder();
	static std::vector<std::vector<double>> transpositionMatrix(std::vector<std::vector<double>> matrix);
	static std::vector<std::vector<double>> createSymmetricMatrix(int n);
};

