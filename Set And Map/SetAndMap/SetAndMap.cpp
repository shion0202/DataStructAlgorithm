#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include "TreeSet.h"
#include "HashMap.h"
using namespace std;

int main()
{
    set<int> s;
    TreeSet ts;

    for (int i = 0; i < 10; ++i)
    {
        s.insert(i * 10);
        ts.insert(i * 10);
    }

    s.erase(30);
    ts.erase(30);

    cout << *(s.find(10)) << ", " << ts.find(10)->data << endl;
    cout << s.empty() << ", " << ts.empty() << endl;

    s.clear();
    ts.clear();
    cout << s.empty() << ", " << ts.empty() << endl << endl;

    unordered_map<int, int> m(10);
    HashMap<int, int> hm(10);

    cout << "[Empty] " << m.empty() << ", " << hm.empty() << endl;

    for (int i = 0; i < 10; ++i)
    {
        m.insert({i, i * 10});
        hm.insert(i, i * 10);
    }

    cout << "[10] " << m.bucket(10) << ", " << hm.bucket(10) << endl;
    cout << "[Size] " << m.size() << ", " << hm.size() << endl;
    cout << "[Bucket Count] " << m.bucket_count() << ", " << hm.bucket_count() << endl;
    cout << "[Bucket Size] " << m.bucket_size(m.bucket(10)) << ", " << hm.bucket_size(hm.bucket(10)) << endl;

    m.erase(10);
    hm.erase(10);
    cout << "[10] " << m[10] << ", " << hm[10] << endl;
}
