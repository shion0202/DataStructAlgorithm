#pragma once
#include "ChainingHashTable.h"

ChainingHashMap::ChainingHashMap(size_t n)
{
	data.resize(n);
}

void ChainingHashMap::Insert(uint value)
{
	// 크기로 나눈 값의 나머지를 Key로 사용
	int key = value % data.size();
	data[key].push_back(value);
	cout << value << " 삽입" << endl;
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
		cout << value << " 삭제" << endl;
	}
}
