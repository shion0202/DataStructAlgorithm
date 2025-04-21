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
		"������", "������", "������", "���ȯ"
	};

	CardGame NewCardGame;

	for (auto player : players)
	{
		NewCardGame.AddPlayer(player);
	}

	NewCardGame.InitGame();
	NewCardGame.PlayGame();

	//vector<string> winners = NewCardGame.GetWinner();

	//cout << "���ڴ� ";
	//for (int i = 0; i < winners.size(); ++i)
	//{
	//	if (i > 0)
	//	{
	//		cout << ", ";
	//	}

	//	cout << winners[i];
	//}
	//cout << "�Դϴ�!";
}
