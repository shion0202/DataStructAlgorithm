#pragma once
#include <iostream>
#include <queue>
using namespace std;

// �� Ʈ���� �켱���� ť�� ����

struct HeapNode
{
	int data;
	HeapNode* parent;
	HeapNode* left;
	HeapNode* right;
};

class MyPrioirtyQueue
{
public:
	void Push(const int& data);
	void Pop();
	const int& Top();
	int Size();
	bool Empty();

private:
	HeapNode* FindInsertedNode();
	HeapNode* FindLastLeafNode();
	void SwapNode(HeapNode* left, HeapNode* right);

private:
	HeapNode* root;
	int size = 0;
};
