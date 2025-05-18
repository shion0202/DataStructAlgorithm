#include <iostream>
#include "OrganizationTree.h"
#include "BinarySearchTree.h"
#include "MedianHeap.h"
#include "MyPriorityQueue.h"
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

int main()
{
    
}
