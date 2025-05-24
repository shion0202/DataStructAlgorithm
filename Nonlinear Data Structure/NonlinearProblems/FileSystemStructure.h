#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

// ���͸� �̵�, ���� �� ���͸� �˻�, �߰�, ��� ��� ���� ����� �����ϴ� ���� �ý��� �ڷ� ������ N-�� Ʈ���� �̿��Ͽ� �����ϴ� ����

struct FSNode
{
	string name;
	bool isFile;
	FSNode* parent;
	vector<FSNode*> children;
};

class FileSystemTree
{
public:
	FileSystemTree();
	~FileSystemTree();

	FSNode* Find(string path);
	void Make(string name, bool isFile);
	void Remove(string path);
	void ForceRemoveAll();
	void List();
	void ChangeDirectory(string path);
	
private:
	void ForceRemove(FSNode* node);

private:
	FSNode* root;
	FSNode* currentDirectory;
};