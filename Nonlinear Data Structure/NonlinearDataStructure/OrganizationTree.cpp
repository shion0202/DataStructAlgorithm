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

	// �Ű� ������ �־��� root�� �̸��� Ȯ��
	if (root->position == value)
	{
		return root;
	}

	// ���� ���� Ʈ���� ã�ƺ����� �ϰ�, ���� �ִٸ� �� ���� ��ȯ
	OrganizationNode* firstFound = Find(root->first, value);
	if (firstFound != NULL)
	{
		return firstFound;
	}

	// ���� ���� Ʈ������ �̸��� ã�� �� �ߴٸ� ������ ���� Ʈ���� Ȯ���ϰ� �� ����� ��ȯ
	return Find(root->second, value);
}

bool OrganizationTree::AddSubordinate(const string& manager, const string& subordinate)
{
	OrganizationNode* managerNode = Find(root, manager);

	// ã�� ��尡 ���� ���
	if (!managerNode)
	{
		cout << "Can't find " << manager << "." << endl;
		return false;
	}

	// ��带 ã������ ����, ������ ���� Ʈ���� ��� ������ ���
	if (managerNode->first && managerNode->second)
	{
		cout << "Can't add " << subordinate << " under " << manager << "." << endl;
		return false;
	}

	// ��带 ã������ ���� Ʈ���� �ϳ��� ������� ���
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

	// ���� ��� -> ���� ��� -> ������ ��� ����
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

	// ���� ��� -> ���� ��� -> ������ ��� ����
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

	// ���� ��� -> ������ ��� -> ���� ��� ����
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
