#pragma once
#include "HashTable.h"

template <typename K, typename V>
class HashMap
{
public:
	HashMap() { }
	HashMap(size_t n) { hashMap.Rehash(n); }

	void insert(K key, V value) { hashMap.Insert(key, value); }
	void insert(pair<K, V> newData) { hashMap.Insert(newData.first, newData.second); }
	void erase(K key) { hashMap.Erase(key); }
	void rehash(size_t n) { hashMap.Rehash(n); }

	int size() { return hashMap.Size(); }
	bool empty() { return size() == 0; }

	int bucket(K key) { return hashMap.Bucket(key); }
	int bucket_count() { return hashMap.BucketCount(); }
	int bucket_size(int n) { return hashMap.BucketSize(n); }

	V& at(K index) { return hashMap.At(index); }
	V& operator[](K index) { return hashMap[index]; }

private:
	HashTable<K, V> hashMap;
};
