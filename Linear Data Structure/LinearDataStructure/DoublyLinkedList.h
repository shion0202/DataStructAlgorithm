#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct DoublyNode
{
	T data;
	DoublyNode<T>* prev;
	DoublyNode<T>* next;
};

template <typename T>
class DoublyLinkedList
{
public:
	class DoublyLinkedListIterator
	{
	public:
		DoublyLinkedListIterator(DoublyNode<T>* nodePtr) : pointer(nodePtr) {}

		T& operator*() { return pointer->data; }

		DoublyLinkedListIterator& operator++()
		{
			pointer = pointer->next;
			return *this;
		}

		DoublyLinkedListIterator operator++(int)
		{
			DoublyLinkedListIterator temp = *this;
			++(*this);
			return temp;
		}

		DoublyLinkedListIterator& operator+(int value)
		{
			// value가 현재 리스트의 마지막 위치보다 큰 값이라면?

			for (int i = 0; i < value; ++i)
			{
				pointer = pointer->next;
			}
			return *this;
		}

		bool operator==(const DoublyLinkedListIterator& other) { return pointer == other.pointer; }
		bool operator!=(const DoublyLinkedListIterator& other) { return pointer != other.pointer; }

	private:
		DoublyNode<T>* pointer;
	};

public:
	DoublyLinkedList() : listSize(0)
	{
		DoublyNode<T>* newNode = new DoublyNode<T>();
		newNode->data = NULL;
		newNode->prev = nullptr;
		newNode->next = nullptr;

		head = newNode;
	}

	DoublyLinkedList(DoublyLinkedList<T>& other)
	{
		listSize = 0;

		DoublyNode<T>* newNode = new DoublyNode<T>();
		newNode->data = NULL;
		newNode->prev = nullptr;
		newNode->next = nullptr;

		head = newNode;

		if (other.empty())
		{
			return;
		}

		DoublyNode<T>* curNode = other.head->next;
		while (true)
		{
			push_back(curNode->data);

			if (curNode == other.head->prev)
			{
				break;
			}

			curNode = curNode->next;
		}
	}

	~DoublyLinkedList() { clear(); delete head; }

	void push_front(const T& value)
	{
		// head->next에 새 노드를 추가
		head->next = GetNode(value);
	}

	void push_back(const T& value)
	{
		// head->prev에 새 노드를 추가
		head->prev = GetNode(value);
	}

	void pop_front()
	{
		// head->next를 삭제하고 head->next를 head->next->next로 변경
		// next의 이전에 위치한 노드인 prev->next를 head->next->next로 변경
		// next의 다음에 오는 노드인 next->prev를 head->next->prev로 변경

		if (empty())
		{
			return;
		}

		DoublyNode<T>* tempNode = head->next;

		if (size() == 1)
		{
			head->prev = nullptr;
			head->next = nullptr;
			delete tempNode;
			listSize--;

			return;
		}

		head->next = tempNode->next;
		tempNode->prev->next = tempNode->next;
		tempNode->next->prev = tempNode->prev;
		delete tempNode;
		listSize--;
	}

	void pop_back()
	{
		if (empty())
		{
			return;
		}

		DoublyNode<T>* tempNode = head->prev;

		if (size() == 1)
		{
			head->prev = nullptr;
			head->next = nullptr;
			delete tempNode;
			listSize--;

			return;
		}

		head->prev = tempNode->prev;
		tempNode->prev->next = tempNode->next;
		tempNode->next->prev = tempNode->prev;
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
		// 맨 앞, 맨 뒤의 노드가 삭제될 경우 head도 수정이 필요
		// 중간 노드가 삭제될 경우 전후 노드의 포인터만 변경

		if (empty())
		{
			return;
		}

		if (size() == 1)
		{
			if (predicate(head->next->data))
			{
				pop_front();
			}

			return;
		}

		DoublyNode<T>* curNode = head->next;

		// head->next, 즉 첫 노드가 삭제 대상일 경우
		if (predicate(curNode->data))
		{
			head->next = curNode->next;
			curNode->prev->next = curNode->next;
			curNode->next->prev = curNode->prev;
			delete curNode;
			listSize--;

			return;
		}

		curNode = curNode->next;

		while (curNode != head->prev)
		{
			if (predicate(curNode->data))
			{
				curNode->prev->next = curNode->next;
				curNode->next->prev = curNode->prev;
				delete curNode;
				listSize--;

				return;
			}

			curNode = curNode->next;
		}

		// head->prev, 즉 마지막 노드가 삭제 대상일 경우
		if (predicate(curNode->data))
		{
			head->prev = curNode->prev;
			curNode->prev->next = curNode->next;
			curNode->next->prev = curNode->prev;
			delete curNode;
			listSize--;
		}
	}

	void reverse()
	{
		// 이중 연결 리스트이므로 모든 노드의 next와 prev 값을 서로 변경

		if (empty() || size() == 1)
		{
			return;
		}

		DoublyNode<T>* curNode = head->next;
		DoublyNode<T>* nextNode = nullptr;

		while (curNode != head->prev)
		{
			nextNode = curNode->next;
			curNode->next = curNode->prev;
			curNode->prev = nextNode;

			curNode = nextNode;
		}

		nextNode = curNode->next;
		curNode->next = curNode->prev;
		curNode->prev = nextNode;

		nextNode = head->next;
		head->next = head->prev;
		head->prev = nextNode;
	}

	void clear()
	{
		while (head->next)
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

		return head->prev->data;
	}

	int size() { return listSize; }
	bool empty() { return size() == 0 ? true : false; }

	DoublyLinkedListIterator begin() { return DoublyLinkedListIterator(head->next); }
	DoublyLinkedListIterator begin() const { return DoublyLinkedListIterator(head->next); }
	DoublyLinkedListIterator end() { return DoublyLinkedListIterator(head->prev); }
	DoublyLinkedListIterator end() const { return DoublyLinkedListIterator(head->prev); }

private:
	DoublyNode<T>* GetNode(const T& value)
	{
		DoublyNode<T>* newNode = new DoublyNode<T>();
		newNode->data = value;

		if (empty())
		{
			newNode->prev = newNode;
			newNode->next = newNode;

			head->prev = newNode;
			head->next = newNode;
		}
		else
		{
			head->next->prev = newNode;
			head->prev->next = newNode;

			newNode->prev = head->prev;
			newNode->next = head->next;
		}

		listSize++;

		return newNode;
	}

private:
	DoublyNode<T>* head;
	int listSize;
};
