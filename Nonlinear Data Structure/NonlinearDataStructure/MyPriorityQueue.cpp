#pragma once
#include "MyPriorityQueue.h"

void MyPrioirtyQueue::Push(const int& data)
{
	if (Empty())
	{
		root = new HeapNode{ data, NULL, NULL, NULL };
		size = 1;
		return;
	}

	// 삽입 후 완전 이진 트리를 유지할 수 있는 노드 위치 검색
	HeapNode* insertedNode = FindInsertedNode();
	HeapNode* currentNode = NULL;
	if (!insertedNode->left)
	{
		insertedNode->left = new HeapNode{ data, insertedNode, NULL, NULL };
		currentNode = insertedNode->left;
	}
	else
	{
		insertedNode->right = new HeapNode{ data, insertedNode, NULL, NULL };
		currentNode = insertedNode->right;
	}
	size++;

	// 리프 노드로부터 부모 노드를 따라 올라가면서, 자신의 값이 더 크다면 값을 교환하면서 트리를 정리
	while (currentNode->parent)
	{
		if (currentNode->data < currentNode->parent->data)
		{
			break;
		}

		SwapNode(currentNode, currentNode->parent);
		currentNode = currentNode->parent;
	}
}

void MyPrioirtyQueue::Pop()
{
	if (Empty())
	{
		return;
	}

	if (Size() == 1)
	{
		delete root;
		root = NULL;
		size = 0;
		return;
	}

	// 루트 노드 삭제, 즉 루트 노드의 값을 마지막 리프 노드의 값과 교환하고 리프 노드를 삭제
	HeapNode* lastLeafNode = FindLastLeafNode();

	root->data = lastLeafNode->data;
	
	if (lastLeafNode->parent->left == lastLeafNode)
	{
		lastLeafNode->parent->left = NULL;
	}
	else if (lastLeafNode->parent->right == lastLeafNode)
	{
		lastLeafNode->parent->right = NULL;
	}

	delete lastLeafNode;
	lastLeafNode = NULL;
	size--;

	// 자신의 값과 자식 노드의 값을 비교하여 더 큰 값이 있다면 교환하며 트리를 정리
	HeapNode* currentNode = root;
	while (currentNode->left)
	{
		if (currentNode->right)
		{
			if (currentNode->data >= currentNode->left->data && currentNode->data >= currentNode->right->data)
			{
				break;
			}

			if (currentNode->left->data > currentNode->right->data)
			{
				SwapNode(currentNode, currentNode->left);
				currentNode = currentNode->left;
			}
			else
			{
				SwapNode(currentNode, currentNode->right);
				currentNode = currentNode->right;
			}
		}
		else
		{
			if (currentNode->data >= currentNode->left->data)
			{
				break;
			}

			SwapNode(currentNode, currentNode->left);
			currentNode = currentNode->left;
		}
	}
}

const int& MyPrioirtyQueue::Top()
{
	return root->data;
}

int MyPrioirtyQueue::Size()
{
	return size;
}

bool MyPrioirtyQueue::Empty()
{
	return size == 0 ? true : false;
}

HeapNode* MyPrioirtyQueue::FindInsertedNode()
{
	queue<HeapNode*> q;
	q.push(root);

	// 레벨 순회를 통해 삽입할 수 있는 노드를 반환
	while (!q.empty())
	{
		for (int i = 0; i < q.size(); ++i)
		{
			HeapNode* currentNode = q.front();
			q.pop();

			if (!currentNode->left || !currentNode->right)
			{
				return currentNode;
			}

			q.push(currentNode->left);
			q.push(currentNode->right);
		}
	}

	// root가 없을 경우 NULL을 반환
	return NULL;
}

HeapNode* MyPrioirtyQueue::FindLastLeafNode()
{
	HeapNode* currentNode = NULL;
	queue<HeapNode*> q;
	q.push(root);

	// 레벨 순회를 통해 마지막 리프 노드 검색
	while (!q.empty())
	{
		for (int i = 0; i < q.size(); ++i)
		{
			currentNode = q.front();
			q.pop();

			if (currentNode->left)
			{
				q.push(currentNode->left);
			}
			if (currentNode->right)
			{
				q.push(currentNode->right);
			}
		}
	}

	return currentNode;
}

void MyPrioirtyQueue::SwapNode(HeapNode* left, HeapNode* right)
{
	int temp = left->data;
	left->data = right->data;
	right->data = temp;
}
