#include "HashTable.h"

template<>
inline vector<unsigned char> HashKey(const string& key)
{
	// ���ڿ� Ÿ�� Ư��ȭ
	return vector<unsigned char>(
		reinterpret_cast<const unsigned char*>(key.c_str()),
		reinterpret_cast<const unsigned char*>(key.c_str() + key.size())
	);
}
