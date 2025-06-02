#pragma once
#include <iostream>
#include <vector>
using namespace std;
using uint = unsigned int;

class CuckooHashMap
{
public:
	CuckooHashMap(int n);

	vector<int>::iterator Lookup(int key);
	void Erase(int key);
	void Insert(int key);
	void Print();

private:
	void Insert_Impl(int key, int count, int table);

	int fHash(int key) const { return key % size; }
	int sHash(int key) const { return (key / size) % size; }

private:
	vector<int> fData;
	vector<int> sData;
	int size;
};