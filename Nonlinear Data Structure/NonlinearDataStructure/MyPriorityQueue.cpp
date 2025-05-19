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

	// ���� �� ���� ���� Ʈ���� ������ �� �ִ� ��� ��ġ �˻�
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

	// ���� ���κ��� �θ� ��带 ���� �ö󰡸鼭, �ڽ��� ���� �� ũ�ٸ� ���� ��ȯ�ϸ鼭 Ʈ���� ����
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

	// ��Ʈ ��� ����, �� ��Ʈ ����� ���� ������ ���� ����� ���� ��ȯ�ϰ� ���� ��带 ����
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

	// �ڽ��� ���� �ڽ� ����� ���� ���Ͽ� �� ū ���� �ִٸ� ��ȯ�ϸ� Ʈ���� ����
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

	// ���� ��ȸ�� ���� ������ �� �ִ� ��带 ��ȯ
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

	// root�� ���� ��� NULL�� ��ȯ
	return NULL;
}

HeapNode* MyPrioirtyQueue::FindLastLeafNode()
{
	HeapNode* currentNode = NULL;
	queue<HeapNode*> q;
	q.push(root);

	// ���� ��ȸ�� ���� ������ ���� ��� �˻�
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
