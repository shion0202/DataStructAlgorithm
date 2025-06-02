#pragma once
#include "RedBlackTree.h"

MyRBTree::MyRBTree()
{
	NIL = new RBNode{ -1, false, nullptr, nullptr, nullptr };
	root = NIL;
}

MyRBTree::~MyRBTree()
{
	delete NIL;
}

RBNode* MyRBTree::Find(const int& value)
{
	return Find_Implement(root, value);
}

void MyRBTree::Insert(const int& value)
{
	if (!root || root == NIL)
		root = new RBNode{ value, false, NIL, NIL, nullptr };
	else
		Insert_Implement(root, value);

	// PrintTree();
}

void MyRBTree::DeleteNode(const int& value)
{
	Delete_Implement(value);
	// PrintTree();
}

void MyRBTree::InOrder()
{
	InOrder_Implement(root);
	cout << endl << endl;
}

void MyRBTree::PrintTree()
{
	PrintTree_Implement(root);
	cout << endl;
}

RBNode* MyRBTree::Find_Implement(RBNode* current, const int& value)
{
	if (!current || current == NIL)
		return nullptr;

	if (current->data == value)
	{
		cout << "Success to find " << value << "." << endl;
		return current;
	}

	if (value < current->data)
		return Find_Implement(current->left, value);
	else
		return Find_Implement(current->right, value);
}

void MyRBTree::Insert_Implement(RBNode* current, const int& value)
{
	if (value < current->data)
	{
		if (current->left == NIL)
		{
			current->left = new RBNode{ value, true, NIL, NIL, current };
			RebalanceAfterInsert(current->left);
		}
		else
		{
			Insert_Implement(current->left, value);
		}
	}
	else
	{
		if (current->right == NIL)
		{
			current->right = new RBNode{ value, true, NIL, NIL, current };
			RebalanceAfterInsert(current->right);
		}
		else
		{
			Insert_Implement(current->right, value);
		}
	}
}

void MyRBTree::Delete_Implement(const int& value)
{
	RBNode* current = root;

	while (current && current->data != value && current != NIL)
	{
		if (value < current->data)
			current = current->left;
		else
			current = current->right;
	}

	if (!current || current == NIL)
		return;

	bool isOriginalRed = current->isRed;
	RBNode* newNode = nullptr;
	RBNode* successor = nullptr;

	// 자식 노드가 없거나 하나인 경우
	if (current->left == NIL)
	{
		// current 자리를 newNode로 대체, 즉 current의 부모와 newNode를 부모-자식 관계로 연결
		newNode = current->right;
		Transplant(current, newNode);
	}
	else if (current->right == NIL)
	{
		newNode = current->left;
		Transplant(current, newNode);
	}
	else
	{
		// 자식 노드가 2개인 경우, 후속자 노드를 찾아서 교체
		successor = GetSuccessor(current);
		isOriginalRed = successor->isRed;
		newNode = successor->right;

		// 후속자 노드가 현재 노드의 오른쪽 자식이 아니라 후손 노드인 경우, 후속자 노드를 그의 자식 노드로 교체
		if (successor->parent != current)
		{
			Transplant(successor, successor->right);
			successor->right = current->right;
			successor->right->parent = successor;
		}
		else
		{
			newNode->parent = successor;
		}

		// 현재 노드와 후속자 노드를 교체
		Transplant(current, successor);
		successor->left = current->left;
		successor->left->parent = successor;
		successor->isRed = current->isRed;
	}

	delete current;

	if (!isOriginalRed)
		RebalanceAfterDelete(newNode);
}

void MyRBTree::InOrder_Implement(RBNode* start)
{
	if (!start || start == NIL)
		return;

	InOrder_Implement(start->left);
	cout << start->data << " ";
	InOrder_Implement(start->right);
}

void MyRBTree::PrintTree_Implement(RBNode* start, string prefix, bool isRight)
{
	if (start && start != NIL)
	{
		cout << prefix;
		cout << (isRight ? "R - " : "L - ");
		prefix += (isRight ? "     " : "|    ");

		string color = start->isRed ? "R" : "B";
		cout << color << start->data << endl;

		PrintTree_Implement(start->left, prefix, false);
		PrintTree_Implement(start->right, prefix, true);
	}
}

void MyRBTree::RebalanceAfterInsert(RBNode* node)
{
	// 삽입 후 트리의 균형이 맞는지 확인
	// 4번째 삽입 이후, 즉 최소한 조상 노드가 존재하는 상태에서 Double Red 문제가 발생
	while (node->parent && node->parent->isRed)
	{
		RBNode* grandParent = GetGrandParent(node);
		RBNode* uncle = GetUncleNode(node);

		if (node->parent == grandParent->left)
		{
			if (uncle && uncle->isRed)
			{
				// 삼촌 노드도 Red일 경우 Recoloring
				node->parent->isRed = false;
				uncle->isRed = false;
				grandParent->isRed = true;

				// 조부모 노드로 이동하여 Double Red가 다시 발생했는지 확인
				node = grandParent;
			}
			else
			{
				// 삼촌 노드가 Black일 경우 Restructuring
				if (node == node->parent->right)
				{
					// 조부모 노드의 왼쪽에 있는 부모 노드의 오른쪽 노드일 경우, 부모 노드를 기준으로 회전
					// 이 경우 새 부모 노드(기존 자식 노드)의 왼쪽에 기존 부모 노드가 위치하며, Double Red가 발생한다.
					node = node->parent;
					RotateLeft(node);
				}

				// 조부모 노드의 왼쪽에 있는 부모 노드의 왼쪽 노드일 경우, 조부모를 기준으로 회전
				node->parent->isRed = !node->parent->isRed;
				grandParent->isRed = !grandParent->isRed;
				RotateRight(grandParent);
			}
		}
		else
		{
			if (uncle && uncle->isRed)
			{
				node->parent->isRed = false;
				uncle->isRed = false;
				grandParent->isRed = true;

				node = grandParent;
			}
			else
			{
				if (node == node->parent->left)
				{
					// 조부모 노드의 오른쪽에 있는 부모 노드의 왼쪽 노드일 경우, 부모 노드를 기준으로 회전
					// 이 경우 새 부모 노드(기존 자식 노드)의 오른쪽에 기존 부모 노드가 위치하며, Double Red가 발생한다.
					node = node->parent;
					RotateRight(node);
				}

				// 조부모 노드의 오른쪽 있는 부모 노드의 오른쪽 노드일 경우, 조부모를 기준으로 회전
				node->parent->isRed = !node->parent->isRed;
				grandParent->isRed = !grandParent->isRed;
				RotateLeft(grandParent);
			}
		}
	}

	// 조부모 노드가 root일 경우 while문이 종료되므로, root 노드의 색을 한 번 더 확인
	root->isRed = false;
}

