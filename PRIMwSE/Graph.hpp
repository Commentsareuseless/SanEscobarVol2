#pragma once

#include <vector>
#include <iostream>

// for convenient storage of results :)
struct Edge
{
	Edge(int _x, int _y, int _cost) :
		x(_x), y(_y), cost(_cost)
	{
	}

	int x, y;
	int cost;
};

using Edges = std::vector<Edge>;

class Graph
{
public:
	int GetVal(int xPos, int yPos) const;

	[[nodiscard]]
	bool SetMatrix(std::vector<int>&& matrix, int width);
	int GetSize() const { return _rowWidth; }
	int GetRoot() const;
	// For later matrix manipulation
	void RmEdge(int x, int y);
	void AddEdge(int x, int y, int cost);
	Edges GetAllEdges();

private:
	int _rootIdx{ 0 };
	int _rowWidth{ 0 };
	std::vector<int> _matrix;
};
