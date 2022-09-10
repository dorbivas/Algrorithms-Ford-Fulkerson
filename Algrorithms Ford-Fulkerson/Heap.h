#pragma once
#include <vector>
#include "Heap.h"
#include <iostream>
#include <ostream>
using namespace std;

#define MAX_SIZE 100

class Heap {
public:
	struct HeapNode
	{
		int weight;
		unsigned int nodeId;
	};

	//Interface
	void Build(vector<int>& min);
	bool IsEmpty();
	void DecreaseKey(int searchedIndex, int newWeight);
	int DeleteMin();

	Heap(int size) : heapSize(size), data(size) { };
	int heapSize;
	bool ValidateInput(int nodeId);
	int GetSize() { return heapSize; }

private:
	vector<int>nodeIDArr; //nodeID at location x points to the nodeId of nodeID in data.
	vector<HeapNode> data;
	int parent(int index) { return (index - 1) / 2; }
	int left(int index) { return (2 * index + 1); }
	int right(int index) { return (2 * index + 2); }
	void  fixHeap(int index);

	void buildHeapFloyd();
	void reassignWeights(vector<int>& min);
	bool validatePointingTwoWays() const; //validates if two way pointers are correct, otherwise exits.
	bool validateHeapSorted();
};

