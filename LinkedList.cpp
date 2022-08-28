#include "LinkedList.h"

using namespace std;

LinkedList::~LinkedList()
{
	Node* current = head;
	Node* tmpNext = nullptr;
	while (current != nullptr)
	{
		tmpNext = current->next;
		delete current;
		current = tmpNext;
	}
}

bool LinkedList::IsEmpty() const
{
	return head == nullptr;
}

void LinkedList::InsertHead(const int index, const int weight)
{
	temp = new Node;
	temp->nodeId = index;
	temp->weight = weight;

	if (IsEmpty())
	{
		temp->next = nullptr;
		tail = temp;
	}
	else
		temp->next = head;
	head = temp;
	++size;
}

void LinkedList::InsertTail(const int index, const int weight)
{
	temp = new Node;
	temp->nodeId = index;
	temp->weight = weight;
	temp->next = nullptr;
	if (IsEmpty())
		head = tail = temp;

	else
	{
		tail->next = temp;
		tail = temp;
	}
	++size;
}

bool LinkedList::RemoveNode(int indexRemoved)
{
	bool status = false;
	Node* current = head, * prev = nullptr;

	while (current != nullptr)
	{
		if (current->nodeId == indexRemoved) { // if match
			status = true;
			break;
		}
		prev = current;
		current = current->next; // go to prev value
	}

	if (status == false) //not found
		return status;

	Node* tmp = current;
	/*remove from list with 1 node*/
	if (prev == nullptr && current->next == nullptr)
	{
		head = tail = nullptr;
	}
	/*remove first*/
	else if (prev == nullptr && current->next != nullptr)
		head = current->next;
	/*remove last*/
	else if (prev != nullptr && current->next == nullptr)
		prev->next = nullptr;
	else
		prev->next = current->next;

	delete tmp;
	--size;
	return status;
}

Node* LinkedList::find(int data)
{
	int i;
	Node* ret_val = nullptr;
	for (i = 1, temp = head; temp->next != nullptr && temp->nodeId != data; temp = temp->next, i++);
	if (temp->nodeId == data)
	{
		ret_val = temp;
	}
	else if (temp->next == nullptr)
	{
		throw "cant find vertix to remove in list " + this->head->nodeId;
	}
	return ret_val;

}

ostream& operator<<(ostream& os, const Node& vertex)
{
	os << "(" << vertex.nodeId + 1
		<< ", " << vertex.weight << ") ";
	return os;
}

ostream& operator<<(ostream& os, const LinkedList& list)
{
	Node* ptr = list.head;
	if (ptr == nullptr)
	{
		os << "empty";
	}
	while (ptr != nullptr) {
		os << *ptr << "->";
		ptr = ptr->next;

	}
	return os;
}