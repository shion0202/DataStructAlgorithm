#pragma once
#include "URLMapping.h"

void URLMapping::Insert(const string& originalURL, const string& shortURL)
{
	urlMap[shortURL] = originalURL;
}

const string& URLMapping::Find(const string& shortURL)
{
	auto it = urlMap.find(shortURL);
	if (it != urlMap.end())
	{
		return it->second;
	}
	else
	{
		throw std::runtime_error("Short URL not found");
	}
}
