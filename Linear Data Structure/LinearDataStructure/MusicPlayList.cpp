#pragma once
#include <iostream>
using namespace std;

/*

[ 음악 재생 목록 구현 ]
일반적인 연결 리스트를 사용하기 애매한 프로그램을 구현하는 상황을 가정하여, 직접 원형 연결 리스트를 구현하는 문제

1. 여러 개의 음악을 이용하여 재생 목록을 생성할 수 있다.
2. 재생 목록에 음악을 추가하거나 제거할 수 있다.
3. 음악을 순환적으로 재생할 수 있어야 한다.

*/

struct MusicNode
{
	MusicNode* next;
	string name;
};

class Playlist
{
public:
	using node = MusicNode;
	using nodePtr = node*;

	class PlaylistIterator
	{
	public:
		PlaylistIterator(nodePtr p) : ptr(p) {}

		nodePtr get() { return ptr; }

		string& operator*() { return ptr->name; }

		PlaylistIterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		PlaylistIterator operator++(int)
		{
			PlaylistIterator temp = *this;
			++(*this);
			return temp;
		}

		friend bool operator==(const PlaylistIterator& left, const PlaylistIterator& right)
		{
			return left.ptr == right.ptr;
		}

		friend bool operator!=(const PlaylistIterator& left, const PlaylistIterator& right)
		{
			return left.ptr != right.ptr;
		}

	private:
		nodePtr ptr;
	};

	Playlist() = default;

	Playlist(const Playlist& other) : head(NULL)
	{
		if (other.head == NULL)
		{
			return;
		}

		head = new node{ NULL, "" };
		nodePtr curNode = head;
		auto it = other.begin();

		while (true)
		{
			curNode->name = *it;

			auto tmp = it;
			++tmp;
			if (tmp == other.begin())
			{
				break;
			}

			curNode->next = new node{ NULL, "" };
			curNode = curNode->next;
			it = tmp;
		}
	}

	Playlist(const initializer_list<MusicNode>& ilist) : head(NULL)
	{
		for (const auto& element : ilist)
		{
			push_front(element.name);
		}
	}

	~Playlist()
	{
		clear();
	}

	void push_front(string data)
	{
		nodePtr newNode = new node{ NULL, data };

		if (head == NULL)
		{
			newNode->next = newNode;
			head = newNode;
		}
		else
		{
			newNode->next = head->next;
			head->next = newNode;
		}
	}

	void pop_front()
	{
		if (head == NULL)
		{
			return;
		}

		if (head->next == head)
		{
			delete head;
			head = NULL;
			return;
		}

		nodePtr tmp = head->next;
		head->next = head->next->next;
		delete tmp;
	}

	void insert_after(PlaylistIterator where, string data)
	{
		nodePtr targetNode = where.get();
		if (targetNode == NULL)
		{
			return;
		}

		nodePtr curNode = head->next;
		bool bIsContain = false;

		if (head == targetNode)
		{
			bIsContain = true;
		}
		else
		{
			while (curNode != head)
			{
				if (curNode == targetNode)
				{
					bIsContain = true;
					break;
				}
				curNode = curNode->next;
			}
		}

		if (!bIsContain)
		{
			return;
		}

		nodePtr newNode = new node{ NULL, data };
		newNode->next = targetNode->next;
		targetNode->next = newNode;
	}

	void erase_after(PlaylistIterator where)
	{
		nodePtr targetNode = where.get();
		if (targetNode == NULL)
		{
			return;
		}

		nodePtr curNode = head->next;
		bool bIsContain = false;

		if (head == targetNode)
		{
			bIsContain = true;
		}
		else
		{
			while (curNode != head)
			{
				if (curNode == targetNode)
				{
					bIsContain = true;
					break;
				}
				curNode = curNode->next;
			}
		}

		if (!bIsContain)
		{
			return;
		}

		if (targetNode->next == targetNode)
		{
			delete targetNode;
			head = NULL;
		}
		else
		{
			nodePtr tmp = targetNode->next;
			targetNode->next = targetNode->next->next;
			delete tmp;
		}
	}

	void clear()
	{
		if (head == NULL)
		{
			return;
		}
		
		nodePtr curNode = head->next;
		while (curNode != head)
		{
			nodePtr tmp = curNode;
			curNode = curNode->next;
			delete tmp;
		}

		delete head;
		head = NULL;
	}

	void print_all()
	{
		if (head == NULL)
		{
			cout << "목록에 음악이 없습니다." << endl;
			return;
		}

		cout << "[ 음악 목록 ]" << endl << head->name << endl;

		nodePtr curNode = head->next;
		while (curNode != head)
		{
			cout << curNode->name << endl;
			curNode = curNode->next;
		}
		cout << endl;
	}

	PlaylistIterator begin() { return PlaylistIterator(head); }
	PlaylistIterator begin() const { return PlaylistIterator(head); }
	PlaylistIterator end() { return PlaylistIterator(NULL); }
	PlaylistIterator end() const { return PlaylistIterator(NULL); }

private:
	nodePtr head;
};
