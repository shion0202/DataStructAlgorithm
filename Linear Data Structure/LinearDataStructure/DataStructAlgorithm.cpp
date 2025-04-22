#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <forward_list>
#include <list>
#include <algorithm>
#include "PrintWatingList.cpp"
using namespace std;

int main()
{
	Printer printer;
	vector<Job> jobs = {
		{ 1, "Alice", 5 },
		{ 2, "Bob", 3 },
		{ 3, "Charlie", 10 },
		{ 4, "David", 2 },
		{ 5, "Eve", 7 }
	};

	for (const auto& job : jobs)
	{
		printer.addJob(job);
	}
}
