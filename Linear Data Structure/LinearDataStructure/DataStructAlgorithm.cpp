#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <forward_list>
#include <list>
#include <algorithm>
#include "DoublyLinkedList.h"
using namespace std;

int main()
{
	DoublyLinkedList<int> doublyList;

	for (int i = 0; i < 3; ++i)
	{
		doublyList.push_front((i + 1) * 100);
	}
	for (int i = 0; i < 3; ++i)
	{
		doublyList.push_back((i + 1) * 10);
	}
	cout << doublyList.front() << ", " << doublyList.back() << endl;

	doublyList.pop_front();
	doublyList.pop_back();
	cout << doublyList.size() << endl;

	DoublyLinkedList<int> newList(doublyList);
	doublyList.clear();

	newList.remove(200);

	newList.reverse();

	int beginValue = *(newList.begin());
	bool bIsSame = (newList.begin() != newList.end());

	int prefixValue = *(++newList.begin());
	int incrementValue = *(newList.begin() + 2);
}
