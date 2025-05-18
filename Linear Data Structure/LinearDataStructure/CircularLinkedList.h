#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct CircularNode
{
	T data;
	CircularNode<T>* next;
};

template <typename T>
class CircularLinkedList
{
public:
	CircularLinkedList() : head(nullptr), listSize(0) {}

	CircularLinkedList(CircularLinkedList<T>& other)
	{
		listSize = 0;

		if (other.empty())
		{
			head = NULL;
			return;
		}

		push_front(other.head->data);

		CircularNode<T>* curNode = other.head->next;
		while (curNode != other.head)
		{
			push_front(curNode->data);
			curNode = curNode->next;
		}
	}

	~CircularLinkedList() { clear(); }

	void push_front(const T& value)
	{
		// �� ��� ���� �� ����
		// �� ����� next�� head->next�̰�, head->next�� �� ����� next�� ����
		// head(back) -> �� ���(front) -> ... -> head

		CircularNode<T>* newNode = new CircularNode<T>();
		newNode->data = value;

		if (empty())
		{
			newNode->next = newNode;
			head = newNode;
		}
		else
		{
			newNode->next = head->next;
			head->next = newNode;
		}

		listSize++;
	}

	void pop_front()
	{
		// head->next�� �����ϰ� head->next�� head->next->next�� ����

		if (empty())
		{
			return;
		}

		if (size() == 1)
		{
			delete head;
			head = nullptr;
			listSize--;

			return;
		}

		CircularNode<T>* tempNode = head->next;
		head->next = head->next->next;
		delete tempNode;

		listSize--;
	}

	void remove(const T& value)
	{
		remove_if([&](const T& other) -> bool { return other == value; });
	}

	template <class Pred>
	void remove_if(Pred predicate)
	{
		if (empty())
		{
			return;
		}

		if (size() == 1)
		{
			if (predicate(head->data))
			{
				pop_front();
			}

			return;
		}

		CircularNode<T>* preNode = head;
		CircularNode<T>* curNode = head->next;

		while (curNode != head)
		{
			if (predicate(curNode->data))
			{
				preNode->next = curNode->next;
				delete curNode;
				listSize--;

				return;
			}

			preNode = curNode;
			curNode = curNode->next;
		}

		if (predicate(curNode->data))
		{
			preNode->next = curNode->next;
			head = preNode;
			delete curNode;
			listSize--;
		}
	}

	void reverse()
	{
		// 1->2->3->4(head)->1�� 4->3->2->1(head)->4�� ����
		// 1(head->next)�� next�� 4�� ����Ű���� �ϰ�, head�� 1�� ����
		// 1�� ���� next(2)�� �����ؾ� �ϴµ�, �̸� ������ next�� �����Ͽ� ���
		// �̸� 1(head)�� �� ������ �ݺ�

		if (empty() || size() == 1)
		{
			return;
		}

		CircularNode<T>* prevNode = head;
		CircularNode<T>* curNode = head->next;
		CircularNode<T>* nextNode = nullptr;

		while (curNode != head)
		{
			nextNode = curNode->next;

			curNode->next = prevNode;

			prevNode = curNode;
			curNode = nextNode;
		}

		nextNode = curNode->next;
		curNode->next = prevNode;
		head = nextNode;
	}

	void clear()
	{
		while (head)
		{
			pop_front();
		}
	}

	const T& front()
	{
		if (empty())
		{
			throw out_of_range("front() called on empty list.");
		}

		return head->next->data;
	}

	const T& back()
	{
		if (empty())
		{
			throw out_of_range("back() called on empty list.");
		}

		return head->data;
	}

	int size() { return listSize; }
	bool empty() { return size() == 0 ? true : false; }

private:
	CircularNode<T>* head;
	int listSize;
};
