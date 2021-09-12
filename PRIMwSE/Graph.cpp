#include "Graph.hpp"


int Graph::GetVal(int xPos, int yPos) const
{
	if (_rowWidth == 0 || _matrix.empty()) // matrix not specified
	{
		printf("Matrix not set !\n");
		return -1;
	}
	return _matrix[xPos + _rowWidth * yPos];
}

bool Graph::SetMatrix(std::vector<int>&& matrix, int width)
{
	if (matrix.size() % width == 0 && width != 0)
	{
		_matrix = matrix;
		_rowWidth = width;
	}
	// Check if matrix is symethrical 
	if(CheckGraph())
		return true;

	printf("Invalid matrix! (symethrical square matrix must be provided)\n");
	return false;
}

int Graph::GetRoot() const
{
	return _rootIdx;
}

void Graph::RmEdge(int x, int y)
{
	if (x < _rowWidth && y < _rowWidth)
	{
		_matrix[x + _rowWidth * y] = 0;
		_matrix[y + _rowWidth * x] = 0;
		return;
	}
	printf("Invalid coordinates!!!\n");
}

void Graph::AddEdge(int x, int y, int cost)
{
	if (x < _rowWidth && y < _rowWidth)
	{
		_matrix[x + _rowWidth * y] = cost;
		_matrix[y + _rowWidth * x] = cost;
		return;
	}
}

Edges Graph::GetAllEdges()
{
	Edges edg{};
	int startX;
	int cost;
	const unsigned maxPossibleEdges =
		(_rowWidth * (_rowWidth - 1)) / 2 + _rowWidth;

	edg.reserve(maxPossibleEdges);
	startX = 1;

	for (int y{ 0 }; y < _rowWidth - 1; ++y)
	{
		for (int x{ startX }; x < _rowWidth; ++x)
		{
			cost = GetVal(x, y);
			if (cost)
			{
				edg.push_back(Edge{ x, y, cost });
			}
		}
		++startX;
	}

	return edg;
}

bool Graph::CheckGraph() 
{
	for (int x = 0; x < _rowWidth; x++)
	{
		for (int y = 0; y < _rowWidth; y++)
		{
			if (_matrix[x + _rowWidth * y] != _matrix[y + _rowWidth * x])
				return false;
		}
	}

	for (int x = 0; x < _rowWidth; x++)
	{
		if (_matrix[x + _rowWidth * x] != 0)
			return false;
	}
	return true;
}
