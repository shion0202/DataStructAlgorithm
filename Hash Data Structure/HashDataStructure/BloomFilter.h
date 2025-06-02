#pragma once
#include <iostream>
#include <vector>
using namespace std;

class BloomFilter
{
public:
	BloomFilter(int n);

	void Lookup(int key);
	void Insert(int key);

private:
	int Hash(int num, int key);

private:
	vector<bool> data;
	int nBits;
};