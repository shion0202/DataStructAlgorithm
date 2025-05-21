#pragma once
#include "MyGraph.h"

ostream& operator<<(ostream& os, const City& city)
{
	switch (city)
	{
	case City::SEOUL: os << "서울"; break;
	case City::DAEGU: os << "대구"; break;
	case City::INCHEON: os << "인천"; break;
	case City::BUSAN: os << "부산"; break;
	case City::POHANG: os << "포항"; break;
	case City::DAEJEON: os << "대전"; break;
	default: break;
	}

	return os;
}

MyMatrixGraph::MyMatrixGraph(int size)
{
	data.reserve(size);
	vector<int> row(size);
	fill(row.begin(), row.end(), -1);

	for (int i = 0; i < size; ++i)
	{
		data.push_back(row);
	}
}

void MyMatrixGraph::AddEdge(const City& from, const City& to, int distance)
{
	cout << "간선 추가: " << from << " <-> " << to << " = " << distance << endl;

	int n1 = static_cast<int>(from);
	int n2 = static_cast<int>(to);
	data[n1][n2] = distance;
	data[n2][n1] = distance;
}

void MyMatrixGraph::RemoveEdge(const City& from, const City& to)
{
	cout << "간선 삭제: " << from << " <-> " << to << endl;

	int n1 = static_cast<int>(from);
	int n2 = static_cast<int>(to);
	data[n1][n2] = -1;
	data[n2][n1] = -1;
}

MyListGraph::MyListGraph(int size)
{
	data = vector<vector<pair<int, int>>>(size, vector<pair<int, int>>());
}

void MyListGraph::AddEdge(const City& from, const City& to, int distance)
{
	cout << "간선 추가: " << from << " <-> " << to << " = " << distance << endl;

	int n1 = static_cast<int>(from);
	int n2 = static_cast<int>(to);
	data[n1].push_back(make_pair(n2, distance));
	data[n2].push_back(make_pair(n1, distance));
}

void MyListGraph::RemoveEdge(const City& from, const City& to)
{
	cout << "간선 삭제: " << from << " <-> " << to << endl;

	int n1 = static_cast<int>(from);
	int n2 = static_cast<int>(to);
	remove_if(data[n1].begin(), data[n1].end(), [n2](const pair<int, int>& p) {
		return p.first == n2; });
	remove_if(data[n2].begin(), data[n2].end(), [n1](const pair<int, int>& p) {
		return p.first == n1; });
}
