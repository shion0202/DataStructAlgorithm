#pragma once
#include "BinarySearchTree.h"

BSTNode* MyBST::Find(const int& value)
{
	return Find_Implement(root, value);
}

void MyBST::Insert(const int& value)
{
	if (!root)
	{
		root = new BSTNode{ value, NULL, NULL };
	}
	else
	{
		Insert_Implement(root, value);
	}
}

void MyBST::DeleteNode(const int& value)
{
	root = Delete_Implement(root, value);
}

void MyBST::InOrder()
{
	InOrder_Implement(root);
}

BSTNode* MyBST::Successor(BSTNode* start)
{
	BSTNode* current = start->right;
	
	while (current && current->left)
	{
		current = current->left;
	}
	return current;
}

BSTNode* MyBST::Find_Implement(BSTNode* current, const int& value)
{
	if (!current)
	{
		cout << endl;
		return nullptr;
	}

	if (current->data == value)
	{
		cout << "Success to find " << value << "."  << endl;
		return current;
	}

	if (value < current->data)
	{
		cout << "Move from " << current->data << " to left." << endl;
		return Find_Implement(current->left, value);
	}
	else
	{
		cout << "Move from " << current->data << " to right." << endl;
		return Find_Implement(current->right, value);
	}
}

void MyBST::Insert_Implement(BSTNode* current, const int& value)
{
	if (value < current->data)
	{
		if (!current->left)
		{
			current->left = new BSTNode{ value, NULL, NULL };
		}
		else
		{
			Insert_Implement(current->left, value);
		}
	}
	else if (value > current->data)
	{
		if (!current->right)
		{
			current->right = new BSTNode{ value, NULL, NULL };
		}
		else
		{
			Insert_Implement(current->right, value);
		}
	}
	else
	{
		cout << "동일한 값이 이미 존재합니다." << endl;
	}
}

void MyBST::InOrder_Implement(BSTNode* start)
{
	if (!start)
	{
		return;
	}

	InOrder_Implement(start->left);
	cout << start->data << " ";
	InOrder_Implement(start->right);
}

BSTNode* MyBST::Delete_Implement(BSTNode* start, const int& value)
{
	if (!start)
	{
		return NULL;
	}

	if (value < start->data)
	{
		start->left = Delete_Implement(start->left, value);
	}
	else if (value > start->data)
	{
		start->right = Delete_Implement(start->right, value);
	}
	else
	{
		if (!start->left)
		{
			BSTNode* temp = start->right;
			delete start;
			return temp;
		}

		if (!start->right)
		{
			BSTNode* temp = start->left;
			delete start;
			return temp;
		}

		BSTNode* successorNode = Successor(start);
		start->data = successorNode->data;
		
		start->right = Delete_Implement(start->right, successorNode->data);
	}

	return start;
}
