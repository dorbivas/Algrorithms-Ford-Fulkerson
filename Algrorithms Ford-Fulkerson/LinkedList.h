#pragma once
#include <iostream>
#include "ProgramException.h"

#define UNINIT -1;
using namespace std;

struct Node
{
	int nodeId = UNINIT;
	int capacity = UNINIT;
	Node* next = nullptr;
	bool includedFlag = false;
	Node* brother = nullptr;
	~Node() = default;

private:
	friend ostream& operator<<(ostream& os, const Node& vertex);
};


class LinkedList
{
public:
	Node* head = nullptr;
	Node* tail = nullptr;
	Node* find(int data);
	int size = 0;

	~LinkedList();
	bool IsEmpty() const;
	void InsertHead(int index, int capacity);
	void InsertTail(const int start_ver, const int end_ver, int capacity);
	bool RemoveNode(int indexRemoved);


private:
	Node* temp = nullptr;
	friend auto operator<<(ostream& os, const LinkedList& vertex)->ostream&;

};

