#pragma once
#include <iostream>
#include <vector>
using namespace std;
using uint = unsigned int;

class MyHashMap
{
public:
	MyHashMap(size_t n);

	void Insert(uint value);
	bool Find(uint value);
	void Erase(uint value);

private:
	vector<int> data;
};