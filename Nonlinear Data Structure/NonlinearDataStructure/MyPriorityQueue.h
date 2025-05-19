#pragma once
#include <iostream>
#include <queue>
using namespace std;

// 힙 트리로 우선순위 큐를 구현

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
