#include "TreeSet.h"

TreeSet::TreeSet()
{
	
}

void TreeSet::insert(const int& value)
{
	treeSet.Insert(value);
}

RBNode* TreeSet::find(const int& value)
{
	return treeSet.Find(value);
}

void TreeSet::erase(const int& value)
{
	treeSet.DeleteNode(value);
}
