#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
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

	void InitGame()
	{
		if (players.size() != NumberOfPlayer)
		{
			cout << "���� �÷��� �ο���" << NumberOfPlayer << "���Դϴ�." << endl;
			return;
		}

		random_shuffle(cards.begin(), cards.end());

		for (int i = 0; i < players.size(); ++i)
		{
			players[i].deck.clear();

			for (int j = 0; j < cards.size() / players.size(); ++j)
			{
				players[i].deck.push_back(cards[i * (cards.size() / players.size()) + j]);
			}
		}
	}

	void PlayGame()
	{
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
			cout << "�� �÷��̾�� ī�带 �����մϴ�." << endl;
			for (int i = 0; i < players.size(); ++i)
			{
				cout << players[i].name << ": " << SuitName[takeCards[i].suit] << " " << takeCards[i].number << endl;
			}
			cout << endl << endl;

			vector<bool> isMatched = IsMatchedCards(takeCards);

			// ���� ī�带 ȸ��
			// ���� ������ �ʱ�ȭ

			break;
		}
	}

	const vector<string>& GetWinner()
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
	vector<Card> TakeCardFromPlayers()
	{
		vector<Card> takeCards;

		for (auto player : players)
		{
			takeCards.push_back(player.deck.back());
		}

		return takeCards;
	}

	vector<bool> IsMatchedCards(const vector<Card>& takeCards)
	{
		vector<bool> isMatched;
		return isMatched;
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

private:
	vector<Card> cards;
	vector<Player> players;

	vector<string> SuitName = { "�����̵�", "��Ʈ", "���̾Ƹ��", "Ŭ�ι�" };
};
