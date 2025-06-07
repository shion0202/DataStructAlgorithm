#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <openssl/sha.h>
using namespace std;

template <typename K>
vector<unsigned char> HashKey(const K& key)
{
	if constexpr (is_arithmetic_v<K>)
	{
		// 기본 타입일 경우
		vector<unsigned char> bytes(sizeof(K));
		memcpy(bytes.data(), &key, sizeof(K));
		return bytes;
	}
	else
	{
		// 사용자 정의 타입일 경우
		static_assert(sizeof(K) != 0, "Type not supported.");
		return vector<unsigned char>(
			reinterpret_cast<const unsigned char*>(&key),
			reinterpret_cast<const unsigned char*>(&key) + sizeof(K)
		);
	}
}

template <>
vector<unsigned char> HashKey<string>(const string& key);

template <typename K, typename V>
class HashTable
{
public:
	HashTable() { }
	HashTable(size_t n) { data.resize(n); }

	void Insert(K key, V value)
	{
		int index = Hash(key);
		data[key].push_back({ key, 0 });
		size++;
	}

	void Erase(K key)
	{
		int index = Hash(key);
		for (const pair<K, V>& element : data[index])
		{
			if (element.first == key)
			{
				data[index].remove(element);
				return;
			}
		}
	}

	void Rehash()
	{
		// 기존 사이즈보다 2배 이상인 소수
		size_t newSize = GetPrime(BucketCount);
		Rehash(newSize);
	}

	void Rehash(int newSize)
	{
		vector<list<pair<K, V>>> newData(newSize);

		for (auto& bucket : data)
		{
			for (auto& element : bucket)
			{
				int newIndex = Hash(element.first) % newSize;
				newData[newIndex].push_back(element);
			}
		}

		data.swap(newData);
	}

	int GetPrime(int n)
	{
		if (n <= 2)
		{
			return 2;
		}

		// 짝수인 경우 홀수로 바꾸어, 홀수만 검사
		if (n % 2 == 0)
		{
			n++;
		}

		while (true)
		{
			if (IsPrime(n))
			{
				return n;
			}

			n += 2;
		}
	}

	bool IsPrime(int n)
	{
		if (n <= 1)
		{
			return false;
		}

		if (n <= 3)
		{
			return true;
		}

		if (n % 2 == 0 || n % 3 == 0)
		{
			return false;
		}

		// 6k +- 1 패턴 검사
		for (int i = 5; i * i <= n; i += 6)
		{
			if (n % i == 0 || n % (i + 2) == 0)
			{
				return false;
			}
		}

		return true;
	}

	int Hash(const K& key)
	{
		auto keyBytes = HashKey(key);
		unsigned char hash[SHA256_DIGEST_LENGTH];
		SHA256(keyBytes.data(), keyBytes.size(), hash);

		uint64_t result;
		memcpy(&result, hash, sizeof(uint64_t));
		return result % BucketCount();
	}

	int Size() { return size; }
	int Bucket(K key) { return Hash(key); }
	int BucketCount() { return data.size(); }
	int BucketSize(int n) { return data[n].size(); }

	V& At(K index)
	{
		int key = Hash(index);

		for (pair<K, V>& element : data[key])
		{
			if (element.first == key)
			{
				return element.second;
			}
		}

		throw out_of_range("Key not found.");
	}

	V& operator[](K index)
	{
		int key = Hash(index);

		for (pair<K, V>& element : data[key])
		{
			if (element.first == key)
			{
				return element.second;
			}
		}

		data[key].push_back({ key, 0 });
		size++;
		return data[key].back().second;
	}

private:
	vector<list<pair<K, V>>> data;
	int size = 0;
};
