#include "ExeSolution.h"

int ExeSolution::runProgram()
{
	try
	{
		readData();
		if (!graph->IsConnectedVisit())
		{
			//ProgramException e;
			//e.isConnected = false;

			//throw e;
		}
		else {
			int maxFlow = 0;
			auto maxFlowBfs = getMaxFlow(*graph, S, T, false);
			cout << "BFS Method:" << endl;
			cout << "Max flow = " << maxFlowBfs << endl;
			findMinCut(*graph, S, T);

			auto maxFlowDji = getMaxFlow(*djGraph, S, T, true);
			cout << "Greedy Method:" << endl;
			cout << "Max flow = " << maxFlowDji << endl;
			findMinCut(*djGraph, S, T);
			
			return 0;
		}
	}
	catch (exception e)
	{
		//if (!e.isConnected)
		//{
			cout << "The graph is not connected\n";
	//	}
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

void ExeSolution::readData()
{
	int numOfVertices = 0;
	int numOfArcs = 0;
	int s = 0;
	int t = 0;
	vector<graphArc> edgesArrInput;
	bool isValid = false;

	cout << "Enter number of vertices: \n";
	cin >> numOfVertices;
	cout << "Enter number of arcs: \n";
	cin >> numOfArcs;
	cout << "Enter source vertex: \n";
	cin >> s;
	cout << "Enter sink vertex: \n";
	cin >> t;
	if (numOfVertices > 0 && numOfArcs > 0 && s >= 0 && t >= 0 && s <= numOfVertices && t <= numOfVertices && s != t)
	{
		isValid = true;
	}
	else
	{
		cout << "Invalid input. Try again." << endl;
		exit(1);
	}

	if (isValid)
	{
		S = s - 1;
		T = t - 1;

		for (int i = 0; i < numOfArcs; i++)
		{
			int v1 = 0, v2 = 0, capacity = 0;
			cout << "Enter v1, v2, capacity\n";
			cin >> v1 >> v2 >> capacity;
			//Check is v1 and v2 are in range
			if (v1 >= 1 && v1 <= numOfVertices && v2 >= 1 && v2 <= numOfVertices && capacity > 0 && v1 != v2)
			{
				edgesArrInput.push_back({ v1 - 1, v2 - 1, capacity });
			}
			else
			{
				cout << "Invalid input. Try again." << endl;
				exit(1);
			}
		}
		createGraphFromInput(numOfVertices, numOfArcs, edgesArrInput);
	}
}

void ExeSolution::createGraphFromInput(const int& vertixAmount, const int& arcsAmount, const vector<graphArc>& edgesArrInput)
{
	graph = new Graph(vertixAmount);
	djGraph = new Graph(vertixAmount);

	graph->vertixAmount = vertixAmount;

	for (int i = 0; i < arcsAmount; i++)
	{
		graphArc arc = edgesArrInput[i];
		//check if arc exist in graph
		if (false)//graph->ArcExists(arc.startVertex, arc.endVertex)) // TODO 
		{
			cout << "Arc already exist. Try again." << endl;
			exit(1);
		}
		else
		{
			graph->AddArc(arc.startVertex, arc.endVertex, arc.capacity, true);
			djGraph->AddArc(arc.startVertex, arc.endVertex, arc.capacity, true);
			graph->AddArc(edgesArrInput[i].endVertex, edgesArrInput[i].startVertex, 0, false);
			djGraph->AddArc(edgesArrInput[i].endVertex, edgesArrInput[i].startVertex, 0, false);
		}
	}
}

int ExeSolution::getMaxFlow(Graph& graph, int source, int sink, bool isItGreedyMethod)
{
	int maxFlow = 0;
	vector<int> parent(graph.vertixAmount);
	int pathFlow = INT8_MAX;
	int u = source;

	while (true) {
		if (isItGreedyMethod) {
			if (!Djikstra(graph, source, sink, parent))
				break;
		}
		else {
			if (!BFS(source, sink, parent))
				break;
		}


		for (int v = sink; v != source; v = parent[v])
		{
			u = parent[v];
			pathFlow = min(pathFlow, graph[u].find(v)->capacity);// graph.GetAdjList(parent[v]).head->capacity);
		}
		for (int v = sink; v != source; v = parent[v])
		{
			u = parent[v];
			graph.IncreaseArcFlow(u, v, pathFlow, false);//u->v,  false=forward
			graph.IncreaseArcFlow(v, u, -pathFlow, true);//v->u,  true=opposite edge

		}
		maxFlow += pathFlow;
	}
	return maxFlow;
}
void ExeSolution::findMinCut(Graph& graph, int source, int sink)
{
	vector<int> parent(graph.vertixAmount,-1);
	vector<int> minCut_S, minCut_T;
	
	/*for (int i = 0; i < graph.vertixAmount; i++) {
		parent[i] = -1;
	}*/
	
	BFS(source, sink, parent);
	minCut_S.push_back(source + 1);
	for (int i = 0; i < graph.vertixAmount; i++)
	{
		if(i==source)
			continue;
		
		if (parent[i] != -1)
		{
			minCut_S.push_back(i + 1);
		}
		else
		{
			minCut_T.push_back(i + 1);
		}
	}
	sort(minCut_S.begin(), minCut_S.end());
	sort(minCut_T.begin(), minCut_T.end());
	
	cout << "Min cut: S = { ";
	for (auto i : minCut_S)
	{
		if (i == minCut_S.back())
		{
			cout << i;
		}
		else
		{
			cout << i << ", ";
		}
	}
	cout << " }";
	cout << " T = { ";
	for (auto i : minCut_T)
	{
		if (i == minCut_T.back())
		{
			cout << i;
		}
		else
		{
			cout << i << ", ";
		}
	}
	cout << " }";
	cout << endl;
}


bool ExeSolution::BFS(int source, int sink, vector<int>& parent)
{
	const int vertixAmount = this->graph->vertixAmount;
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

bool ExeSolution::Djikstra(Graph& graph, int source, int sink, vector<int>& parent) {
	priority_queue<int> Q;
	vector<int> dist(graph.vertixAmount, -INT8_MAX);
	vector<bool> visited(graph.vertixAmount, false);
	Q.push(source);
	dist[source] = 0;
	parent[source] = -1;
	while (!Q.empty()) {
		int u = Q.top();
		Q.pop();
		if (visited[u]) continue;
		visited[u] = true;
		Node* currNode = graph.GetAdjList(u).head;
		while (currNode != nullptr)
		{
			if (!visited[currNode->nodeId] && currNode->capacity > 0)
			{
				int v = currNode->nodeId;
				int weight = currNode->capacity;
				if (dist[v] < dist[u] + weight) {
					dist[v] = dist[u] + weight;
					parent[v] = u;
					Q.push(v);
				}
			}
			currNode = currNode->next;
		}
	}
	return visited[sink];
}

