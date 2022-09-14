#include <vector>
#include <istream>
#include <fstream>
#include <string>
#include <queue>
#include "graph.h"
#include <algorithm>

using namespace std;

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
	int getMaxFlow(Graph& graph,int source, int sink, bool isItGreedyMethod);
	void findMinCut(Graph& graph, int source, int sink);
	bool Djikstra(Graph& graph, int source, int sink, vector<int>& parent);
	bool BFS(int source, int sink, vector<int>& parent);

};