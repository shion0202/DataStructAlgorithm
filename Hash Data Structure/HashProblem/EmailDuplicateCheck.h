#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ��� ���͸� ����Ͽ� �̸��� �ߺ� �˻縦 �����ϴ� ����

class BloomFilter
{
public:
	BloomFilter(int size);

	void Lookup(string key);
	void Insert(string key);

private:
	unsigned char* Hash(string key);

private:
	vector<bool> data;
	int nBits;
};
