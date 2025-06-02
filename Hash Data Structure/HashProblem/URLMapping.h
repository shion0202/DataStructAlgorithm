#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;

// 원본 URL을 짧은 길이의 단축 URL로 변환하는 사이트를 구현하는 문제

class URLMapping
{
public:
	void Insert(const string& originalURL, const string& shortURL);
	const string& Find(const string& shortURL);

private:
	// Key: 단축 URL, Value: 원본 URL
	unordered_map<string, string> urlMap;
};
