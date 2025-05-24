#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;

// �ټ��� ���ĵ� �迭�� ���ļ� �ϳ��� ���ĵ� �迭�� ����� ����� ���� �̿��Ͽ� �����ϴ� ����

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