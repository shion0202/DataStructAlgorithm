#include <iostream>
#include "OrganizationTree.h"
#include "BinarySearchTree.h"
#include "MedianHeap.h"
#include "MyPriorityQueue.h"
#include "MyGraph.h"
using namespace std;

void CreateOrganizationTree()
{
    auto tree = OrganizationTree::CreateTree("����");

    tree.AddSubordinate("����", "�λ���");
    tree.AddSubordinate("�λ���", "IT����");
    tree.AddSubordinate("�λ���", "����������");
    tree.AddSubordinate("IT����", "��������");
    tree.AddSubordinate("IT����", "�۰�������");
    tree.AddSubordinate("����������", "��������");
    tree.AddSubordinate("����������", "ȫ������");
    cout << endl;

    tree.PreOrder(tree.root);
    cout << endl;
    tree.InOrder(tree.root);
    cout << endl;
    tree.PostOrder(tree.root);
    cout << endl;

    tree.AddSubordinate("�λ���", "�űԻ������");
    tree.AddSubordinate("����", "�űԻ������");
    tree.AddSubordinate("�űԻ������", "�űԻ����");
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

    // BST�� ��� ���Ұ� ������������ ���
    cout << "���� ��ȸ: ";
    newBST.InOrder();
    cout << endl;

    newBST.DeleteNode(12);
    cout << "12�� ������ �� ���� ��ȸ: ";
    newBST.InOrder();
    cout << endl << endl;

    if (newBST.Find(12))
    {
        cout << "�ش� ���� Ʈ���� �����մϴ�." << endl;
    }
    else
    {
        cout << "�ش� ���� Ʈ���� �������� �ʽ��ϴ�." << endl;
    }
}
void CreateMedianHeap()
{
    MedianHeap median;

    median.Insert(1);
    cout << "�߾� ��: " << median.Get() << endl;

    median.Insert(5);
    cout << "�߾� ��: " << median.Get() << endl;

    median.Insert(2);
    cout << "�߾� ��: " << median.Get() << endl;

    median.Insert(10);
    cout << "�߾� ��: " << median.Get() << endl;

    median.Insert(40);
    cout << "�߾� ��: " << median.Get() << endl;
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
    cout << "���� ū ��: " << pq.Top() << ", ��� ����: " << pq.Size() << endl;

    pq.Pop();
    pq.Pop();
    cout << "���� ū ��: " << pq.Top() << ", ��� ����: " << pq.Size() << endl;
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
