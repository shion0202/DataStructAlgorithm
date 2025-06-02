#pragma once
#include "SimpleDictionary.h"

MyHashMap::MyHashMap(size_t n)
{
	data = vector<int>(n, -1);
}

void MyHashMap::Insert(uint value)
{
	int n = data.size();
	data[value % n] = value;
	cout << value << " »ðÀÔ" << endl;
}

bool MyHashMap::Find(uint value)
{
	int n = data.size();
	return (data[value % n] == value);
}

void MyHashMap::Erase(uint value)
{
	
	if (Find(value))
	{
		int n = data.size();
		data[value % n] = -1;
		cout << value << " »èÁ¦" << endl;
	}
}
