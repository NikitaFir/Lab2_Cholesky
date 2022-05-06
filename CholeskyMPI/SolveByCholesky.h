#include <vector>
#include "MatrixBuilder.h"

#pragma once
class SolveByCholesky
{


public:
	SolveByCholesky();
	~SolveByCholesky();
	static std::vector<double> SolveByCholesky::solveLinearSystem(std::vector<std::vector<double>> matrixA, 
		std::vector<double> vectorB, int numThreds);
};

