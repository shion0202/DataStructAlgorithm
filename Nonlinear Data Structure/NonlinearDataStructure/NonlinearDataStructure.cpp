#include <iostream>
#include "OrganizationTree.h"
#include "BinarySearchTree.h"
#include "MedianHeap.h"
#include "MyPriorityQueue.h"
#include "MyGraph.h"
#include "RedBlackTree.h"
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
    cout << endl;
    graph.BFS();
    graph.DFS();

	graph.RemoveEdge(City::DAEGU, City::BUSAN);
    cout << endl;
    graph.BFS();
    graph.DFS();
}

bool CheckRBProperties(RBNode* node, MyRBTree& tree)
{
    if (node == tree.NIL)
        return true;

    // Rule 1: ��Ʈ�� ����
    if (node == tree.root && node->isRed)
    {
        cout << "Root�� Red: " << node->data << endl;
        return false;
    }

    // Rule 3: RED ����� �ڽ��� ��� BLACK
    if (node->isRed)
    {
        if (node->left->isRed || node->right->isRed)
        {
            cout << "Double Red ����: " << node->data << endl;
            return false;
        }
    }

    // Rule 4: ��� �������� �� ���� ����
    int leftBlack = 0;
    RBNode* left = node;
    while (left != tree.NIL)
    {
        if (!left->isRed) leftBlack++;
        left = left->left;
    }

    int rightBlack = 0;
    RBNode* right = node;
    while (right != tree.NIL)
    {
        if (!right->isRed) rightBlack++;
        right = right->right;
    }

    if (leftBlack != rightBlack)
    {
        cout << "�� ���� ����ġ: " << node->data << endl;
        return false;
    }

    return CheckRBProperties(node->left, tree) && CheckRBProperties(node->right, tree);
}
void TestCase1()
{
    cout << "=== �׽�Ʈ ���̽� 1: �⺻ ���� ===" << endl;
    MyRBTree tree;

    // ���� �׽�Ʈ
    vector<int> inserts = { 10, 20, 30, 15, 25, 35, 5, 1 };
    for (int num : inserts)
    {
        tree.Insert(num);
        if (!CheckRBProperties(tree.root, tree))
        {
            cout << "���� ����: " << num << endl;
            return;
        }
    }
    tree.PrintTree();
    cout << "���� �׽�Ʈ ���!" << endl;

    // ���� �׽�Ʈ
    vector<int> deletes = { 20, 5 };
    for (int num : deletes)
    {
        tree.DeleteNode(num);
        if (!CheckRBProperties(tree.root, tree))
        {
            cout << "���� ����: " << num << endl;
            return;
        }
    }
    tree.PrintTree();
    cout << "���� �׽�Ʈ ���!" << endl;
}
void TestCase2()
{
    cout << "\n=== �׽�Ʈ ���̽� 2: �ش��� ��� ===" << endl;
    MyRBTree tree;

    // ��Ʈ ���� �׽�Ʈ
    tree.Insert(100);
    tree.DeleteNode(100);
    if (tree.root != tree.NIL)
    {
        cout << "��Ʈ ���� ����!" << endl;
        return;
    }
    cout << "��Ʈ ���� �׽�Ʈ ���!" << endl;

    // ���� ���� �׽�Ʈ
    for (int i = 10; i >= 1; i--) tree.Insert(i);
    if (!CheckRBProperties(tree.root, tree))
    {
        cout << "���� ���� ����" << endl;
        return;
    }
    cout << "���� ���� �׽�Ʈ ���!" << endl;
}
void TestCase3()
{
    cout << "\n=== �׽�Ʈ ���̽� 3: ���� �׽�Ʈ ===" << endl;
    MyRBTree tree;
    vector<int> randomDatas;
    srand(time(nullptr));

    // 1000�� ���� ����
    for (int i = 0; i < 1000; i++) {
        int num = rand() % 500;
        if (rand() % 2 == 0) {
            cout << "Ʈ�� ����" << endl;
            tree.Insert(num);
            randomDatas.push_back(num);
        }
        else
        {
            if (randomDatas.empty()) continue;
            cout << "Ʈ�� ����" << endl;
            num = rand() % randomDatas.size();
            tree.DeleteNode(randomDatas[num]);
        }

        if (!CheckRBProperties(tree.root, tree))
        {
            cout << "���� �׽�Ʈ ����: " << randomDatas[num] << endl;
            return;
        }
    }
    cout << "���� �׽�Ʈ ���!" << endl;
}

int main()
{
    TestCase1();
    TestCase2();
    TestCase3();
}
