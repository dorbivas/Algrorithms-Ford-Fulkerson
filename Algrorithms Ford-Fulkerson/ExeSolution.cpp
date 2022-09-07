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
			//Graph* copyGraph = new Graph(graph);//COPY CONSTRUCTOR
			int maxFlow=0;
			auto maxFlowBfs = getMaxFlow(*graph, sourceSink[0], sourceSink[1],false);
			cout << "BFS Method:" << endl;
			cout << "Max flow = " << maxFlowBfs << endl;
			//TODO MINCUT
			
			/*auto maxFlowDji = getMaxFlow(*copyGraph, sourceSink[0], sourceSink[1], true);
			cout << "Greedy Method:" << endl;
			cout << "Max flow = " << maxFlowDji << endl;*/
			//TODO MINCUT
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
	vector<graphArc> edgesArrInput; // data meberm

	while (numOfVertices <= 0) {
		cout << "Enter the number of vertices in the graph\n";
		cin >> numOfVertices;//TODO EXCEPTION
	}

	while (numOfArcs <= 0) {
		cout << "Enter the number of arcs in the graph\n";
		cin >> numOfArcs;//TODO EXCEPTION
	}

	while (s <= 0) {
		cout << "Enter s\n";
		cin >> s;
	}

	while (t <= 0) {
		cout << "Enter t\n";
		cin >> t;
	}
	if(s==t)
	{
		ProgramException e;
		e.isConnected = false;
		throw e;
	}
	else
	{
		sourceSink[0] = s - 1;
		sourceSink[1] = t - 1;

		for (int i = 0; i < numOfArcs; i++)
		{
			int v1 = 0, v2 = 0, capacity = 0;
			cout << "Enter v1, v2, capacity\n";
			cin >> v1 >> v2 >> capacity;
			//TODO EXCEPTION- >0
			edgesArrInput.push_back(graphArc(v1 - 1, v2 - 1, capacity));
		}

		createGraphFromInput(numOfVertices, numOfArcs, edgesArrInput);
		return sourceSink;
	}
	
}

void ExeSolution::createGraphFromInput(const int& vertixAmount, const int& arcsAmount, const vector<graphArc>& edgesArrInput)
{
	graph = new Graph(vertixAmount);
	graph->vertixAmount = vertixAmount;

	for (int i = 0; i < arcsAmount; i++)
	{
		graphArc arc = edgesArrInput[i];
		graph->AddArc(edgesArrInput[i].startVertex, edgesArrInput[i].endVertex, edgesArrInput[i].capacity);
	}

}

int ExeSolution::getMaxFlow(Graph& graph, int source, int sink,bool isItGreedyMethod)//TODO COMMON FUNCTION
{
	int maxFlow = 0;
	vector<int> parent(graph.vertixAmount);
	if (isItGreedyMethod) {
		while (Djikstra(graph, source, sink, parent))
		{
			int pathFlow = INT_MAX;
			for (int i = sink; i != source; i = parent[i])
			{
				pathFlow = min(pathFlow, graph.GetAdjList(parent[i]).head->capacity);
			}
			for (int i = sink; i != source; i = parent[i])
			{
				graph.IncreaseArcFlow(parent[i], i, pathFlow);

				if (graph.ArcExists(i, parent[i]))
					graph.IncreaseArcFlow(parent[i], i, -pathFlow);
				else
					graph.AddArc(i, parent[i], pathFlow);
			}
			maxFlow += pathFlow;
		}
	}
	else
	{
		while (BFS(source, sink, parent))
		{
			int pathFlow = INT_MAX;
			for (int i = sink; i != source; i = parent[i])
			{
				pathFlow = min(pathFlow, graph.GetAdjList(parent[i]).head->capacity);
			}
			for (int i = sink; i != source; i = parent[i])
			{
				graph.IncreaseArcFlow(parent[i], i, pathFlow);

				if (graph.ArcExists(i, parent[i]))
					graph.IncreaseArcFlow(parent[i], i, -pathFlow);
				else
					graph.AddArc(i, parent[i], pathFlow);
			}
			maxFlow += pathFlow;
		}
		
	}
	return maxFlow;
	
}


bool ExeSolution::BFS(int source, int sink, vector<int>& parent)
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

bool ExeSolution::Djikstra(Graph& graph, int source, int sink, vector<int>& parent)
{
	Heap Q(graph.vertixAmount);
	vector<int> capacitys(graph.vertixAmount); //Weight array

	for (int i = 0; i < graph.vertixAmount; i++)
	{
		capacitys[i] = INT_MAX;
	}
	capacitys[source] = 0;
	Q.Build(capacitys);
	
	while (!Q.IsEmpty())
	{
		int u = Q.DeleteMin();
		Node* currNode = this->graph->GetAdjList(u).head;
		while (currNode != nullptr)
		{
			if (capacitys[currNode->nodeId] < capacitys[u] + currNode->capacity)//todo <
			{
				capacitys[currNode->nodeId] = capacitys[u] + currNode->capacity;
				parent[currNode->nodeId] = u;
				Q.DecreaseKey(currNode->nodeId, capacitys[currNode->nodeId]);
			}
			currNode = currNode->next;
		}
	}
	return capacitys[sink] != INT_MAX;
}

