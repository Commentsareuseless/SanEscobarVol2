#include "PathCalculator.hpp"

#include <limits>

bool PathCalculator::CalcShortestPaths(const Graph& graph, std::vector<int>& out_dist)
{
    std::vector<bool> isProcessed{};
    int graphRow = graph.GetSize();

    isProcessed.reserve(graphRow);
    out_dist.clear();
    if (out_dist.capacity() < graphRow)
    {
        out_dist.reserve(graphRow);
    }

    for (int i{ 0 }; i < graphRow; ++i)
    {
        out_dist.push_back(INT_MAX);
        isProcessed.push_back(false);
    }

    out_dist[0] = 0;


    for (int count = 0; count < graphRow - 1; count++) 
    {
        int candidate = GetMinDistance(out_dist, isProcessed);
        if (candidate == -1)
        {
            out_dist.clear(); // Make sure this is invalid
            return false;
        }
        isProcessed[candidate] = true;

        for (int node{ 0 }; node < graphRow; ++node)
        {
            if (!isProcessed.at(node) && graph.GetVal(candidate, node) && out_dist.at(candidate) != INT_MAX
                && out_dist.at(candidate) + graph.GetVal(candidate, node) < out_dist.at(node))
            {
                out_dist.at(node) = out_dist.at(candidate) + graph.GetVal(candidate,node);
            }
        }
    }
   
    return true;
}

int PathCalculator::GetMinDistance(std::vector<int>& dist_array, std::vector<bool>& isProcessed)
{
    int min_dist, min_idx;

    min_idx = -1;
    min_dist = INT_MAX;

    for (unsigned i{ 0 }; i < dist_array.size(); ++i)
    {
        if (isProcessed[i] == false && dist_array[i] < min_dist)
        {
            min_dist = dist_array[i];
            min_idx = i;
        }
    }
    return min_idx;
}
