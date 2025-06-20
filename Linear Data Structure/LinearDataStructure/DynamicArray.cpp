#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// 연산자, 복사 생성자, 입출력
template <typename T>
class DynamicArray
{
public:
    DynamicArray(int n)
    {
        this->n = n;
        data = new T[n];
    }

    DynamicArray(const DynamicArray& other)
    {
        n = other.size();
        data = new T[n];
        for (int i = 0; i < n; ++i)
        {
            data[i] = other[i];
        }
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    T& at(int index)
    {
        if (index < n)
        {
            return data[index];
        }
        throw "Index out of range";
    }

    const T& at(int index) const
    {
        if (index < n)
        {
            return data[index];
        }
        throw "Index out of range";
    }

    string to_string(const string& sep = ", ")
    {
        if (n == 0)
        {
            return NULL;
        }

        ostringstream os;
        os << data[0];

        for (int i = 1; i < n; ++i)
        {
            os << sep << data[i];
        }

        return os.str();
    }

    size_t size() { return n; }
    const T& front() { return data[0]; }
    const T& back() { return data[n - 1]; }
    bool empty() { return n == 0; }

    T* begin() { return data; }
    const T* begin() const { return data; }
    T* end() { return data + n; }
    const T* end() const { return data + n; }

    T& operator[](int index)
    {
        return data[index];
    }

    const T& operator[](int index) const
    {
        return data[index];
    }

private:
    T* data;
    size_t n;
};

struct StudentData
{
public:
    string name;
    int number;
};

// 연산자는 링크 과정에서 구현부가 중복 생성될 수 있으므로, inline 사용 또는 헤더 파일을 분리
inline ostream& operator<<(ostream& os, const StudentData& student)
{
    return (os << "[" << student.name << ", " << student.number << "]");
}
