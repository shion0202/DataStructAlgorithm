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

class MyMedianHeap
{
public:
    // 값의 삽입과 중앙값 반환이 필요
    void Insert(const int& value);
    float GetMedian();

public:
    // 중앙값을 구하기 위한 최대, 최소 힙
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
};
