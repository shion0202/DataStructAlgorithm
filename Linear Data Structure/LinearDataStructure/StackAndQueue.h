#pragma once
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <typename T>
class VectorStack
{
public:
	VectorStack() : last(-1)
	{
		data.reserve(1);
	}

	void push(const T& value)
	{
		if (data.size() == data.capacity())
		{
			data.reserve(data.size() * 2);
			cout << "Reserved memory doubled to " << data.capacity() << ", ";
		}

		cout << "Pushed value: " << value << endl;
		data.push_back(value);
		last++;
	}

	void pop()
	{
		if (last < 0)
		{
			throw out_of_range("Stack is empty");
		}

		cout << "Poped value: " << top() << endl;
		data.pop_back();
		last--;
	}

	T& top()
	{
		if (last < 0)
		{
			throw out_of_range("Stack is empty.");
		}

		return data[last];
	}

	bool empty() { return last < 0; }
	int size() { return last + 1; }

private:
	vector<T> data;
	int last;
};

template <typename T>
class ListStack
{
public:
	void push(const T& value)
	{
		cout << "Pushed value: " << value << endl;
		data.push_back(value);
	}

	void pop()
	{
		if (empty())
		{
			throw out_of_range("Stack is empty.");
		}

		cout << "Poped value: " << top() << endl;
		data.pop_back();
	}

	T& top()
	{
		if (empty())
		{
			throw out_of_range("Stack is empty.");
		}

		return data.back();
	}

	bool empty() { return data.empty(); }
	int size() { return data.size(); }

private:
	list<T> data;
};

template <typename T>
class VectorQueue
{
public:
	VectorQueue() : first(0), last(-1)
	{
		data.reserve(1);
	}

	void push(const T& value)
	{
		if (data.size() == data.capacity())
		{
			data.reserve(data.size() * 2);
			cout << "Reserved memory doubled to " << data.capacity() << ", ";
		}

		cout << "Pushed value: " << value << endl;
		data.push_back(value);
		last++;
	}

	void pop()
	{
		if (empty())
		{
			throw out_of_range("Queue is empty.");
		}

		cout << "Poped value: " << front() << endl;
		first++;
	}

	T& front()
	{
		if (empty())
		{
			throw out_of_range("Queue is empty.");
		}

		return data[first];
	}

	T& back()
	{
		if (empty())
		{
			throw out_of_range("Queue is empty.");
		}

		return data[last];
	}

	bool empty() { return (last == -1 || size() == 0); }
	int size() { return last - first + 1; }

private:
	vector<int> data;
	int first;
	int last;
};

template <typename T>
class ListQueue
{
public:
	void push(const T& value)
	{
		cout << "Pushed value: " << value << endl;
		data.push_back(value);
	}

	void pop()
	{
		if (empty())
		{
			throw out_of_range("Queue is empty.");
		}

		cout << "Poped value: " << front() << endl;
		data.pop_front();
	}

	T& front()
	{
		if (empty())
		{
			throw out_of_range("Queue is empty.");
		}

		return data.front();
	}

	T& back()
	{
		if (empty())
		{
			throw out_of_range("Queue is empty.");
		}

		return data.back();
	}

	bool empty() { return data.empty(); }
	int size() { return data.size(); }

private:
	list<T> data;
};