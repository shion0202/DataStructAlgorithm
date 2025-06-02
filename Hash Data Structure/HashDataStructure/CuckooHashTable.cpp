#pragma once
#include "CuckooHashTable.h"

CuckooHashMap::CuckooHashMap(int n) : size(n)
{
	fData = vector<int>(size, -1);
	sData = vector<int>(size, -1);
}

vector<int>::iterator CuckooHashMap::Lookup(int key)
{
	auto fValue = fHash(key);
	if (fData[fValue] == key)
	{
		cout << "1차 해시 테이블에서 " << key << "을(를) 찾았습니다." << endl;
		return fData.begin() + fValue;
	}

	auto sValue = sHash(key);
	if (sData[sValue] == key)
	{
		cout << "2차 해시 테이블에서 " << key << "을(를) 찾았습니다." << endl;
		return sData.begin() + sValue;
	}

	return fData.end();
}

void CuckooHashMap::Erase(int key)
{
	auto pos = Lookup(key);
	if (pos != fData.end())
	{
		*pos = -1;
		cout << key << "을(를) 삭제했습니다." << endl;
	}
	else
	{
		cout << key << "을(를) 찾을 수 없습니다." << endl;
	}
}

void CuckooHashMap::Insert(int key)
{
	Insert_Impl(key, 0, 1);
}

void CuckooHashMap::Print()
{
	cout << "1차 해시 테이블: ";
	for (int i = 0; i < size; ++i)
	{
		if (fData[i] != -1)
			cout << fData[i] << " ";
		else
			cout << "- ";
	}
	cout << endl;

	cout << "2차 해시 테이블: ";
	for (int i = 0; i < size; ++i)
	{
		if (sData[i] != -1)
			cout << sData[i] << " ";
		else
			cout << "- ";
	}
	cout << endl;
}

void CuckooHashMap::Insert_Impl(int key, int count, int table)
{
	if (count >= size)
	{
		cout << "테이블이 가득 찼습니다. " << key << "을(를) 삽입할 수 없습니다." << endl;
		return;
	}

	// 1차 해시 테이블과 2차 해시 테이블을 구분
	if (table == 1)
	{
		int hash = fHash(key);
		if (fData[hash] == -1)
		{
			cout << "1차 해시 테이블에 " << key << "을(를) 삽입했습니다." << endl;
			fData[hash] = key;
		}
		else
		{
			// 충돌이 발생할 경우, 기존 값을 2차 해시 테이블로 이동
			int old = fData[hash];
			fData[hash] = key;
			cout << "1차 해시 테이블에 충돌 발생. " << old << "을(를) " << key << "으로 대체했습니다." << endl;
			Insert_Impl(old, count + 1, 2);
		}
	}
	else
	{
		int hash = sHash(key);
		if (sData[hash] == -1)
		{
			cout << "2차 해시 테이블에 " << key << "을(를) 삽입했습니다." << endl;
			sData[hash] = key;
		}
		else
		{
			// 충돌이 발생할 경우, 기존 값을 1차 해시 테이블로 이동
			int old = sData[hash];
			sData[hash] = key;
			cout << "2차 해시 테이블에 충돌 발생. " << old << "을(를) " << key << "으로 대체했습니다." << endl;
			Insert_Impl(old, count + 1, 1);
		}
	}
}
