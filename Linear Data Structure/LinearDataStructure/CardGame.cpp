#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

/*

[ 카드 게임 시뮬레이션 ]
주어진 상황을 분석하고, 가장 적합한 자료 구조를 선택하여 카드 게임을 구현하는 문제

1. 4명의 플레이어가 있고, 각각 임의의 카드 13장을 가지고 게임을 시작한다.
2. 각 플레이어의 카드 중 임의의 카드 1장을 선택한다.
3. 4장의 카드를 비교하여, 중복되는 카드 쌍을 제거한다. 이 때 3장의 카드가 같을 경우 임의의 카드 2장을 제거한다.
4. 남은 카드는 카드를 낸 플레이어가 다시 가져가며, 일치하는 쌍이 없었을 경우 플레이어의 카드 덱을 섞는다.
5. 이 과정을 한 사람의 카드가 없어질 때까지 반복한다. 가장 먼저 카드가 없어진 플레이어가 승리한다.

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

		cout << "게임을 시작합니다." << endl;
		cout << "이번 게임의 참여자는 ";
		for (int i = 0; i < players.size(); ++i)
		{
			if (i > 0)
			{
				cout << ", ";
			}

			cout << players[i].name;
		}
		cout << "입니다." << endl << endl;

		while (!IsPlayersDeckEmpty())
		{
			vector<Card> takeCards = TakeCardFromPlayers();
			cout << "[" << playCount++ << "번째 턴]" << endl << "각 플레이어는 카드를 제시합니다." << endl << endl;
			for (int i = 0; i < players.size(); ++i)
			{
				cout << players[i].name << ": " << SuitName[takeCards[i].suit] << " " << takeCards[i].number << endl;
			}
			cout << endl;

			vector<bool> isMatched = IsMatchedCardsList(takeCards);
			if (IsMatchedCards(isMatched))
			{
				cout << "문자가 일치하는 카드 쌍을 제거합니다. 남은 카드는 다시 덱으로 가져갑니다." << endl << endl;
				for (int i = 0; i < players.size(); ++i)
				{
					if (isMatched[i])
					{
						players[i].deck.pop_back();
					}

					cout << players[i].name << "의 남은 카드 수: " << players[i].deck.size() << endl;
				}
			}
			else
			{
				cout << "일치하는 카드 쌍이 없습니다. 덱을 섞습니다." << endl;
				for (int i = 0; i < players.size(); ++i)
				{
					mt19937 g((unsigned int)time(NULL) + playCount + i);
					shuffle(players[i].deck.begin(), players[i].deck.end(), g);
				}
			}
			cout << endl;
		}

		vector<string> winners = GetWinner();

		cout << "게임이 종료되었습니다. 결과를 발표합니다." << endl << "승자는 ";
		for (int i = 0; i < winners.size(); ++i)
		{
			if (i > 0)
			{
				cout << ", ";
			}

			cout << winners[i];
		}
		cout << "입니다!" << endl;
	}

private:
	void InitGame()
	{
		if (players.size() != NumberOfPlayer)
		{
			cout << "게임 플레이 인원은" << NumberOfPlayer << "인입니다." << endl;
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

	vector<string> SuitName = { "스페이드", "하트", "다이아몬드", "클로버" };
};
