#pragma once
#include <vector>
#include <istream>
#include <fstream>
#include <string>
#include <queue>
#include "Graph.h"

class ExeSolution
{
public:
	int runProgram();
	ExeSolution();
	~ExeSolution();

private:
	void readData();
	
	int FordFulkerson(Graph& graph, int source, int sink);
	int getMaxFlow(int source, int sink);
	int getMaxFlow(int source, int sink, int parent[], int path[], int pathCapacity[], int pathFlow[], int pathFlowIndex);
	int Djikstra(int source, int sink);
	bool BFS(int source, int sink, int parent[]);

};