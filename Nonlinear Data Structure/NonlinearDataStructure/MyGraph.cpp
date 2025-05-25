#pragma once
#include "MyGraph.h"

ostream& operator<<(ostream& os, const City& city)
{
	switch (city)
	{
	case City::SEOUL: os << "����"; break;
	case City::DAEGU: os << "�뱸"; break;
	case City::INCHEON: os << "��õ"; break;
	case City::BUSAN: os << "�λ�"; break;
	case City::POHANG: os << "����"; break;
	case City::DAEJEON: os << "����"; break;
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
	cout << "���� �߰�: " << from << " <-> " << to << " = " << distance << endl;

	int n1 = static_cast<int>(from);
	int n2 = static_cast<int>(to);
	data[n1][n2] = distance;
	data[n2][n1] = distance;
}

void MyMatrixGraph::RemoveEdge(const City& from, const City& to)
{
	cout << "���� ����: " << from << " <-> " << to << endl;

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
	// ���� ������ ����(����)�ϰ� �� �� �ִٸ� ���� �������� �̵�, �ݺ�
	// �� �� �ִ� ��尡 ���ٸ� ���� ��带 �湮(���� bool�� üũ)
	// ���� ���� ���ư� ��(������ ��� ���� top�� pop) 1�� üũ, ������ 2�� �ݺ�
	// ���� �׷����� ������ �߰��� ������ ����ٸ�, ���� �������� �ٽ� ����

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

		// ���� ������ �� �� �ִ� ��尡 ���� ���
		visited[static_cast<int>(s.top())] = true;
		cout << "Visited: " << static_cast<int>(s.top()) << endl;
		s.pop();
	}
	cout << endl;
}

void MyMatrixGraph::OldBFS()
{
	// ù��° ������ ť�� ����
	// ť�� ����� ������ pop�Ͽ� �湮, �ش� ������ ����� �������� ť�� push
	// 2�� �ݺ�, ���� ť�� ������� ��� ��� ������ �湮�ߴ��� Ȯ��

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
	cout << "���� �߰�: " << from << " <-> " << to << " = " << distance << endl;

	int fromCity = static_cast<int>(from);
	int toCity = static_cast<int>(to);
	data[fromCity].push_back(make_pair(toCity, distance));
	data[toCity].push_back(make_pair(fromCity, distance));
}

void MyListGraph::RemoveEdge(const City& from, const City& to)
{
	cout << "���� ����: " << from << " <-> " << to << endl;

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
