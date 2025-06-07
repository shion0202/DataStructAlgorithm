#pragma once
#include <iostream>
using namespace std;

struct RBNode
{
	int data;
	bool isRed;

	RBNode* left;
	RBNode* right;
	RBNode* parent;
};

class RBTree
{
public:
	RBTree();
	~RBTree();

	RBNode* Find(const int& value);
	void Insert(const int& value);
	void DeleteNode(const int& value);

	void InOrder();
	void PrintTree();

	void Clear();

private:
	RBNode* Find_Implement(RBNode* current, const int& value);
	void Insert_Implement(RBNode* current, const int& value);
	void Delete_Implement(const int& value);
	void InOrder_Implement(RBNode* start);
	void PrintTree_Implement(RBNode* start, string prefix = "", bool isRight = true);
	void Clear_Implement(RBNode* start);

	void RebalanceAfterInsert(RBNode* node);
	void RebalanceAfterDelete(RBNode* node);
	void RotateLeft(RBNode* node);
	void RotateRight(RBNode* node);
	void Transplant(RBNode* current, RBNode* newNode);

	RBNode* GetSuccessor(RBNode* start);
	RBNode* GetGrandParent(RBNode* node);
	RBNode* GetUncleNode(RBNode* node);
	RBNode* GetSibling(RBNode* node);

public:
	RBNode* root = nullptr;
	RBNode* NIL;
};
