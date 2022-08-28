#include "Heap.h"
bool Heap::IsEmpty()
{
	return heapSize == 0;
}

bool Heap::ValidateInput(int nodeId)
{
	if (nodeId >= data.size() || nodeId < 0)
	{
		cout << "Invalid input at DecreaseKey" << endl;
		exit(1);
	}
	return false;
}

void Heap::DecreaseKey(const int nodeId, const int newWeight)
{
	int heapNodeIndex = nodeIDArr[nodeId];
	if (heapNodeIndex > 0 && heapNodeIndex < heapSize)
	{
		while (heapNodeIndex >= 1) {
			swap(data[heapNodeIndex], data[parent(heapNodeIndex)]); // a[i] = a[p(i)] 
			swap(nodeIDArr[data[heapNodeIndex].nodeId], nodeIDArr[data[parent(heapNodeIndex)].nodeId]);
			heapNodeIndex = parent(heapNodeIndex);
		}
		data[0].weight = newWeight;
		fixHeap(0);
	}
}

void Heap::buildHeapFloyd()
{
	for (int i = heapSize / 2; i >= 0; i--)
		fixHeap(i);
}

void Heap::reassignWeights(vector<int>& min)
{
	int i = 0;
	for (HeapNode& node : data)
	{
		node.weight = min[i];
		node.nodeId = i++;
	}
}

//assumes heapSize is correct
void Heap::Build(vector<int>& min)
{
	//assign wieghts at nodeId
	for (int i = 0; i < heapSize; ++i) {
		nodeIDArr.push_back(i);
	}
	reassignWeights(min);
	buildHeapFloyd();
}

int Heap::DeleteMin() {
	if (heapSize < 1)
	{
		cout << "Invalid input" << endl;
		exit(1);
	}
	int delNodeId = data[0].nodeId;
	--heapSize;
	swap(data[0], data[heapSize]);
	swap(nodeIDArr[delNodeId], nodeIDArr[data[heapSize].nodeId]);
	fixHeap(0);

	return(delNodeId);
}

void Heap::fixHeap(int index)
{
	int min;
	int leftIndex = left(index);
	int rightIndex = right(index);

	if ((leftIndex < heapSize) && (data[leftIndex].weight < data[index].weight))
	{
		min = leftIndex;
	}
	else
	{
		min = index;
	}

	if ((rightIndex < heapSize) && (data[rightIndex].weight < data[min].weight))
	{
		min = rightIndex;
	}

	if (min != index)
	{
		swap(nodeIDArr[data[index].nodeId], nodeIDArr[data[min].nodeId]);
		swap(data[index], data[min]);
		fixHeap(min);
	}
}

bool Heap::validatePointingTwoWays() const
{
	bool status = true;
	for (int i = 0; i < heapSize; ++i) {

		status = i == data[nodeIDArr[i]].nodeId;
		if (!status) {

			cout << "nodeId: " << i << " invalid" << endl;
			exit(1);

		}
	}
	return status;
}

bool Heap::validateHeapSorted()
{
	bool status = true;
	for (int i = 0; i < heapSize; ++i) {
		if (left(i) > heapSize || data[i].weight > data[left(i)].weight) {
			status &= false;
		}
		if (right(i) > heapSize || data[i].weight > data[right(i)].weight) {
			status &= false;
		}
		if (!status) {
			cout << "nodeId: " << i << " invalid" << endl;
			exit(1);
		}
		return status;
	}
	return false;
}

