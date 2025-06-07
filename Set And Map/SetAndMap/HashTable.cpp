#include "HashTable.h"

template<>
inline vector<unsigned char> HashKey(const string& key)
{
	// 문자열 타입 특수화
	return vector<unsigned char>(
		reinterpret_cast<const unsigned char*>(key.c_str()),
		reinterpret_cast<const unsigned char*>(key.c_str() + key.size())
	);
}
