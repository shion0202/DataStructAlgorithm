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

	int fromCity = static_cast<int>(from);
	int toCity = static_cast<int>(to);
	data[fromCity][toCity] = -1;
	data[toCity][fromCity] = -1;
}

void MyMatrixGraph::DFS()
{
	stack<City> s;
	vector<bool> visited(data.size(), false);

	for (int start = 0; start < data.size(); ++start)
	{
		if (visited[start])
		{
			continue;
		}

		s.push(static_cast<City>(start));
		visited[start] = true;

		while (!s.empty())
		{
			City current = s.top();
			s.pop();
			cout << "Visited: " << static_cast<int>(current) << endl;

			for (int i = data.size() - 1; i >= 0; --i)
			{
				if (data[static_cast<int>(current)][i] > 0 && !visited[i])
				{
					s.push(static_cast<City>(i));
					visited[i] = true;
				}
			}
		}
	}
	cout << endl;
}

void MyMatrixGraph::BFS()
{
	queue<City> q;
	vector<bool> visited(data.size(), false);

	for (int start = 0; start < data.size(); ++start)
	{
		if (visited[start])
		{
			continue;
		}

		q.push(static_cast<City>(start));
		visited[start] = true;

		while (!q.empty())
		{
			City current = q.front();
			q.pop();
			cout << "Visited: " << static_cast<int>(current) << endl;

			for (int i = 0; i < data.size(); ++i)
			{
				if (data[static_cast<int>(current)][i] > 0 && !visited[i])
				{
					q.push(static_cast<City>(i));
					visited[i] = true;
				}
			}
		}
	}
	cout << endl;
}

void MyMatrixGraph::OldDFS()
{
	// 현재 정점을 예약(스택)하고 갈 수 있다면 다음 정점으로 이동, 반복
	// 갈 수 있는 노드가 없다면 현재 노드를 방문(보통 bool로 체크)
	// 이전 노드로 돌아간 뒤(스택의 경우 다음 top을 pop) 1번 체크, 없으면 2번 반복
	// 만약 그래프가 끊어져 중간에 스택이 비었다면, 끊긴 정점에서 다시 시작

	stack<City> s;
	vector<bool> checked(data.size(), false);
	vector<bool> visited(data.size(), false);

	s.push(City::SEOUL);
	checked[static_cast<int>(City::SEOUL)] = true;

	while (true)
	{
		bool isChecked = false;

		if (s.empty())
		{
			for (int i = 0; i < data.size(); ++i)
			{
				if (!visited[i])
				{
					s.push(City(i));
					checked[i] = true;
					isChecked = true;
					break;
				}
			}

			if (isChecked)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (int i = 0; i < data.size(); ++i)
		{
			if (data[static_cast<int>(s.top())][i] != -1 && !checked[i])
			{
				s.push(static_cast<City>(i));
				checked[i] = true;
				isChecked = true;
				break;
			}
		}

		if (isChecked)
		{
			continue;
		}

		// 현재 정점이 갈 수 있는 노드가 없을 경우
		visited[static_cast<int>(s.top())] = true;
		cout << "Visited: " << static_cast<int>(s.top()) << endl;
		s.pop();
	}
	cout << endl;
}

void MyMatrixGraph::OldBFS()
{
	// 첫번째 정점을 큐에 저장
	// 큐에 저장된 정점을 pop하여 방문, 해당 정점과 연결된 정점들을 큐에 push
	// 2를 반복, 이후 큐가 비어있을 경우 모든 정점을 방문했는지 확인

	queue<City> q;
	vector<bool> visited(data.size(), false);

	q.push(City::SEOUL);

	while (true)
	{
		if (q.empty())
		{
			bool isChecked = false;

			for (int i = 0; i < data.size(); ++i)
			{
				if (!visited[i])
				{
					q.push(City(i));
					isChecked = true;
					break;
				}
			}

			if (isChecked)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		City current = q.front();
		q.pop();

		if (visited[static_cast<int>(current)])
		{
			continue;
		}

		visited[static_cast<int>(current)] = true;
		cout << "Visited: " << static_cast<int>(current) << endl;

		for (int i = 0; i < data.size(); ++i)
		{
			if (data[static_cast<int>(current)][i] != -1 && !visited[i])
			{
				q.push(static_cast<City>(i));
			}
		}
	}
	cout << endl;
}

MyListGraph::MyListGraph(int size)
{
	data = vector<vector<pair<int, int>>>(size, vector<pair<int, int>>());
}

void MyListGraph::AddEdge(const City& from, const City& to, int distance)
{
	cout << "간선 추가: " << from << " <-> " << to << " = " << distance << endl;

	int fromCity = static_cast<int>(from);
	int toCity = static_cast<int>(to);
	data[fromCity].push_back(make_pair(toCity, distance));
	data[toCity].push_back(make_pair(fromCity, distance));
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

void MyListGraph::DFS()
{
	stack<City> s;
	vector<bool> visited(data.size(), false);

	for (int start = 0; start < data.size(); ++start)
	{
		if (visited[start])
		{
			continue;
		}

		s.push(static_cast<City>(start));
		visited[start] = true;

		while (!s.empty())
		{
			City current = s.top();
			s.pop();
			cout << "Visited: " << static_cast<int>(current) << endl;

			for (int i = data[static_cast<int>(current)].size() - 1; i >= 0; --i)
			{
				int targetNode = data[static_cast<int>(current)][i].first;

				if (!visited[targetNode])
				{
					s.push(static_cast<City>(targetNode));
					visited[targetNode] = true;
				}
			}
		}
	}
	cout << endl;
}

void MyListGraph::BFS()
{
	queue<City> q;
	vector<bool> visited(data.size(), false);

	for (int start = 0; start < data.size(); ++start)
	{
		if (visited[start])
		{
			continue;
		}

		q.push(static_cast<City>(start));
		visited[start] = true;

		while (!q.empty())
		{
			City current = q.front();
			q.pop();
			cout << "Visited: " << static_cast<int>(current) << endl;

			for (int i = 0; i < data[static_cast<int>(current)].size(); ++i)
			{
				int targetNode = data[static_cast<int>(current)][i].first;
				if (!visited[targetNode])
				{
					q.push(static_cast<City>(targetNode));
					visited[targetNode] = true;
				}
			}
		}
	}
	cout << endl;
}
