#pragma once

#include "Graph.hpp"

#include <vector>

class PathCalculator
{
public:
	// Every index in instances  is num of part. node, value is distance from source node
	static void CalcShortestPaths(
		const Graph& graph, 
		std::vector<int>& out_distances);

private:
	static int GetMinDistance(
		std::vector<int>& dist_array,
		std::vector<bool>& isProcessed);
};
