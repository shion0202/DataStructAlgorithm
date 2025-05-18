#pragma once
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class MedianHeap
{
public:
    void Insert(const int& data);
    double Get();

public:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
};