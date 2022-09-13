#pragma once
#include <iostream>
#include "LinkedList.h"

using namespace std;

// structure to store edges
struct graphArc {
	int startVertex, endVertex, capacity;
	graphArc() {}

	graphArc(int _startVer, int _endVer, int _capacity) : startVertex(_startVer), endVertex(_endVer), capacity(_capacity)
	{}
}; 

class Graph {
public:
	int vertixAmount;
	int edgesAmount;

	Graph(int numberOfVector);
	~Graph();

	void MakeEmptyGraph();
	bool ArcExists(int startVer, int endVer) const;
	void AddArc(int start_ver, int end_ver, int capacity, bool toAddEdge); // todo changeames n
	void IncreaseArcFlow(int startVertex, int endVertex, int flow,bool opposite);
	bool RemoveArc(int startVer, int endVer);

	bool IsConnectedVisit();
	void PrintColorArray() const;
	LinkedList& GetAdjList(int index) const;

	Node* GetAdjListNode(int index, LinkedList adjArrGraph);
	LinkedList& operator [](int start_ver) const;
	friend ostream& operator<<(ostream& os, Graph& graph);
	//print graph
	//print graph
	void printAllgraph() const;

private:
	enum eColor { WHITE, GRAY, BLACK };
	LinkedList* graph;
	eColor* colorArr;
	int FLAG_INIT = false;

	void visit(int vertexId);
	static Node* createAdjNode(int value, int capacity);
	void setFlagInit(int flagInit);
	friend ostream& operator<<(ostream& os, const Graph& graph);
};

