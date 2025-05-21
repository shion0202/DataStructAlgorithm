#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum class City : int
{
	SEOUL,
	DAEGU,
	INCHEON,
	BUSAN,
	POHANG,
	DAEJEON
};

ostream& operator<<(ostream& os, const City& city);

class MyMatrixGraph
{
public:
	// ����ִ� ��� �׷����� ����
	MyMatrixGraph(int size);

	// ���� �߰�
	void AddEdge(const City& from, const City& to, int distance);

	// ���� ����
	void RemoveEdge(const City& from, const City& to);

private:
	vector<vector<int>> data;
};

class MyListGraph
{
public:
	// ����ִ� ����Ʈ �׷����� ����
	MyListGraph(int size);

	void AddEdge(const City& from, const City& to, int distance);
	void RemoveEdge(const City& from, const City& to);

private:
	vector<vector<pair<int, int>>> data;
};
