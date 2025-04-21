#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

/*

[ ī�� ���� �ùķ��̼� ]
�־��� ��Ȳ�� �м��ϰ�, ���� ������ �ڷ� ������ �����Ͽ� ī�� ������ �����ϴ� ����

1. 4���� �÷��̾ �ְ�, ���� ������ ī�� 13���� ������ ������ �����Ѵ�.
2. �� �÷��̾��� ī�� �� ������ ī�� 1���� �����Ѵ�.
3. 4���� ī�带 ���Ͽ�, �ߺ��Ǵ� ī�� ���� �����Ѵ�. �� �� 3���� ī�尡 ���� ��� ������ ī�� 2���� �����Ѵ�.
4. ���� ī��� ī�带 �� �÷��̾ �ٽ� ��������, ��ġ�ϴ� ���� ������ ��� �÷��̾��� ī�� ���� ���´�.
5. �� ������ �� ����� ī�尡 ������ ������ �ݺ��Ѵ�. ���� ���� ī�尡 ������ �÷��̾ �¸��Ѵ�.

*/

#define NumberOfPlayer 4

enum CardType
{
	Spade,
	Heart,
	Diamond,
	Clover
};

struct Card
{
	int number;
	CardType suit;
};

struct Player
{
	string name;
	vector<Card> deck;
};

class CardGame
{
public:
	CardGame()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 13; ++j)
			{
				cards.push_back(Card{ j + 1, (CardType)i });
			}
		}
	}

	~CardGame()
	{
		cards.clear();

		for (auto player : players)
		{
			player.deck.clear();
		}
		players.clear();
	}

	void AddPlayer(string name)
	{
		vector<Card> deck;
		players.push_back(Player{ name, deck });
	}

	void PlayGame()
	{
		InitGame();

		int playCount = 1;

		cout << "������ �����մϴ�." << endl;
		cout << "�̹� ������ �����ڴ� ";
		for (int i = 0; i < players.size(); ++i)
		{
			if (i > 0)
			{
				cout << ", ";
			}

			cout << players[i].name;
		}
		cout << "�Դϴ�." << endl << endl;

		while (!IsPlayersDeckEmpty())
		{
			vector<Card> takeCards = TakeCardFromPlayers();
			cout << "[" << playCount++ << "��° ��]" << endl << "�� �÷��̾�� ī�带 �����մϴ�." << endl << endl;
			for (int i = 0; i < players.size(); ++i)
			{
				cout << players[i].name << ": " << SuitName[takeCards[i].suit] << " " << takeCards[i].number << endl;
			}
			cout << endl;

			vector<bool> isMatched = IsMatchedCardsList(takeCards);
			if (IsMatchedCards(isMatched))
			{
				cout << "���ڰ� ��ġ�ϴ� ī�� ���� �����մϴ�. ���� ī��� �ٽ� ������ �������ϴ�." << endl << endl;
				for (int i = 0; i < players.size(); ++i)
				{
					if (isMatched[i])
					{
						players[i].deck.pop_back();
					}

					cout << players[i].name << "�� ���� ī�� ��: " << players[i].deck.size() << endl;
				}
			}
			else
			{
				cout << "��ġ�ϴ� ī�� ���� �����ϴ�. ���� �����ϴ�." << endl;
				for (int i = 0; i < players.size(); ++i)
				{
					mt19937 g((unsigned int)time(NULL) + playCount + i);
					shuffle(players[i].deck.begin(), players[i].deck.end(), g);
				}
			}
			cout << endl;
		}

		vector<string> winners = GetWinner();

		cout << "������ ����Ǿ����ϴ�. ����� ��ǥ�մϴ�." << endl << "���ڴ� ";
		for (int i = 0; i < winners.size(); ++i)
		{
			if (i > 0)
			{
				cout << ", ";
			}

			cout << winners[i];
		}
		cout << "�Դϴ�!" << endl;
	}

private:
	void InitGame()
	{
		if (players.size() != NumberOfPlayer)
		{
			cout << "���� �÷��� �ο���" << NumberOfPlayer << "���Դϴ�." << endl;
			return;
		}

		random_device rd;
		mt19937 g(rd());
		shuffle(cards.begin(), cards.end(), g);

		for (int i = 0; i < players.size(); ++i)
		{
			players[i].deck.clear();

			for (int j = 0; j < cards.size() / players.size(); ++j)
			{
				players[i].deck.push_back(cards[i * (cards.size() / players.size()) + j]);
			}
		}
	}

	vector<Card> TakeCardFromPlayers()
	{
		vector<Card> takeCards;

		for (auto player : players)
		{
			takeCards.push_back(player.deck.back());
		}

		return takeCards;
	}

	vector<bool> IsMatchedCardsList(const vector<Card>& takeCards)
	{
		vector<bool> isMatched(4, false);
		int count = 0;

		for (int i = 0; i < takeCards.size(); ++i)
		{
			for (int j = i + 1; j < takeCards.size(); ++j)
			{
				if (takeCards[i].suit == takeCards[j].suit)
				{
					isMatched[i] = true;
					isMatched[j] = true;
				}
			}
		}

		for (auto isMatch : isMatched)
		{
			count = isMatch ? count + 1 : count;
		}

		while (count % 2 != 0)
		{
			srand((unsigned int)time(NULL));
			int index = rand() % (int)takeCards.size();
			if (isMatched[index])
			{
				isMatched[index] = false;
				count--;
			}
		}

		return isMatched;
	}

	bool IsMatchedCards(const vector<bool>& isMatched)
	{
		for (auto isMatch : isMatched)
		{
			if (isMatch)
			{
				return true;
			}
		}
		return false;
	}

	bool IsPlayersDeckEmpty()
	{
		bool bIsEmpty = false;

		for (auto player : players)
		{
			if (player.deck.empty())
			{
				bIsEmpty = true;
				break;
			}
		}

		return bIsEmpty;
	}

	const vector<string> GetWinner()
	{
		vector<string> winners;

		for (auto player : players)
		{
			if (player.deck.empty())
			{
				winners.push_back(player.name);
			}
		}

		return winners;
	}

private:
	vector<Card> cards;
	vector<Player> players;

	vector<string> SuitName = { "�����̵�", "��Ʈ", "���̾Ƹ��", "Ŭ�ι�" };
};
