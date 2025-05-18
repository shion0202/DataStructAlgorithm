#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

// 연산자, 반복자, 초기화 리스트, 람다식
struct MyNode
{
	MyNode* next;
	int data;
};

class MyForwardList
{
public:
	using node = MyNode;
	using nodePtr = MyNode*;

	class MyForwardListIterator
	{
	public:
		MyForwardListIterator(nodePtr ptr) : ptr(ptr) {}

		int& operator*() { return ptr->data; }
		nodePtr get() { return ptr; }

		MyForwardListIterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		MyForwardListIterator& operator++(int)
		{
			MyForwardListIterator newIterator = *this;
			++(*this);
			return newIterator;
		}

		friend bool operator==(const MyForwardListIterator& left, const MyForwardListIterator& right)
		{
			return left.ptr == right.ptr;
		}

		friend bool operator!=(const MyForwardListIterator& left, const MyForwardListIterator& right)
		{
			return left.ptr != right.ptr;
		}

	private:
		nodePtr ptr;
	};

public:
	MyForwardList() = default;

	MyForwardList(const MyForwardList& other) : Head(NULL)
	{
		if (other.Head == NULL)
		{
			return;
		}

		Head = new node{ 0, NULL };
		nodePtr currentNode = Head;
		auto it = other.begin();

		while (true)
		{
			currentNode->data = *it;

			auto tmp = it;
			++tmp;
			if (tmp == other.end())
			{
				break;
			}

			currentNode->next = new node{ 0, NULL };
			currentNode = currentNode->next;
			it = tmp;
		}
	}

	MyForwardList(const initializer_list<int>& ilist) : Head(NULL)
	{
		for (auto it = rbegin(ilist); it != rend(ilist); ++it)
		{
			push_front(*it);
		}
	}

	~MyForwardList()
	{
		clear();
	}

	void push_front(int data)
	{
		nodePtr newNode = new node {NULL, data};

		if (Head != NULL)
		{
			newNode->next = Head;
		}

		Head = newNode;
	}

	void pop_front()
	{
		if (Head == NULL)
		{
			return;
		}

		nodePtr newNode = Head;
		Head = Head->next;
		delete newNode;
	}

	MyForwardListIterator insertAfter(MyForwardListIterator where, int value)
	{
		if (where == NULL)
		{
			return NULL;
		}

		nodePtr newNode = new node {where.get()->next, value};
		where.get()->next = newNode;
		return newNode;
	}
	
	MyForwardListIterator eraseAfter(MyForwardListIterator where)
	{
		if (where == NULL)
		{
			return NULL;
		}

		nodePtr newNode = where.get()->next;

		if (newNode != NULL)
		{
			where.get()->next = where.get()->next->next;
		}

		delete newNode;
		return where.get()->next;
	}

	void remove(int value)
	{
		removeIf([&](const int& other) -> bool { return other == value; });
	}

	template <class C>
	void removeIf(C func)
	{
		nodePtr prev = NULL;
		MyForwardListIterator it = begin();

		while (it != end())
		{
			if (func(it.get()->data))
			{
				nodePtr tmp = it.get();

				if (prev == NULL)
				{
					Head = tmp->next;
				}
				else
				{
					prev->next = tmp->next;
				}

				it++;
				delete tmp;
			}
			else
			{
				it++;
			}
		}
	}
	
	const int& front()
	{
		if (Head == NULL)
		{
			return NULL;
		}

		return Head->data;
	}

	void clear()
	{
		while (Head != NULL)
		{
			nodePtr newNode = Head;
			Head = Head->next;
			delete newNode;
		}
	}
	
	bool empty() { return Head == NULL; }

	MyForwardListIterator begin() { return MyForwardListIterator(Head); }
	MyForwardListIterator begin() const { return MyForwardListIterator(Head); }
	MyForwardListIterator end() { return MyForwardListIterator(NULL); }
	MyForwardListIterator end() const { return MyForwardListIterator(NULL); }
	
private:
	nodePtr Head;
};
