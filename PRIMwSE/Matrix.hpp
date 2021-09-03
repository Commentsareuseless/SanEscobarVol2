#pragma once

#include <vector>
#include <iostream>

class Matrix
{
public:
	int GetVal(int xPos, int yPos)
	{
		if (_rowWidth == 0 || _matrix.empty()) // matrix not specified
		{
			printf("Matrix not set !\n");
			return -1;
		}
		return _matrix[xPos + _rowWidth * yPos];
	}

	void SetMatrix(std::vector<int>&& matrix, int width)
	{
		if (matrix.size() % width == 0 && width != 0)
		{
			_rowWidth = width;
			_matrix = matrix;
			return;
		}
		printf("Invalid matrix! (square matrix must be provided)\n");
	}
private:
	int _rowWidth{ 0 };
	std::vector<int> _matrix;
};
