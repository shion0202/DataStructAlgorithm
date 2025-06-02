#pragma once
#include "BloomFilter.h"

BloomFilter::BloomFilter(int n) : nBits(n)
{
	data = vector<bool>(nBits, false);
}

void BloomFilter::Lookup(int key)
{
	bool result = data[Hash(0, key)] & data[Hash(1, key)] & data[Hash(2, key)];
	if (result)
	{
		cout << "Key " << key << " is possibly in the Bloom Filter." << endl;
	}
	else
	{
		cout << "Key " << key << " is definitely not in the Bloom Filter." << endl;
	}
}

void BloomFilter::Insert(int key)
{
	data[Hash(0, key)] = true;
	data[Hash(1, key)] = true;
	data[Hash(2, key)] = true;
	cout << "Key " << key << " inserted into the Bloom Filter: ";

	for (auto ele : data)
	{
		cout << ele << " ";
	}
	cout << endl;
}

int BloomFilter::Hash(int num, int key)
{
	switch (num)
	{
	case 0: return key % nBits;
	case 1: return (key / 7) % nBits;
	case 2: return (key / 11) % nBits;
	}

	return 0;
}
