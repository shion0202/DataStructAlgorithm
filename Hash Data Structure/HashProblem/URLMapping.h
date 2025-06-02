#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;

// ���� URL�� ª�� ������ ���� URL�� ��ȯ�ϴ� ����Ʈ�� �����ϴ� ����

class URLMapping
{
public:
	void Insert(const string& originalURL, const string& shortURL);
	const string& Find(const string& shortURL);

private:
	// Key: ���� URL, Value: ���� URL
	unordered_map<string, string> urlMap;
};
