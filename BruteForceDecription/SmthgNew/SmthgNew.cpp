#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <filesystem>
#include <thread>
#include <mutex>
#include <list>

#include <windows.h>
#include "bruteforce.h"


#include "openssl/evp.h"
#include <openssl/aes.h>
#include "openssl/sha.h"
#include "openssl/md5.h"
#include "SmthgNew.h"

unsigned char key[EVP_MAX_KEY_LENGTH];
unsigned char iv[EVP_MAX_IV_LENGTH];


std::mutex mut;

void ReadFile(const std::string& filePath, std::vector<unsigned char>& buf)
{
	std::basic_fstream<unsigned char> fileStream(filePath, std::ios::binary | std::fstream::in);

	if (!fileStream.is_open())
	{
		throw std::runtime_error("Can not open file " + filePath);
	}

	buf.clear();
	buf.insert(buf.begin(), std::istreambuf_iterator<unsigned char>(fileStream), std::istreambuf_iterator<unsigned char>());

	fileStream.close();
}

void ExtractHash(std::vector<unsigned char>& hashBuf, std::vector<unsigned char>& buf) {

	hashBuf.clear();
	for (size_t i = SHA256_DIGEST_LENGTH; i > 0; --i) {
		hashBuf.push_back(buf[buf.size() - i]);
	}
}

void WriteFile(const std::string& filePath, const std::vector<unsigned char>& buf)
{
	std::basic_ofstream<unsigned char> fileStream(filePath, std::ios::binary);
	fileStream.write(&buf[0], buf.size());
	fileStream.close();
}

void PasswordToKey(std::string& password)
{
	OpenSSL_add_all_digests();
	const EVP_MD* dgst = EVP_get_digestbyname("md5");
	if (!dgst)
	{
		throw std::runtime_error("no such digest");
	}

	const unsigned char* salt = NULL;
	if (!EVP_BytesToKey(EVP_aes_128_cbc(), EVP_md5(), salt,
		reinterpret_cast<unsigned char*>(&password[0]),
		password.size(), 1, key, iv))
	{
		throw std::runtime_error("EVP_BytesToKey failed");
	}
}

bool DecryptAes(const std::vector<unsigned char> cryptedText, std::vector<unsigned char>& decryptedText)
{

	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
	{
		throw std::runtime_error("DecryptInit error");
	}

	std::vector<unsigned char> decryptedTextBuf(cryptedText.size() - SHA256_DIGEST_LENGTH);
	int decryptedTextSize = 0;
	if (!EVP_DecryptUpdate(ctx, &decryptedTextBuf[0], &decryptedTextSize, &cryptedText[0], cryptedText.size() - SHA256_DIGEST_LENGTH)) {
		EVP_CIPHER_CTX_free(ctx);
		throw std::runtime_error("Decrypt error");
	}


	int lastPartLen = 0;
	if (!EVP_DecryptFinal_ex(ctx, &decryptedTextBuf[0] + decryptedTextSize, &lastPartLen)) {
		EVP_CIPHER_CTX_free(ctx);
		return false;
	}


	decryptedTextSize += lastPartLen;
	decryptedTextBuf.erase(decryptedTextBuf.begin() + decryptedTextSize, decryptedTextBuf.end());

	decryptedText.swap(decryptedTextBuf);

	EVP_CIPHER_CTX_free(ctx);
	return true;
}

void CalculateHash(std::vector<unsigned char>& hash, const std::vector<unsigned char>& decryptedText)
{

	std::vector<unsigned char> hashTmp(SHA256_DIGEST_LENGTH);

	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, &decryptedText[0], decryptedText.size());
	SHA256_Final(&hashTmp[0], &sha256);

	hash.swap(hashTmp);
}

void CompareHash(std::vector<unsigned char>& sourceHash, std::vector<unsigned char>& decryptedText, std::string pass, bool* isDecOK)
{
	std::vector<unsigned char> hash;
	CalculateHash(hash, decryptedText);
	if (hash == sourceHash) {
		WriteFile("C:/chipher_text_brute_forceD", decryptedText);
		std::cout << "Correct password is " << pass << std::endl;
		*isDecOK = true;
	}
};

void Decrypt(std::vector<unsigned char>& chipherText, std::vector<unsigned char>& sourceHash, std::vector<std::string>* containerPass, class GenPasswords* c_getPass, bool* isDecOK) 
{
	std::vector<unsigned char> plainText;
	std::vector<unsigned char> hashBuf;
	std::string pass;

	for (; *isDecOK != true;) {
		mut.lock();
		c_getPass->Gen(containerPass);
		std::vector<std::string>::iterator i_Pass = containerPass->begin();
		i_Pass = containerPass->begin();

		for (; *isDecOK != true;)
		{

			pass = *i_Pass;
			++i_Pass;
			PasswordToKey(pass);

			if ((DecryptAes(chipherText, plainText) != false))
			{
				CompareHash(sourceHash, plainText, pass, isDecOK);
			}
			if (i_Pass == containerPass->end())
			{
				mut.unlock();
				break;
			}
		}
	}
	mut.unlock();
}