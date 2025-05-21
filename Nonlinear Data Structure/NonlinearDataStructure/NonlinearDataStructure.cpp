#include <iostream>
#include "OrganizationTree.h"
#include "BinarySearchTree.h"
#include "MedianHeap.h"
#include "MyPriorityQueue.h"
#include "MyGraph.h"
using namespace std;

void CreateOrganizationTree()
{
    auto tree = OrganizationTree::CreateTree("사장");

    tree.AddSubordinate("사장", "부사장");
    tree.AddSubordinate("부사장", "IT팀장");
    tree.AddSubordinate("부사장", "마케팅팀장");
    tree.AddSubordinate("IT팀장", "보안팀장");
    tree.AddSubordinate("IT팀장", "앱개발팀장");
    tree.AddSubordinate("마케팅팀장", "물류팀장");
    tree.AddSubordinate("마케팅팀장", "홍보팀장");
    cout << endl;

    tree.PreOrder(tree.root);
    cout << endl;
    tree.InOrder(tree.root);
    cout << endl;
    tree.PostOrder(tree.root);
    cout << endl;

    tree.AddSubordinate("부사장", "신규사업팀장");
    tree.AddSubordinate("사장", "신규사업팀장");
    tree.AddSubordinate("신규사업팀장", "신규사업팀");
    cout << endl;

    tree.LevelOrder(tree.root);
}
void CreateMyBST()
{
    MyBST newBST;
    newBST.Insert(12);
    newBST.Insert(10);
    newBST.Insert(20);
    newBST.Insert(8);
    newBST.Insert(11);
    newBST.Insert(15);
    newBST.Insert(28);
    newBST.Insert(4);
    newBST.Insert(2);

    // BST의 모든 원소가 오름차순으로 출력
    cout << "중위 순회: ";
    newBST.InOrder();
    cout << endl;

    newBST.DeleteNode(12);
    cout << "12를 삭제한 후 중위 순회: ";
    newBST.InOrder();
    cout << endl << endl;

    if (newBST.Find(12))
    {
        cout << "해당 값이 트리에 존재합니다." << endl;
    }
    else
    {
        cout << "해당 값이 트리에 존재하지 않습니다." << endl;
    }
}
void CreateMedianHeap()
{
    MedianHeap median;

    median.Insert(1);
    cout << "중앙 값: " << median.Get() << endl;

    median.Insert(5);
    cout << "중앙 값: " << median.Get() << endl;

    median.Insert(2);
    cout << "중앙 값: " << median.Get() << endl;

    median.Insert(10);
    cout << "중앙 값: " << median.Get() << endl;

    median.Insert(40);
    cout << "중앙 값: " << median.Get() << endl;
}
void CreateMyPriorityQueue()
{
    MyPrioirtyQueue pq;
    pq.Push(10);
    pq.Push(1);
    pq.Push(2);
    pq.Push(3);
    pq.Push(15);
    pq.Push(20);
    cout << "가장 큰 값: " << pq.Top() << ", 노드 개수: " << pq.Size() << endl;

    pq.Pop();
    pq.Pop();
    cout << "가장 큰 값: " << pq.Top() << ", 노드 개수: " << pq.Size() << endl;
}
void CreateGraph()
{
    MyListGraph graph(6);
    graph.AddEdge(City::SEOUL, City::DAEGU, 2500);
	graph.AddEdge(City::SEOUL, City::INCHEON, 1000);
	graph.AddEdge(City::SEOUL, City::BUSAN, 4000);
	graph.AddEdge(City::INCHEON, City::BUSAN, 3000);
	graph.AddEdge(City::INCHEON, City::DAEGU, 2000);
	graph.AddEdge(City::BUSAN, City::POHANG, 1500);
	graph.AddEdge(City::POHANG, City::DAEGU, 1000);
	graph.AddEdge(City::POHANG, City::DAEJEON, 2000);
	graph.AddEdge(City::DAEGU, City::DAEJEON, 3000);

	graph.AddEdge(City::DAEGU, City::BUSAN, 1500);
	graph.RemoveEdge(City::DAEGU, City::BUSAN);
}

int main()
{
    CreateGraph();
}
