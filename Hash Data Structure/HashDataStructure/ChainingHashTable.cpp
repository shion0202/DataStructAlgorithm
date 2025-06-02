#pragma once
#include "ChainingHashTable.h"

ChainingHashMap::ChainingHashMap(size_t n)
{
	data.resize(n);
}

void ChainingHashMap::Insert(uint value)
{
	// ũ��� ���� ���� �������� Key�� ���
	int key = value % data.size();
	data[key].push_back(value);
	cout << value << " ����" << endl;
}

bool ChainingHashMap::Find(uint value)
{
	int key = value % data.size();
	return find(data[key].begin(), data[key].end(), value) != data[key].end();
}

void ChainingHashMap::Erase(uint value)
{
	if (Find(value))
	{
		int key = value % data.size();
		data[key].remove(value);
		cout << value << " ����" << endl;
	}
}
