#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 블룸 필터를 사용하여 이메일 중복 검사를 구현하는 문제

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
