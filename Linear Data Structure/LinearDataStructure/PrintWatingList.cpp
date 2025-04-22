#pragma once
#include <iostream>
#include <queue>
using namespace std;

/*

[ ���� ������ �μ� ��� ��� �ùķ��̼� ]
�繫�� ��� ���� ���� ��ǻ�Ͱ� �� ���� �����Ϳ� ����Ǿ� �ִ� ��Ȳ�� �����Ͽ�, �μ� ��û ��Ȳ�� ����

1. �����ʹ� �� ���� �ϳ��� �μ� ��û�� ������ �� ������ �μ� �۾��� �Ϸ��ϱ� ���� ���� �ð��� �ʿ��ϴ�.
2. �� ���� �ٸ� ����ڰ� �μ� ��û�� ���� �� ������, �̷��� ������ �μ� ��û ������ �����Ѵ�.
3. ���� �μ� �۾��� �Ϸ�Ǹ� ������ �μ� ��û ������ Ȯ���Ͽ� ���� �μ� �۾��� �����Ѵ�.

*/

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