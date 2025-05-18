#pragma once
#include <iostream>
using namespace std;

struct BSTNode
{
	int data;
	BSTNode* left;
	BSTNode* right;
};

class MyBST
{
public:
	BSTNode* Find(const int& value);
	void Insert(const int& value);
	void DeleteNode(const int& value);

	void InOrder();

	// 본인보다 큰 값 중 가장 작은, 후손 노드를 찾는 함수
	BSTNode* Successor(BSTNode* start);

private:
	BSTNode* Find_Implement(BSTNode* current, const int& value);
	void Insert_Implement(BSTNode* current, const int& value);
	void InOrder_Implement(BSTNode* start);
	BSTNode* Delete_Implement(BSTNode* start, const int& value);

public:
	BSTNode* root = nullptr;
};
