#pragma once
#include <iostream>
#include <queue>
using namespace std;

// 한 번에 하나의 인쇄 요청을 수행하며, 인쇄 작업이 완료되면 대기 중인 요청을 처리하는 공유 프린터를 구현하는 문제

struct Job
{
	int id;
	string requester;
	int pages;
};

inline ostream& operator<<(ostream& os, const Job& job)
{
	os << "[ ID: " << job.id << ", 요청자: " << job.requester << ", 페이지 수: " << job.pages << " ]";
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
			cout << "인쇄 대기 중: " << newJob << endl;
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
			cout << "인쇄 대기 중: " << newJob << endl;
		}
	}

	void processJobs()
	{
		while (!printQueue.empty())
		{
			Job currentJob = printQueue.front();

			cout << "인쇄 시작: " << currentJob << endl;

			printQueue.pop();
		}
	}

private:
	queue<Job> printQueue;
};