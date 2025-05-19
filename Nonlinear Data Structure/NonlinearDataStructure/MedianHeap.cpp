#pragma once
#include "MedianHeap.h"

void MedianHeap::Insert(const int& data)
{
	if (maxHeap.size() == 0)
	{
		maxHeap.push(data);
		return;
	}

	if (maxHeap.size() == minHeap.size())
	{
		if (data <= Get())
		{
			maxHeap.push(data);
		}
		else
		{
			minHeap.push(data);
		}

		return;
	}

	if (maxHeap.size() < minHeap.size())
	{
		if (data > Get())
		{
			maxHeap.push(minHeap.top());
			minHeap.pop();
			minHeap.push(data);
		}
		else
		{
			maxHeap.push(data);
		}

		return;
	}

	if (data < Get())
	{
		minHeap.push(maxHeap.top());
		maxHeap.pop();
		maxHeap.push(data);
	}
	else
	{
		minHeap.push(data);
	}
}

double MedianHeap::Get()
{
	if (maxHeap.size() > minHeap.size())
	{
		return maxHeap.top();
	}
	else if (maxHeap.size() < minHeap.size())
	{
		return minHeap.top();
	}
	else
	{
		return (maxHeap.top() + minHeap.top()) * 0.5f;
	}
}

void MyMedianHeap::Insert(const int& value)
{
	// 최대 힙이 비어있거나 두 힙의 크기가 같을 경우 최대 힙에 삽입
	// 그렇지 않을 경우 최소 힙에 삽입

	if (maxHeap.size() == minHeap.size())
	{
		maxHeap.push(value);
	}
	else
	{
		minHeap.push(value);
	}

	// 최소 힙이 비어있지 않다면 최소 힙과 최대 힙의 top을 비교
	// 이 때 최대 힙의 값이 최소 힙의 값보다 클 경우 두 값을 교환

	if (minHeap.empty())
	{
		return;
	}

	if (maxHeap.top() > minHeap.top())
	{
		int temp = maxHeap.top();
		maxHeap.pop();
		maxHeap.push(minHeap.top());
		minHeap.pop();
		minHeap.push(temp);
	}
}

float MyMedianHeap::GetMedian()
{
	// 두 힙의 크기가 같을 경우, 두 개의 값이 중앙에 위치하므로 평균을 반환
	// 한 쪽 힙의 크기가 클 경우, 해당 힙의 top 값이 중앙값

	if (maxHeap.size() > minHeap.size())
	{
		return (float)maxHeap.top();
	}
	else if (maxHeap.size() < minHeap.size())
	{
		return (float)minHeap.top();
	}
	else
	{
		return (maxHeap.top() + minHeap.top()) * 0.5f;
	}
}
