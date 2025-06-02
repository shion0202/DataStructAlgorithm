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

	// �ڽ� ��尡 ���ų� �ϳ��� ���
	if (current->left == NIL)
	{
		// current �ڸ��� newNode�� ��ü, �� current�� �θ�� newNode�� �θ�-�ڽ� ����� ����
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
		// �ڽ� ��尡 2���� ���, �ļ��� ��带 ã�Ƽ� ��ü
		successor = GetSuccessor(current);
		isOriginalRed = successor->isRed;
		newNode = successor->right;

		// �ļ��� ��尡 ���� ����� ������ �ڽ��� �ƴ϶� �ļ� ����� ���, �ļ��� ��带 ���� �ڽ� ���� ��ü
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

		// ���� ���� �ļ��� ��带 ��ü
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
	// ���� �� Ʈ���� ������ �´��� Ȯ��
	// 4��° ���� ����, �� �ּ��� ���� ��尡 �����ϴ� ���¿��� Double Red ������ �߻�
	while (node->parent && node->parent->isRed)
	{
		RBNode* grandParent = GetGrandParent(node);
		RBNode* uncle = GetUncleNode(node);

		if (node->parent == grandParent->left)
		{
			if (uncle && uncle->isRed)
			{
				// ���� ��嵵 Red�� ��� Recoloring
				node->parent->isRed = false;
				uncle->isRed = false;
				grandParent->isRed = true;

				// ���θ� ���� �̵��Ͽ� Double Red�� �ٽ� �߻��ߴ��� Ȯ��
				node = grandParent;
			}
			else
			{
				// ���� ��尡 Black�� ��� Restructuring
				if (node == node->parent->right)
				{
					// ���θ� ����� ���ʿ� �ִ� �θ� ����� ������ ����� ���, �θ� ��带 �������� ȸ��
					// �� ��� �� �θ� ���(���� �ڽ� ���)�� ���ʿ� ���� �θ� ��尡 ��ġ�ϸ�, Double Red�� �߻��Ѵ�.
					node = node->parent;
					RotateLeft(node);
				}

				// ���θ� ����� ���ʿ� �ִ� �θ� ����� ���� ����� ���, ���θ� �������� ȸ��
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
					// ���θ� ����� �����ʿ� �ִ� �θ� ����� ���� ����� ���, �θ� ��带 �������� ȸ��
					// �� ��� �� �θ� ���(���� �ڽ� ���)�� �����ʿ� ���� �θ� ��尡 ��ġ�ϸ�, Double Red�� �߻��Ѵ�.
					node = node->parent;
					RotateRight(node);
				}

				// ���θ� ����� ������ �ִ� �θ� ����� ������ ����� ���, ���θ� �������� ȸ��
				node->parent->isRed = !node->parent->isRed;
				grandParent->isRed = !grandParent->isRed;
				RotateLeft(grandParent);
			}
		}
	}

	// ���θ� ��尡 root�� ��� while���� ����ǹǷ�, root ����� ���� �� �� �� Ȯ��
	root->isRed = false;
}

void MyRBTree::RebalanceAfterDelete(RBNode* node)
{
	RBNode* sibling;

	// Node�� root�̰ų� Red�� ���, �� �̻� ������ �ʿ����� �ʴ�.
	while (node != root && !node->isRed)
	{
		if (node == node->parent->left)
			sibling = node->parent->right;
		else
			sibling = node->parent->left;

		// Case 1. ���� ��尡 Red�� ���
		if (sibling->isRed)
		{
			// �θ�� ������ ���� ����
			sibling->isRed = false;
			node->parent->isRed = true;

			// �θ� �������� ȸ��
			if (node == node->parent->left)
				RotateLeft(node->parent);
			else
				RotateRight(node->parent);

			// ȸ�� �� ���� ��带 �ٽ� ��������, Case 2~4�� �̵�
			if (node == node->parent->left)
				sibling = node->parent->right;
			else
				sibling = node->parent->left;
		}

		// sibling�� NIL�� ��� ��ġ �ʿ�

		// Case 2. ������ ������ �ڽ� ��尡 ��� Black�� ���
		if (!sibling->left->isRed && !sibling->right->isRed)
		{
			// ���� ����� ���� Red�� �����Ͽ� Black Height�� �����ϰ�, ���� ������ �θ� ��忡 ����
			sibling->isRed = true;
			node = node->parent;
		}
		else
		{
			// Case 3. ���� ��尡 Black�̰�, ������ ���� �ڽ� ��尡 Red�� ���
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

			// Case 4. ���� ��尡 Black�̰�, ������ �ٱ��� �ڽ� ��尡 Red�� ���
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
	// ��ü�� current�� ������ Delete_Implement���� ó��

	if (!current->parent)
		root = newNode;
	else if (current == current->parent->left)
		current->parent->left = newNode;
	else
		current->parent->right = newNode;

	newNode->parent = current->parent;
}
