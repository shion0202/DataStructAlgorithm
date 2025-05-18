#pragma once
#include "OrganizationTree.h"

OrganizationTree OrganizationTree::CreateTree(const string& pos)
{
	OrganizationTree tree;
	tree.root = new OrganizationNode{pos, nullptr, nullptr};
	return tree;
}

OrganizationNode* OrganizationTree::Find(OrganizationNode* root, const string& value)
{
	if (root == NULL)
	{
		return nullptr;
	}

	// 매개 변수로 주어진 root의 이름을 확인
	if (root->position == value)
	{
		return root;
	}

	// 왼쪽 서브 트리를 찾아보도록 하고, 만약 있다면 그 값을 반환
	OrganizationNode* firstFound = Find(root->first, value);
	if (firstFound != NULL)
	{
		return firstFound;
	}

	// 왼쪽 서브 트리에서 이름을 찾지 못 했다면 오른쪽 서브 트리를 확인하고 그 결과를 반환
	return Find(root->second, value);
}

bool OrganizationTree::AddSubordinate(const string& manager, const string& subordinate)
{
	OrganizationNode* managerNode = Find(root, manager);

	// 찾는 노드가 없을 경우
	if (!managerNode)
	{
		cout << "Can't find " << manager << "." << endl;
		return false;
	}

	// 노드를 찾았으나 왼쪽, 오른쪽 서브 트리가 모두 존재할 경우
	if (managerNode->first && managerNode->second)
	{
		cout << "Can't add " << subordinate << " under " << manager << "." << endl;
		return false;
	}

	// 노드를 찾았으며 서브 트리가 하나라도 비어있을 경우
	if (!managerNode->first)
	{
		managerNode->first = new OrganizationNode{ subordinate, nullptr, nullptr };
	}
	else
	{
		managerNode->second = new OrganizationNode{ subordinate, nullptr, nullptr };
	}

	cout << "Success to add " << subordinate << " under " << manager << "." << endl;
	return true;
}

void OrganizationTree::PreOrder(OrganizationNode* start)
{
	if (!start)
	{
		return;
	}

	// 현재 노드 -> 왼쪽 노드 -> 오른쪽 노드 순서
	cout << start->position << endl;
	PreOrder(start->first);
	PreOrder(start->second);
}

void OrganizationTree::InOrder(OrganizationNode* start)
{
	if (!start)
	{
		return;
	}

	// 왼쪽 노드 -> 현재 노드 -> 오른쪽 노드 순서
	InOrder(start->first);
	cout << start->position << endl;
	InOrder(start->second);
}

void OrganizationTree::PostOrder(OrganizationNode* start)
{
	if (!start)
	{
		return;
	}

	// 왼쪽 노드 -> 오른쪽 노드 -> 현재 노드 순서
	PostOrder(start->first);
	PostOrder(start->second);
	cout << start->position << endl;
}

void OrganizationTree::LevelOrder(OrganizationNode* start)
{
	if (!start)
	{
		return;
	}

	queue<OrganizationNode*> q;
	q.push(start);

	while (!q.empty())
	{
		int size = q.size();
		for (int i = 0; i < size; ++i)
		{
			OrganizationNode* current = q.front();
			q.pop();

			cout << current->position << "   ";

			if (current->first)
			{
				q.push(current->first);
			}
			if (current->second)
			{
				q.push(current->second);
			}
		}

		cout << endl;
	}

	cout << endl;
}
