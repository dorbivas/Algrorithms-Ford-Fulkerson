#include "Graph.h"
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

		if (currNode->brother->includedFlag != true) //if not brothers
		{
			currNode->brother->includedFlag = true;
			currNode->includedFlag = true;
			if (colorArr[currNode->nodeId] == WHITE) {
				visit(currNode->nodeId);
			}
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

void Graph::AddArc(int start_ver, int end_ver, int capacity)
{
	if (IsAdjacent(start_ver, end_ver) == true)
	{
		throw ProgramException();
	}
	else
	{
		graph[start_ver].InsertTail(end_ver, capacity);
		graph[end_ver].InsertTail(start_ver, capacity);
		graph[end_ver].tail->brother = graph[start_ver].tail;
		graph[start_ver].tail->brother = graph[end_ver].tail;
		++edgesAmount;
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
		if (ArcExists(startVer, endVer) == true)
		{
			status |= graph[startVer].RemoveNode(endVer);
			if (status) {
				status |= graph[endVer].RemoveNode(startVer);
				if (status)
					--edgesAmount;
				else
					throw "system fail";
			}
			else
				throw "system fail";
		}
		else {
			status = false;
			throw ProgramException();
		}
	}
	else
		status = false;

	return status;
}


void Graph::setFlagInit(const int flagInit)
{
	FLAG_INIT = flagInit;
}

bool Graph::IsAdjacent(const int startVer, const int endVer) const
{
	return ArcExists(endVer, startVer);
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

//next and brother aren't set here because they might not exist yet
Node* Graph::createAdjNode(const int value, const int capacity)
{
	auto newNode = new Node();
	newNode->nodeId = value;
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