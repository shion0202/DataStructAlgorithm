#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
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

	void DFS();
	void BFS();

	void OldDFS();
	void OldBFS();

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

	void DFS();
	void BFS();

private:
	vector<vector<pair<int, int>>> data;
};
