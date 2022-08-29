#include "ExeSolution.h"

int ExeSolution::runProgram()
{
	try
	{
		readData();

		if (!graph->IsConnectedVisit())
		{
			ProgramException e;
			e.isConnected = false;

			throw e;
		}
		else {
			int maxFlow;
			//auto maxFlowBfs = FordFulkerson(*graph, source, sink); TODO
			cout << "BFS Method:" << endl;
			cout << "Max flow = " << maxFlow << endl;
			//auto maxFlowDji = FordFulkerson(*graph, source, sink);
			cout << "Greedy Method:" << endl;
			cout << "Max flow = " << maxFlow << endl;
		}
	}
	catch (ProgramException e)
	{
		if (!e.isConnected)
		{
			cout << e.what() << endl;
			cout << "The graph is not connected\n";
		}
	}
	catch (...)
	{
		cout << "Unknown error\n";
	}
}

ExeSolution::~ExeSolution()
{
	delete graph;
}

void ExeSolution::readData()
{
	int numOfVertices = 0, numOfArcs = 0, s = 0, t = 0;

	cout << "Enter the number of vertices in the graph\n";
	cin >> numOfVertices;

	cout << "Enter the number of arcs in the graph\n"; //TODO fix this 
	cin >> numOfArcs;

	while (s <= 0) {
		cout << "Enter v1\n";
		cin >> s;
	}

	while (t <= 0) {
		cout << "Enter t\n";
		cin >> t;
	}

	for (int i = 0; i < numOfArcs; i++)
	{
		int v1 = 0, v2 = 0, capacity = 0;
		cout << "Enter v1, v2, capacity\n";
		cin >> v1 >> v2 >> capacity;
		//graph->AddArc(v1, v2, capacity); TODO
	}

}

void  ExeSolution::createGraphFromInput(const int& vertixAmount, const int& arcsAmount, const vector<graphArc>& edgesArrInput)
{
	graph = new Graph(vertixAmount);
	graph->vertixAmount = vertixAmount;

	for (int i = 0; i < arcsAmount; i++)
	{
		graphArc arc = edgesArrInput[i];
		graph->AddArc(edgesArrInput[i].startVertex, edgesArrInput[i].endVertex, edgesArrInput[i].capacity);
	}

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
			if (!visited[currNode->nodeId] && currNode->capacity > 0)
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
