#include "ExeSolution.h"



int ExeSolution::runProgram()
{
	return 0;
}

int ExeSolution::getMaxFlow(int source, int sink, int parent[], int path[], int pathCapacity[], int pathFlow[], int pathFlowIndex[])
{
	int maxFlow = 0;
	while (BFS(source, sink, parent))
	{
		int pathFlow = INT_MAX;
		for (int i = sink; i != source; i = parent[i])
		{
			pathFlow = min(pathFlow, pathCapacity[i]); // todo FIX
		}
		for (int i = sink; i != source; i = parent[i])
		{
			pathFlowIndex[i] += pathFlow;
			pathFlowIndex[parent[i]] -= pathFlow;
		}
		maxFlow += pathFlow;
	}
	return maxFlow;
}

int ExeSolution::Djikstra(int source, int sink)
{
	return 0;
}

bool ExeSolution::BFS(int source, int sink, int parent[])
{
	bool visited[1];//[graph.vertixAmount]; // TODO get the graph
	for (int i = 0; i < 1; ++i)// graph.vertixAmount; ++i)
	{
		visited[i] = false;
	}
	std::queue<int> q;
	q.push(source);
	visited[source] = true;
	parent[source] = -1;
	while (!q.empty())
	{
		int curr = q.front();
		q.pop();
		Node* currNode = NULL;// graph.adjGraphArr[curr].head;
		while (currNode != nullptr)
		{
			if (!visited[currNode->nodeId] && currNode->weight > 0)
			{
				q.push(currNode->nodeId);
				visited[currNode->nodeId] = true;
				parent[currNode->nodeId] = curr;
			}
			currNode = currNode->next;
		}
	}
	return visited[sink];
}
