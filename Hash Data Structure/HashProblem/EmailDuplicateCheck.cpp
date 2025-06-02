#pragma once
#include "EmailDuplicateCheck.h"
#include "openssl/md5.h"
#include "openssl/evp.h"

BloomFilter::BloomFilter(int size) : nBits(size)
{
	data = vector<bool>(nBits, false);
}

void BloomFilter::Lookup(string key)
{
	unsigned char* hash = Hash(key);

	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		if (!data[(hash[i] % nBits)])
		{
			cout << "Not Found: " << key << endl;
			return;
		}
	}

	cout << "Found: " << key << endl;
}

void BloomFilter::Insert(string key)
{
	unsigned char* hash = Hash(key);

	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		data[(hash[i] % nBits)] = true;
	}

	for (auto ele : data)
	{
		cout << ele;
	}
	cout << endl;
}

unsigned char* BloomFilter::Hash(string key)
{
	unsigned char digest[MD5_DIGEST_LENGTH];
	unsigned int length;
	EVP_MD_CTX* ctx = EVP_MD_CTX_new();

	EVP_DigestInit_ex(ctx, EVP_md5(), NULL);
	EVP_DigestUpdate(ctx, key.c_str(), key.length());
	EVP_DigestFinal_ex(ctx, digest, &length);

	return digest;
}
