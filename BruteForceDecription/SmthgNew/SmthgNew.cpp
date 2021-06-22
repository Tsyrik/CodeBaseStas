#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <filesystem>
#include <thread>

#include "openssl/evp.h"
#include <openssl/aes.h>
#include "openssl/sha.h"
#include "openssl/md5.h"
#include "SmthgNew.h"

unsigned char key[EVP_MAX_KEY_LENGTH];
unsigned char iv[EVP_MAX_IV_LENGTH];
namespace fs = std::filesystem;

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

void CalculateHash(const std::vector<unsigned char>& data, std::vector<unsigned char>& hash)
{
	std::vector<unsigned char> hashTmp(SHA256_DIGEST_LENGTH);

	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, &data[0], data.size());
	SHA256_Final(&hashTmp[0], &sha256);

	hash.swap(hashTmp);
}

bool CompareHash(std::vector<unsigned char>& decryptedText, std::vector<unsigned char>& hash, std::vector<unsigned char>& sourceHash)
{
	CalculateHash(decryptedText, hash);
	if (hash == sourceHash) {
		return true;
	}
	else {
		return false;
	}

};

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


void Decrypt()
{

	std::vector<unsigned char> chipherText;
	ReadFile("C:/chipher_text_brute_force", chipherText);

	std::vector<unsigned char> sourceHash;
	ExtractHash(sourceHash, chipherText);

	std::vector<unsigned char> plainText;
	std::vector<unsigned char> hashBuf;

	bool isDecOK = false;
	int attempts = 0;
	std::string pass;
	std::ifstream is("C:/Long pass.txt", std::ios::binary);

	for (; isDecOK = true; ++attempts) {
		is >> pass;


		PasswordToKey(pass);
		if ((DecryptAes(chipherText, plainText) == false)) {
			continue;
		}
		else {
			CalculateHash(plainText, hashBuf);
			if (hashBuf == sourceHash) {
				break;
			}
			else{
				continue;
			}
		}
	}

	std::cout <<"Correct password is " <<pass << std::endl;
	std::cout << attempts << std::endl;

	WriteFile("C:/chipher_text_brute_force", plainText);
}

