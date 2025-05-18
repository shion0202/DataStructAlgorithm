#pragma once
#include <iostream>
#include <queue>
using namespace std;

// 회사의 조직도와 유사한 형태의 트리 구현

struct OrganizationNode
{
	string position;
	OrganizationNode* first;
	OrganizationNode* second;
};

class OrganizationTree
{
public:
	// 루트 노드(새로운 트리)를 만드는 정적 함수
	static OrganizationTree CreateTree(const string& pos);

	// 특정 이름(value)를 가진 노드를 찾는 함수
	static OrganizationNode* Find(OrganizationNode* root, const string& value);

	// 특정 이름(manager)를 가진 노드의 서브 트리로 subordinate 노드를 추가하는 함수
	bool AddSubordinate(const string& manager, const string& subordinate);

	// 전위, 중위, 후위, 레벨 순서 순회
	static void PreOrder(OrganizationNode* start);
	static void InOrder(OrganizationNode* start);
	static void PostOrder(OrganizationNode* start);
	static void LevelOrder(OrganizationNode* start);

public:
	OrganizationNode* root;
};
