#pragma once
#include <iostream>
using namespace std;

/*

[ ���� ��� ��� ���� ]
�Ϲ����� ���� ����Ʈ�� ����ϱ� �ָ��� ���α׷��� �����ϴ� ��Ȳ�� �����Ͽ�, ���� ���� ���� ����Ʈ�� �����ϴ� ����

1. ���� ���� ������ �̿��Ͽ� ��� ����� ������ �� �ִ�.
2. ��� ��Ͽ� ������ �߰��ϰų� ������ �� �ִ�.
3. ������ ��ȯ������ ����� �� �־�� �Ѵ�.

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
			cout << "��Ͽ� ������ �����ϴ�." << endl;
			return;
		}

		cout << "[ ���� ��� ]" << endl << head->name << endl;

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
