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
	// 비어있는 행렬 그래프를 생성
	MyMatrixGraph(int size);

	// 간선 추가
	void AddEdge(const City& from, const City& to, int distance);

	// 간선 삭제
	void RemoveEdge(const City& from, const City& to);

private:
	vector<vector<int>> data;
};

class MyListGraph
{
public:
	// 비어있는 리스트 그래프를 생성
	MyListGraph(int size);

	void AddEdge(const City& from, const City& to, int distance);
	void RemoveEdge(const City& from, const City& to);

private:
	vector<vector<pair<int, int>>> data;
};
