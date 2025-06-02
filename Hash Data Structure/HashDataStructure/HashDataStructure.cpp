#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "SimpleDictionary.h"
#include "ChainingHashTable.h"
#include "CuckooHashTable.h"
#include "BloomFilter.h"
using namespace std;

void CreateSimpleDictionary()
{
    MyHashMap map(7);

	auto Print = [&](uint value) {
		if (map.Find(value))
			cout << value << " 검색 성공" << endl;
		else
			cout << value << " 검색 실패" << endl;
		};

	map.Insert(2);
	map.Insert(25);
	map.Insert(10);
	Print(25);

	map.Insert(100);
	Print(100);
	Print(2);

	map.Erase(25);
}
void CreateChainingHashMap()
{
	ChainingHashMap map(7);

	auto Print = [&](uint value) {
		if (map.Find(value))
			cout << value << " 검색 성공" << endl;
		else
			cout << value << " 검색 실패" << endl;
		};

	map.Insert(2);
	map.Insert(25);
	map.Insert(10);
	Print(25);

	map.Insert(100);
	map.Insert(55);
	Print(100);
	Print(2);

	map.Erase(2);
}
void CreateCuckooHashMap()
{
	CuckooHashMap map(7);
	map.Print();
	cout << endl;

	map.Insert(10);
	map.Insert(20);
	map.Insert(30);
	cout << endl;

	map.Insert(104);
	map.Insert(2);
	map.Insert(70);
	map.Insert(9);
	map.Insert(90);
	map.Insert(2);
	map.Insert(7);
	cout << endl;

	map.Print();
	cout << endl;

	// 순환 발생으로 삽입 실패
	map.Insert(14);
}

void Find(const unordered_map<int, int>& map, int key)
{
	auto it = map.find(key);
	if (it != map.end())
		cout << "Key " << key << " found with value: " << it->second << endl;
	else
		cout << "Key " << key << " not found." << endl;
}
void Find(const unordered_set<int>& set, int value)
{
	if (set.find(value) != set.end())
		cout << "Value " << value << " found." << endl;
	else
		cout << "Value " << value << " not found." << endl;
}
void Print(const unordered_map<int, int>& map)
{
	for (const auto& pair : map)
	{
		cout << pair.first << " -> " << pair.second << endl;
	}
}
void Print(const unordered_set<int>& set)
{
	for (const auto& value : set)
	{
		cout << value << " ";
	}
	cout << endl;
}
void CreateHashTable()
{
	cout << "=== std::unoredered_set 예제 ===" << endl;
	unordered_set<int> set = { 1, 2, 3, 4, 5 };
	cout << "초기 값: ";
	Print(set);

	set.insert(2);
	cout << "2 삽입: ";
	Print(set);

	set.insert(10);
	set.insert(300);
	cout << "10, 300 삽입: ";
	Print(set);

	Find(set, 4);
	Find(set, 100);

	set.erase(2);
	cout << "2 삭제: ";
	Print(set);

	Find(set, 2);
	cout << endl;

	cout << "=== std::unoredered_map 예제 ===" << endl;
	unordered_map<int, int> map;
	
	map.insert({ 2, 4 });
	map[3] = 9;
	cout << "2, 3의 제곱 삽입: ";
	Print(map);

	map[20] = 400;
	map[30] = 900;
	cout << "20, 30의 제곱 삽입: ";
	Print(map);

	Find(map, 10);
	Find(map, 20);
	cout << "map[3] = " << map[3] << endl;
	cout << "map[100] = " << map[100] << endl;
	Print(map);
}

void CreateBloomFilter()
{
	BloomFilter bf(7);
	bf.Insert(100);
	bf.Insert(54);
	bf.Insert(82);

	bf.Lookup(5);
	bf.Lookup(50);
	bf.Lookup(20);
	bf.Lookup(54);
}

int main()
{
	CreateBloomFilter();
}
