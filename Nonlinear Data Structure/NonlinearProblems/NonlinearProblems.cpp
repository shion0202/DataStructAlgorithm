#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>
#include "FileSystemStructure.h"
#include "DataListMergeHeap.h"
using namespace std;

void CreateFileSystemTree()
{
    FileSystemTree fs;
    fs.Make("/Users", false);
    fs.Make("/Users/Suyong", false);
    fs.Make("/Users/user", false);
    fs.Make("/Users/Suyong/document.txt", true);
    fs.ChangeDirectory("/Users/Suyong");
    fs.Make("image.png", true);
    fs.List();

    fs.ChangeDirectory("../..");
    fs.Make("Downloads", false);
    fs.Make("/Users/user/test.txt", true);
    fs.Remove("/Users/Suyong/document.txt");
    fs.Remove("/Users/user");
    fs.List();
}
void CreateMergeHeap()
{
    vector<vector<int>> arrays;
    for (int i = 0; i < 3; ++i)
    {
        vector<int> array;
        for (int j = 0; j < 10; ++j)
        {
            array.push_back(rand() % 100 + 1);
        }
        arrays.push_back(array);
    }

	MergeHeap mergeHeap(arrays);
    while (true)
    {
		HeapNode minData = mergeHeap.GetMinData();
		if (minData.arrayIndex < 0)
		{
			break;
		}
		cout << minData.arrayIndex << "번째 배열의 " << minData.elementIndex << "번째 원소: "
			<< minData.data << endl;
    }
    cout << endl;
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    CreateMergeHeap();
}
