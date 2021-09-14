#include "TxtParser.hpp"
#include "Graph.hpp"
#include "PathCalculator.hpp"

#include <utility>

void pause()
{
	char c;
	printf("Wcisnij enter aby kontynuowac...\n");
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get(c);
}

int main()
{
	NeighMatrix matrix;
	Graph graph;
	Edges graphEdges{};
	Edges resultEdges{};
	int matrixSize{ 0 };
	std::vector<int> initialShortestPaths{};
	std::vector<int> nthShortestPaths{};
	

	matrixSize = TxtParser::MakeMatrix(matrix, "graph.txt");

	if (matrixSize < 0)
	{
		printf("Nalezy poprawic macierz w pliku txt\n");
		pause();
		return 1;
	}

	if (!graph.SetMatrix(std::move(matrix), matrixSize))
	{
		printf("Nalezy poprawic macierz w pliku txt\n");
		pause();
		return 1;
	}

	PathCalculator::CalcShortestPaths(graph, initialShortestPaths);

	printf("Calculated initial shortest paths: \n");
	for (int node{ 0 }; node < initialShortestPaths.size(); ++node)
	{
		printf("Node: %d\tCost: %d\n", node, initialShortestPaths[node]);
	}

	graphEdges = graph.GetAllEdges();

	printf("All created edges: \n");
	for (auto& edge : graphEdges)
	{
		printf("Edge %d<->%d cost: %d\n", edge.x, edge.y, edge.cost);
	}

	for (auto& edge : graphEdges)
	{
		graph.RmEdge(edge.x, edge.y);

		if (!PathCalculator::CalcShortestPaths(graph, nthShortestPaths))
		{
			printf("[NOTE] Usuniecie krawedzi %d<->%d spowoduje ze graf stanie sie niespojny\n",
				edge.x, edge.y);
			graph.AddEdge(edge.x, edge.y, edge.cost);
			continue;
		}

		if (nthShortestPaths == initialShortestPaths)
		{
			resultEdges.push_back(edge);
		}

		graph.AddEdge(edge.x, edge.y, edge.cost);
	}

	if (resultEdges.empty())
	{
		printf("Nie znaleziono zadnych kandydatow na lotnisko :( \n");
		pause();
		return 1;
	}

	printf("Kandydaci na lotnisko: \n");
	for (auto& edge : resultEdges)
	{
		printf("Autostrada pomiedzy %d<->%d \n", edge.x, edge.y);
	}
	// Pause execution
	pause();
}
