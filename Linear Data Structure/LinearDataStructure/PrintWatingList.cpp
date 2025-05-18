#pragma once
#include <iostream>
#include <queue>
using namespace std;

// �� ���� �ϳ��� �μ� ��û�� �����ϸ�, �μ� �۾��� �Ϸ�Ǹ� ��� ���� ��û�� ó���ϴ� ���� �����͸� �����ϴ� ����

struct Job
{
	int id;
	string requester;
	int pages;
};

inline ostream& operator<<(ostream& os, const Job& job)
{
	os << "[ ID: " << job.id << ", ��û��: " << job.requester << ", ������ ��: " << job.pages << " ]";
	return os;
}

class Printer
{
public:
	void addJob(int id, string requester, int pages)
	{
		Job newJob{ id, requester, pages };
		printQueue.push(newJob);

		if (printQueue.size() == 1)
		{
			processJobs();
		}
		else
		{
			cout << "�μ� ��� ��: " << newJob << endl;
		}
	}

	void addJob(Job newJob)
	{
		printQueue.push(newJob);

		if (printQueue.size() == 1)
		{
			processJobs();
		}
		else
		{
			cout << "�μ� ��� ��: " << newJob << endl;
		}
	}

	void processJobs()
	{
		while (!printQueue.empty())
		{
			Job currentJob = printQueue.front();

			cout << "�μ� ����: " << currentJob << endl;

			printQueue.pop();
		}
	}

private:
	queue<Job> printQueue;
};