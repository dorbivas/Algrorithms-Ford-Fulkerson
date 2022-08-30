#include "ExeSolution.h"

int ExeSolution::runProgram()
{
	
	try
	{
		int* sourceSink = readData();

		if (!graph->IsConnectedVisit())
		{
			ProgramException e;
			e.isConnected = false;

			throw e;
		}
		else {
			int maxFlow=0;
			auto maxFlowBfs = FordFulkerson(*graph, sourceSink[0], sourceSink[1]);
			cout << "BFS Method:" << endl;
			cout << "Max flow = " << maxFlowBfs << endl;
			//auto maxFlowDji = FordFulkerson(*graph, sourceSink[0], sourceSink[1]);
			cout << "Greedy Method:" << endl;
		//	cout << "Max flow = " << maxFlowDji << endl;
			return 0;
		}
	}
	catch (ProgramException e)
	{
		if (!e.isConnected)
		{
			cout << e.what() << endl;
			cout << "The graph is not connected\n";
		}
		return 0;
	}
	catch (...)
	{
		cout << "Unknown error\n";
		return 0;
	}
}

ExeSolution::~ExeSolution()
{
	delete graph;
}

int* ExeSolution::readData()
{
	int numOfVertices = 0, numOfArcs = 0, s = 0, t = 0;
	int sourceSink[2];
	vector<graphArc> edgesArrInput;

	while (numOfVertices <= 0) {
		cout << "Enter the number of vertices in the graph\n";
		cin >> numOfVertices;//TODO EXCEPTION
	}

	while (numOfArcs <= 0) {
		cout << "Enter the number of arcs in the graph\n";
		cin >> numOfArcs;//TODO EXCEPTION
	}

	while (s <= 0) {
		cout << "Enter v1\n";
		cin >> s;
	}

	while (t <= 0) {
		cout << "Enter t\n";
		cin >> t;
	}
	sourceSink[0] = s;
	sourceSink[1] = t;

	for (int i = 0; i < numOfArcs; i++)
	{
		int v1 = 0, v2 = 0, capacity = 0;
		cout << "Enter v1, v2, capacity\n";
		cin >> v1 >> v2 >> capacity;
		//TODO EXCEPTION- >0
		edgesArrInput.push_back(graphArc(v1-1, v2-1, capacity));
	}
		
	createGraphFromInput(numOfVertices, numOfArcs, edgesArrInput);
	return sourceSink;
	
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
		int pathFlow = 8000000000;
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

int ExeSolution::FordFulkerson(Graph& graph, int source, int sink) { //TODO

	int* parent = new int[graph.vertixAmount];
	int* path=new int[graph.vertixAmount];
	int* pathCapacity = new int[graph.vertixAmount];
	int* pathFlow = new int[graph.vertixAmount];
	int* pathFlowIndex = new int[graph.vertixAmount];
	for (int i = 0; i < graph.vertixAmount; i++)
	{
		parent[i] = -1;
		path[i] = -1;
		pathCapacity[i] = 0;
		pathFlow[i] = 0;
		pathFlowIndex[i] = 0;
	}
	/*delete parent;
	delete path;
	delete pathCapacity;
	delete pathFlow;
	delete pathFlowIndex;*/
	
	return getMaxFlow(source, sink, parent, path, pathCapacity, pathFlow, pathFlowIndex);
}

bool ExeSolution::BFS(int source, int sink, int parent[])
{
	const int vertixAmount= this->graph->vertixAmount;
	bool* visited = new bool[vertixAmount];
	for (int i = 0; i < vertixAmount; ++i)
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
		Node* currNode = this->graph->GetAdjList(curr).head;
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

int ExeSolution::Djikstra(int source, int sink)//TODO
{
	return 0;
}
