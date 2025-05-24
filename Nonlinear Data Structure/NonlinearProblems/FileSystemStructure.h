#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

// 디렉터리 이동, 파일 및 디렉터리 검색, 추가, 목록 출력 등의 기능을 지원하는 파일 시스템 자료 구조를 N-항 트리를 이용하여 구현하는 문제

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