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

    // Rule 1: 루트는 검정
    if (node == tree.root && node->isRed)
    {
        cout << "Root가 Red: " << node->data << endl;
        return false;
    }

    // Rule 3: RED 노드의 자식은 모두 BLACK
    if (node->isRed)
    {
        if (node->left->isRed || node->right->isRed)
        {
            cout << "Double Red 위반: " << node->data << endl;
            return false;
        }
    }

    // Rule 4: 모든 리프에서 블랙 높이 동일
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
        cout << "블랙 높이 불일치: " << node->data << endl;
        return false;
    }

    return CheckRBProperties(node->left, tree) && CheckRBProperties(node->right, tree);
}
void TestCase1()
{
    cout << "=== 테스트 케이스 1: 기본 동작 ===" << endl;
    MyRBTree tree;

    // 삽입 테스트
    vector<int> inserts = { 10, 20, 30, 15, 25, 35, 5, 1 };
    for (int num : inserts)
    {
        tree.Insert(num);
        if (!CheckRBProperties(tree.root, tree))
        {
            cout << "삽입 실패: " << num << endl;
            return;
        }
    }
    tree.PrintTree();
    cout << "삽입 테스트 통과!" << endl;

    // 삭제 테스트
    vector<int> deletes = { 20, 5 };
    for (int num : deletes)
    {
        tree.DeleteNode(num);
        if (!CheckRBProperties(tree.root, tree))
        {
            cout << "삭제 실패: " << num << endl;
            return;
        }
    }
    tree.PrintTree();
    cout << "삭제 테스트 통과!" << endl;
}
void TestCase2()
{
    cout << "\n=== 테스트 케이스 2: 극단적 경우 ===" << endl;
    MyRBTree tree;

    // 루트 삭제 테스트
    tree.Insert(100);
    tree.DeleteNode(100);
    if (tree.root != tree.NIL)
    {
        cout << "루트 삭제 실패!" << endl;
        return;
    }
    cout << "루트 삭제 테스트 통과!" << endl;

    // 역순 삽입 테스트
    for (int i = 10; i >= 1; i--) tree.Insert(i);
    if (!CheckRBProperties(tree.root, tree))
    {
        cout << "역순 삽입 실패" << endl;
        return;
    }
    cout << "역순 삽입 테스트 통과!" << endl;
}
void TestCase3()
{
    cout << "\n=== 테스트 케이스 3: 랜덤 테스트 ===" << endl;
    MyRBTree tree;
    vector<int> randomDatas;
    srand(time(nullptr));

    // 1000개 랜덤 연산
    for (int i = 0; i < 1000; i++) {
        int num = rand() % 500;
        if (rand() % 2 == 0) {
            cout << "트리 삽입" << endl;
            tree.Insert(num);
            randomDatas.push_back(num);
        }
        else
        {
            if (randomDatas.empty()) continue;
            cout << "트리 삭제" << endl;
            num = rand() % randomDatas.size();
            tree.DeleteNode(randomDatas[num]);
        }

        if (!CheckRBProperties(tree.root, tree))
        {
            cout << "랜덤 테스트 실패: " << randomDatas[num] << endl;
            return;
        }
    }
    cout << "랜덤 테스트 통과!" << endl;
}

int main()
{
    TestCase1();
    TestCase2();
    TestCase3();
}
