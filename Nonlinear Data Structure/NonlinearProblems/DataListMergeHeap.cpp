#pragma once
#include "DataListMergeHeap.h"

MergeHeap::MergeHeap(const vector<vector<int>>& arrays)
{
	// minHeaps 초기화
	for (const auto& array : arrays)
	{
		vector<int> minVector = array;
		sort(minVector.begin(), minVector.end());
		minVectors.push_back(minVector);
		vectorIndexes.push_back(0);
	}

	if (minVectors.empty())
	{
		return;
	}

	for (int i = 0; i < minVectors.size(); ++i)
	{
		int index = vectorIndexes[i]++;
		minMergeHeap.push(HeapNode{ minVectors[i][index], i, index });
	}
}

HeapNode MergeHeap::GetMinData()
{
	HeapNode data = minMergeHeap.top();
	minMergeHeap.pop();

	// minVectors를 비교하여 가장 작은 다음 데이터를 찾아 삽입
	int vectorNum = CompareIndex();
	if (vectorNum < 0)
	{
		return HeapNode{ -1, -1, -1 };
	}

	int index = vectorIndexes[vectorNum]++;
	minMergeHeap.push(HeapNode{ minVectors[vectorNum][index], vectorNum, index });

	return data;
}

int MergeHeap::CompareIndex()
{
	int minValue = INT_MAX;
	int minIndex = -1;
	for (int i = 0; i < minVectors.size(); ++i)
	{
		if (vectorIndexes[i] >= minVectors[i].size())
		{
			continue;
		}

		if (minVectors[i][vectorIndexes[i]] < minValue)
		{
			minValue = minVectors[i][vectorIndexes[i]];
			minIndex = i;
		}
	}

	if (minIndex == -1)
	{
		return -1;
	}

	return minIndex;
}
