#include <vector>
#include <istream>
#include <fstream>
#include <string>
#include <queue>
#include "graph.h"

class ExeSolution
{
public:
	int runProgram();
	ExeSolution();
	~ExeSolution();
	Graph* graph = nullptr;

private:
	
	void createGraphFromInput(const int& vertixAmount, const int& arcsAmount, const vector<graphArc>& edgesArrInput);
	void readData();
	int FordFulkerson(Graph& graph, int source, int sink);
	int getMaxFlow(int source, int sink);
	int getMaxFlow(int source, int sink, int parent[], int path[], int pathCapacity[], int pathFlow[], int pathFlowIndex[]);
	int Djikstra(int source, int sink);
	bool BFS(int source, int sink, int parent[]);

};