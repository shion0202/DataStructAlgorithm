#pragma once
#include "RedBlackTree.h"

class TreeSet
{
public:
	TreeSet();

	void insert(const int& value);
	RBNode* find(const int& value);
	void erase(const int& value);

	void clear() { treeSet.Clear(); }
	bool empty() { return !treeSet.root || treeSet.root == treeSet.NIL; }

private:
	RBTree treeSet;
};