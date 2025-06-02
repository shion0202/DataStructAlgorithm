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
		cout << "1�� �ؽ� ���̺��� " << key << "��(��) ã�ҽ��ϴ�." << endl;
		return fData.begin() + fValue;
	}

	auto sValue = sHash(key);
	if (sData[sValue] == key)
	{
		cout << "2�� �ؽ� ���̺��� " << key << "��(��) ã�ҽ��ϴ�." << endl;
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
		cout << key << "��(��) �����߽��ϴ�." << endl;
	}
	else
	{
		cout << key << "��(��) ã�� �� �����ϴ�." << endl;
	}
}

void CuckooHashMap::Insert(int key)
{
	Insert_Impl(key, 0, 1);
}

void CuckooHashMap::Print()
{
	cout << "1�� �ؽ� ���̺�: ";
	for (int i = 0; i < size; ++i)
	{
		if (fData[i] != -1)
			cout << fData[i] << " ";
		else
			cout << "- ";
	}
	cout << endl;

	cout << "2�� �ؽ� ���̺�: ";
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
		cout << "���̺��� ���� á���ϴ�. " << key << "��(��) ������ �� �����ϴ�." << endl;
		return;
	}

	// 1�� �ؽ� ���̺�� 2�� �ؽ� ���̺��� ����
	if (table == 1)
	{
		int hash = fHash(key);
		if (fData[hash] == -1)
		{
			cout << "1�� �ؽ� ���̺� " << key << "��(��) �����߽��ϴ�." << endl;
			fData[hash] = key;
		}
		else
		{
			// �浹�� �߻��� ���, ���� ���� 2�� �ؽ� ���̺�� �̵�
			int old = fData[hash];
			fData[hash] = key;
			cout << "1�� �ؽ� ���̺� �浹 �߻�. " << old << "��(��) " << key << "���� ��ü�߽��ϴ�." << endl;
			Insert_Impl(old, count + 1, 2);
		}
	}
	else
	{
		int hash = sHash(key);
		if (sData[hash] == -1)
		{
			cout << "2�� �ؽ� ���̺� " << key << "��(��) �����߽��ϴ�." << endl;
			sData[hash] = key;
		}
		else
		{
			// �浹�� �߻��� ���, ���� ���� 1�� �ؽ� ���̺�� �̵�
			int old = sData[hash];
			sData[hash] = key;
			cout << "2�� �ؽ� ���̺� �浹 �߻�. " << old << "��(��) " << key << "���� ��ü�߽��ϴ�." << endl;
			Insert_Impl(old, count + 1, 1);
		}
	}
}