void MyRBTree::RebalanceAfterDelete(RBNode* node)
{
	RBNode* sibling;

	// Node가 root이거나 Red인 경우, 더 이상 조정이 필요하지 않다.
	while (node != root && !node->isRed)
	{
		if (node == node->parent->left)
			sibling = node->parent->right;
		else
			sibling = node->parent->left;

		// Case 1. 형제 노드가 Red인 경우
		if (sibling->isRed)
		{
			// 부모와 형제의 색을 변경
			sibling->isRed = false;
			node->parent->isRed = true;

			// 부모를 기준으로 회전
			if (node == node->parent->left)
				RotateLeft(node->parent);
			else
				RotateRight(node->parent);

			// 회전 후 형제 노드를 다시 가져오며, Case 2~4로 이동
			if (node == node->parent->left)
				sibling = node->parent->right;
			else
				sibling = node->parent->left;
		}

		// sibling이 NIL일 경우 조치 필요

		// Case 2. 형제와 형제의 자식 노드가 모두 Black인 경우
		if (!sibling->left->isRed && !sibling->right->isRed)
		{
			// 형제 노드의 색을 Red로 변경하여 Black Height를 유지하고, 현재 문제를 부모 노드에 위임
			sibling->isRed = true;
			node = node->parent;
		}
		else
		{
			// Case 3. 형제 노드가 Black이고, 형제의 안쪽 자식 노드가 Red인 경우
			if (node == node->parent->left && !sibling->right->isRed)
			{
				sibling->isRed = true;
				sibling->left->isRed = false;
				RotateRight(sibling);
				sibling = node->parent->right;
			}
			else if (node == node->parent->right && !sibling->left->isRed)
			{
				sibling->isRed = true;
				sibling->right->isRed = false;
				RotateLeft(sibling);
				sibling = node->parent->left;
			}

			// Case 4. 형제 노드가 Black이고, 형제의 바깥쪽 자식 노드가 Red인 경우
			sibling->isRed = node->parent->isRed;
			node->parent->isRed = false;

			if (node == node->parent->left)
			{
				sibling->right->isRed = false;
				RotateLeft(node->parent);
			}
			else
			{
				sibling->left->isRed = false;
				RotateRight(node->parent);
			}

			node = root;
		}
	}

	node->isRed = false;
	root->isRed = false;
	NIL->isRed = false;
	NIL->parent = nullptr;
}

RBNode* MyRBTree::GetSuccessor(RBNode* start)
{
	if (!start || !start->right || start == NIL || start->right == NIL)
		return nullptr;

	RBNode* current = start->right;
	while (current->left && current->left != NIL)
		current = current->left;

	return current;
}

RBNode* MyRBTree::GetGrandParent(RBNode* node)
{
	if (!node || !node->parent)
		return nullptr;

	return node->parent->parent;
}

RBNode* MyRBTree::GetUncleNode(RBNode* node)
{
	RBNode* grandParent = GetGrandParent(node);
	if (!grandParent)
		return nullptr;

	if (grandParent->left == node->parent)
		return grandParent->right;
	else
		return grandParent->left;
}

RBNode* MyRBTree::GetSibling(RBNode* node)
{
	if (!node || !node->parent)
		return nullptr;

	if (node == node->parent->left)
		return node->parent->right;
	else
		return node->parent->left;
}

void MyRBTree::RotateLeft(RBNode* node)
{
	RBNode* temp = node->right;

	node->right = temp->left;
	if (temp->left && temp->left != NIL)
		temp->left->parent = node;

	temp->parent = node->parent;
	if (node == root)
		root = temp;
	else if (node == node->parent->left)
		node->parent->left = temp;
	else
		node->parent->right = temp;

	temp->left = node;
	node->parent = temp;
}

void MyRBTree::RotateRight(RBNode* node)
{
	RBNode* temp = node->left;

	node->left = temp->right;
	if (temp->right && temp->right != NIL)
		temp->right->parent = node;

	temp->parent = node->parent;
	if (node == root)
		root = temp;
	else if (node == node->parent->left)
		node->parent->left = temp;
	else
		node->parent->right = temp;

	temp->right = node;
	node->parent = temp;
}

void MyRBTree::Transplant(RBNode* current, RBNode* newNode)
{
	// 교체된 current의 삭제는 Delete_Implement에서 처리

	if (!current->parent)
		root = newNode;
	else if (current == current->parent->left)
		current->parent->left = newNode;
	else
		current->parent->right = newNode;

	newNode->parent = current->parent;
}
