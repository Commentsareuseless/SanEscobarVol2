#include "TxtParser.hpp"
#include "Matrix.hpp"

#include <utility>

int main()
{
	NeighMatrix matrix;
	Matrix graph;
	int matrixSize{ 0 };

	matrixSize = TxtParser::MakeMatrix(matrix, "graph.txt");

	graph.SetMatrix(std::move(matrix), matrixSize);

	printf("Get element on 2 1 = %d\n", graph.GetVal(2,1));
}
