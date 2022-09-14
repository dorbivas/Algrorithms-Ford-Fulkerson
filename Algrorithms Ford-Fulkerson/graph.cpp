#include "graph.h"
#include "ProgramException.h"

using namespace std;
//if tree is connected, all neighbors should be visited eventually, since we know it has no cycles,
//we can ensure if all nodes were visited they finish black eventually.

Graph::~Graph()
{
	delete[] graph;
}

bool Graph::IsConnectedVisit() {

	for (int i = 0; i < vertixAmount; ++i)
	{
		colorArr[i] = WHITE;
		//Graph arr neighbor list
		Node* currNode = graph[i].head;
		while (currNode != nullptr)
		{
			currNode->includedFlag = false;
			currNode = currNode->next;
		}

	}
	visit(0);
	bool status = true;

	for (int i = 0; i < vertixAmount; ++i) {
		if (colorArr[i] == WHITE)
		{
			status = false;
			break;
		}
	}
	return status;
}

void Graph::visit(int vertexId) {
	colorArr[vertexId] = GRAY;
	Node* currNode = graph[vertexId].head;
	while (currNode != nullptr) {

		currNode->includedFlag = true;
		if (colorArr[currNode->nodeId] == WHITE) {
			visit(currNode->nodeId);
		}
		currNode = currNode->next;
	}
	colorArr[vertexId] = BLACK;
}

Graph::Graph(const int numberOfVector)
{
	vertixAmount = numberOfVector;
	colorArr = new eColor[vertixAmount];
	MakeEmptyGraph();
}

Node* Graph::GetAdjListNode(const int index, LinkedList adjArrGraph)
{
	return adjArrGraph.find(index);
}

LinkedList& Graph::GetAdjList(int index) const
{
	return graph[index];
}

void Graph::MakeEmptyGraph()
{
	graph = new LinkedList[vertixAmount]();
	FLAG_INIT = true;
}

void Graph::AddArc(int startVertex, int endVertex, int capacity, bool toAddEdge)
{
	graph[startVertex].InsertHead(endVertex, capacity);
	++edgesAmount;
}

void Graph::IncreaseArcFlow(int startVertex, int endVertex, int flow, bool opposite)//TODO DELTE COMMENT
{
	if (!ArcExists(startVertex, endVertex))
		return;

	int oldCapacity = graph[startVertex].find(endVertex)->capacity;
	//int oldCapacity = graph[startVertex].head->capacity;
	int newCapacity = oldCapacity - flow;
	if (newCapacity > 0)
	{
		//graph[startVertex].head->capacity = newCapacity;
		//graph[startVertex].head->flow = newCapacity;
		graph[startVertex].find(endVertex)->capacity = newCapacity;
		graph[startVertex].find(endVertex)->flow = newCapacity;
	}
	else {
		RemoveArc(startVertex, endVertex);
	}
}

LinkedList& Graph::operator[](const int start_ver) const
{
	return graph[start_ver];
}

bool Graph::RemoveArc(const int startVer, const int endVer)
{
	bool status = true;
	if (this->graph != nullptr)
	{
		status |= graph[startVer].RemoveNode(endVer);
		if (status) {
			--edgesAmount;
		}
		else
			throw "system fail";
	}
	else
		status = false;

	return status;
}


void Graph::setFlagInit(const int flagInit)
{
	FLAG_INIT = flagInit;
}


bool Graph::ArcExists(const int startVer, const int endVer) const
{
	bool status = false;
	Node* curr = graph[startVer].head;

	while (curr != nullptr)
	{
		if (endVer == curr->nodeId)
		{
			status = true;
			break;
		}
		curr = curr->next;
	}

	return status;
}

Node* Graph::createAdjNode(const int value, const int capacity)
{
	auto newNode = new Node();
	newNode->nodeId = value;
	newNode->flow = 0;
	newNode->capacity = capacity;
	return newNode;
}

ostream& operator<<(ostream& os, Graph& Graph)
{
	os << "Graph adjacency list " << endl << "(start_vertex, end_vertex, capacity):" << endl;
	for (int i = 0; i < Graph.vertixAmount; i++)
	{
		if (Graph.graph[i].head != nullptr)
			os << "VertixId: " << i + 1 << ":" << Graph[i] << endl;
		else
			os << i + 1 << " list is empty. " << endl;
	}
	return os;
}

void Graph::PrintColorArray() const
{
	for (int i = 0; i < vertixAmount; ++i)
	{
		cout << "Index: " << i << " Color: " << colorArr[i] << endl;
	}
}

//print all the vertices connected to a vertex and the flow
void Graph::printAllgraph() const
{
	for (int i = 0; i < vertixAmount; ++i)
	{
		Node* currNode = graph[i].head;
		while (currNode != nullptr)
		{
			cout << "Start vertex: " << i << " End vertex: " << currNode->nodeId << " Flow: " << currNode->capacity << endl;
			currNode = currNode->next;
		}
	}
}
