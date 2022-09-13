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

void LinkedList::InsertHead(const int index, const int capacity)
{
	//Create new node
	Node* newNode = new Node;
	newNode->nodeId = index;
	newNode->capacity = capacity;
	newNode->flow = 0;
	newNode->next = nullptr;
	
	if (IsEmpty())//insert head
	{
		head = newNode;
		tail = newNode;
	}
	else {
		Node* curr = head;
		Node* prev = head;
		if (newNode->nodeId < head->nodeId) 
			{
				newNode->next = head;
				head = newNode;
			}
		else {
			while (curr != nullptr && curr->nodeId  < newNode->nodeId)
			{
				prev = curr;
				curr = curr->next;
			}
			/*if (prev == head)
				head->next = newNode;*/
			if (curr == nullptr)//insert tail
			{
				prev->next = newNode;
				tail = newNode;
				tail->next = curr;
			}
			else {
				newNode->next = curr;
				prev->next = newNode;
			}
		}
	}
	++size;
}

void LinkedList::InsertTail(const int start_ver, const int end_ver, const int capacity)
{
	temp = new Node;
	temp->nodeId = end_ver;
	temp->capacity = capacity;
	if (IsEmpty()) {
		InsertHead(start_ver, capacity);
		head->next = temp;
		tail = temp;

	}
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
		<< ", " << vertex.capacity << ") ";
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