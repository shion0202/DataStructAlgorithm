#pragma once
#include <iostream>
#include <queue>
using namespace std;

// ȸ���� �������� ������ ������ Ʈ�� ����

struct OrganizationNode
{
	string position;
	OrganizationNode* first;
	OrganizationNode* second;
};

class OrganizationTree
{
public:
	// ��Ʈ ���(���ο� Ʈ��)�� ����� ���� �Լ�
	static OrganizationTree CreateTree(const string& pos);

	// Ư�� �̸�(value)�� ���� ��带 ã�� �Լ�
	static OrganizationNode* Find(OrganizationNode* root, const string& value);

	// Ư�� �̸�(manager)�� ���� ����� ���� Ʈ���� subordinate ��带 �߰��ϴ� �Լ�
	bool AddSubordinate(const string& manager, const string& subordinate);

	// ����, ����, ����, ���� ���� ��ȸ
	static void PreOrder(OrganizationNode* start);
	static void InOrder(OrganizationNode* start);
	static void PostOrder(OrganizationNode* start);
	static void LevelOrder(OrganizationNode* start);

public:
	OrganizationNode* root;
};
