#include <vector>
#include <istream>
#include <fstream>
#include <string>
#include <queue>
#include "graph.h"
#include "Heap.h"

class ExeSolution
{
public:
	int runProgram();
	~ExeSolution();
	Graph* graph = nullptr; 
	Graph * djGraph = nullptr;
	int S = NULL;
	int T = NULL;

private:

	void createGraphFromInput(const int& vertixAmount, const int& arcsAmount, const vector<graphArc>& edgesArrInput);
	void readData();
	//int FordFulkerson(Graph& graph, int source, int sink);
	int getMaxFlow(Graph& graph,int source, int sink, bool isItGreedyMethod);
	//int getMaxFlow(int source, int sink, int parent[], int path[], int pathCapacity[], int pathFlow[], int pathFlowIndex[]);
	void findMinCut(Graph& graph, int source, int sink);
	bool Djikstra(Graph& graph, int source, int sink, vector<int>& parent);
	bool BFS(int source, int sink, vector<int>& parent);

};