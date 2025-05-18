#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

// 플레이어에게 랜덤한 카드를 분배하고, 각 플레이어가 제시한 카드의 모양을 비교하여 일치하는 카드 쌍을 제거하는 게임을 구현하는 문제

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
		// 카드 목록을 초기화
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
	// 플레이어에게 랜덤한 카드를 분배하는 초기화 함수
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

	// 플레이어가 제시한 카드를 가져오는 함수
	vector<Card> TakeCardFromPlayers()
	{
		vector<Card> takeCards;

		for (auto player : players)
		{
			takeCards.push_back(player.deck.back());
		}

		return takeCards;
	}

	// 카드들을 비교하여 일치하는 카드 쌍을 제거하는 함수
	// 카드 모양만을 비교하는 방식으로 구현한 상태
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

	// 카드 쌍의 일치 여부를 확인하는 함수
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

	// 플레이어의 덱이 비어있는지 확인하는 함수
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

	// 플레이어의 덱이 비어있는지 확인하여 승자를 반환하는 함수
	// 승자가 여러 명일 수 있으므로 벡터로 반환
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
