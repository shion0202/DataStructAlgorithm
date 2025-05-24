#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

// 다수의 정렬된 배열을 합쳐서 하나의 정렬된 배열을 만드는 기능을 힙을 이용하여 구현하는 문제

struct HeapNode
{
	int data;
	int arrayIndex;
	int elementIndex;

	bool operator>(const HeapNode& other) const
	{
		return data > other.data;
	}

	bool operator<(const HeapNode& other) const
	{
		return data < other.data;
	}
};

class MergeHeap
{
public:
	MergeHeap(const vector<vector<int>>& arrays);

	HeapNode GetMinData();

private:
	int CompareIndex();

private:
	vector<vector<int>> minVectors;
	vector<int> vectorIndexes;
	priority_queue<HeapNode, vector<HeapNode>, greater<HeapNode>> minMergeHeap;
};