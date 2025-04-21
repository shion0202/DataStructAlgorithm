#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <forward_list>
#include <list>
#include <algorithm>
#include "CardGame.cpp"
using namespace std;

int main()
{
	vector<string> players = {
		"정수용", "전태훈", "박정민", "노승환"
	};

	CardGame NewCardGame;

	for (auto player : players)
	{
		NewCardGame.AddPlayer(player);
	}

	NewCardGame.InitGame();
	NewCardGame.PlayGame();

	//vector<string> winners = NewCardGame.GetWinner();

	//cout << "승자는 ";
	//for (int i = 0; i < winners.size(); ++i)
	//{
	//	if (i > 0)
	//	{
	//		cout << ", ";
	//	}

	//	cout << winners[i];
	//}
	//cout << "입니다!";
}
