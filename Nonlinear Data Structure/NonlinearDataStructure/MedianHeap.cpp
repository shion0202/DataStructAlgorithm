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
	// �ִ� ���� ����ְų� �� ���� ũ�Ⱑ ���� ��� �ִ� ���� ����
	// �׷��� ���� ��� �ּ� ���� ����

	if (maxHeap.size() == minHeap.size())
	{
		maxHeap.push(value);
	}
	else
	{
		minHeap.push(value);
	}

	// �ּ� ���� ������� �ʴٸ� �ּ� ���� �ִ� ���� top�� ��
	// �� �� �ִ� ���� ���� �ּ� ���� ������ Ŭ ��� �� ���� ��ȯ

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
	// �� ���� ũ�Ⱑ ���� ���, �� ���� ���� �߾ӿ� ��ġ�ϹǷ� ����� ��ȯ
	// �� �� ���� ũ�Ⱑ Ŭ ���, �ش� ���� top ���� �߾Ӱ�

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
