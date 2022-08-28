#pragma once
#include <iostream>
#include "LinkedList.h"

using namespace std;

// structure to store edges
struct graphEdge {
	int startVertex, endVertex, weight;
	graphEdge() {}

	graphEdge(int _startVer, int _endVer, int _weight) : startVertex(_startVer), endVertex(_endVer), weight(_weight)
	{}
}; 

class Graph {
public:
	int vertixAmount;
	int edgesAmount;

	Graph(int numberOfVector);
	~Graph();

	void MakeEmptyGraph();
	bool IsAdjacent(int startVer, int endVer) const;
	void AddEdge(int start_ver, int end_ver, int weight);
	bool RemoveEdge(int startVer, int endVer);

	bool IsConnectedVisit();
	void PrintColorArray() const;
	LinkedList& GetAdjList(int index) const;

	Node* GetAdjListNode(int index, LinkedList adjArrGraph);
	LinkedList& operator [](int start_ver) const;
	friend ostream& operator<<(ostream& os, Graph& graph);

private:
	enum eColor { WHITE, GRAY, BLACK };
	LinkedList* adjGraphArr;
	eColor* colorArr;
	int FLAG_INIT = false;

	void visit(int vertexId);
	bool edgeExists(int startVer, int endVer) const;
	static Node* createAdjNode(int value, int weight);
	void setFlagInit(int flagInit);
	friend ostream& operator<<(ostream& os, const Graph& graph);
};

