#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
using uint = unsigned int;

class ChainingHashMap
{
public:
	ChainingHashMap(size_t n);

	void Insert(uint value);
	bool Find(uint value);
	void Erase(uint value);

private:
	vector<list<int>> data;
};