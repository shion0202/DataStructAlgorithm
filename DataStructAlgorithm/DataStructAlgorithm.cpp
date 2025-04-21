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
		"�巡�� ����", "���� ���� ��", "���", "������"
	};

	CardGame NewCardGame;

	for (auto player : players)
	{
		NewCardGame.AddPlayer(player);
	}

	NewCardGame.PlayGame();
}
