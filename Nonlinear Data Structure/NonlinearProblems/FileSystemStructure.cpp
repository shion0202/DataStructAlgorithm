#pragma once
#include "FileSystemStructure.h"

FileSystemTree::FileSystemTree()
{
	root = new FSNode{ "C:", false, nullptr, {} };
	currentDirectory = root;
}

FileSystemTree::~FileSystemTree()
{
	ForceRemoveAll();

	delete root;
	root = nullptr;
}

FSNode* FileSystemTree::Find(string path)
{
	// '/'로 시작하면 절대 경로, 아닐 경우 상대 경로
	vector<string> tokens;
	stringstream ss(path);
	string token;

	while (getline(ss, token, '/'))
	{
		tokens.push_back(token);
	}

	FSNode* currentNode;
	if (tokens[0].empty())
	{
		// 절대 경로
		currentNode = root;
	}
	else
	{
		// 상대 경로
		currentNode = currentDirectory;
	}

	bool isFound = false;
	for (const string& token : tokens)
	{
		if (token.empty())
		{
			continue;
		}

		// 현재 디렉터리 유지
		if (!token.compare("."))
		{
			isFound = true;
			continue;
		}

		// 상위 디렉터리로 이동
		if (!token.compare(".."))
		{
			if (currentNode->parent)
			{
				currentNode = currentNode->parent;
				isFound = true;
				continue;
			}
			else
			{
				cout << "Can't go up from root directory." << endl << endl;
				return nullptr;
			}
		}

		for (FSNode* child : currentNode->children)
		{
			if (child->name.compare(token) == 0)
			{
				currentNode = child;
				isFound = true;
				break;
			}
		}

		if (isFound)
		{
			continue;
		}
		else
		{
			cout << "Directory or file not found: " << path << endl << endl;
			return nullptr;
		}
	}

	return currentNode;
}

void FileSystemTree::Make(string name, bool isFile)
{
	FSNode* currentNode = nullptr;
	
	if (name.substr(0, 1).compare("/"))
	{
		// 상대 경로일 경우 바로 생성
		currentNode = currentDirectory;
	}
	else
	{
		// 절대 경로일 경우 Find가 필요
		int pos = name.rfind('/');
		string directoryPath = name.substr(0, pos);
		name = name.substr(pos + 1);
		currentNode = directoryPath.empty() ? root : Find(directoryPath);
	}
	
	FSNode* newNode = new FSNode{ name, isFile, currentNode, {} };
	currentNode->children.push_back(newNode);
}

void FileSystemTree::Remove(string path)
{
	FSNode* currentNode = Find(path);
	if (!currentNode)
	{
		return;
	}
	
	if (!currentNode->isFile && !currentNode->children.empty())
	{
		cout << "Directory not empty: " << path << endl << endl;
		return;
	}

	currentNode->parent->children.erase(
		remove(currentNode->parent->children.begin(), currentNode->parent->children.end(), currentNode),
		currentNode->parent->children.end()
	);
	delete currentNode;
	return;
}

void FileSystemTree::ForceRemoveAll()
{
	for (FSNode* child : root->children)
	{
		ForceRemove(child);
	}
	root->children.clear();
}

void FileSystemTree::List()
{
	queue<FSNode*> q;
	int size;
	q.push(root);

	while (!q.empty())
	{
		size = q.size();
		for (int i = 0; i < size; ++i)
		{
			FSNode* currentNode = q.front();
			q.pop();

			for (FSNode* child : currentNode->children)
			{
				q.push(child);
			}

			if (i > 0)
			{
				cout << ", ";
			}
			cout << currentNode->name;
		}
		cout << endl;
	}
	cout << endl;
}

void FileSystemTree::ChangeDirectory(string path)
{
	FSNode* targetDirectory = Find(path);
	if (targetDirectory->isFile)
	{
		return;
	}

	currentDirectory = targetDirectory;
}

void FileSystemTree::ForceRemove(FSNode* node)
{
	for (FSNode* child : node->children)
	{
		ForceRemove(child);
	}

	delete node;
}
