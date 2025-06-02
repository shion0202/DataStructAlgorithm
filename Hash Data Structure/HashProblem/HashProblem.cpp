#include <iostream>
#include "URLMapping.h"
#include "EmailDuplicateCheck.h"
using namespace std;

void ConvertURL()
{
	URLMapping urlMapping;

	urlMapping.Insert("https://www.example.com/long-url", "short1");
	urlMapping.Insert("https://www.example.com/another-long-url", "short2");
	urlMapping.Insert("https://www.example.com/yet-another-long-url", "short3");

	cout << "Find: " << urlMapping.Find("short1") << endl;
	cout << "Find: " << urlMapping.Find("short2") << endl;
	try
	{
		cout << "Find: " << urlMapping.Find("short4") << endl;
	}
	catch (const std::runtime_error& e)
	{
		cout << "Error: " << e.what() << endl;
	}
}
void CheckDuplicateEmail()
{
	BloomFilter bf(100);
	bf.Insert("wjdtndyd345");
	bf.Insert("Kaizer");
	bf.Insert("Shion2020");
	bf.Lookup("Shion2020");
	bf.Lookup("HelloWorld");
	cout << endl;
}

int main()
{
	ConvertURL();
}
