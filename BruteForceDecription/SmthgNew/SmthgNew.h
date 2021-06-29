#pragma once
#include <string>

void ReadFile(const std::string& filePath, std::vector<unsigned char>& buf);
void ExtractHash(std::vector<unsigned char>& hashBuf, std::vector<unsigned char>& buf);
void WriteFile(const std::string& filePath, const	std::vector<unsigned char>& buf);
void Decrypt(std::vector<unsigned char>& chipherText, std::vector<unsigned char>& sourceHash, std::vector<std::string>* containerPass, class GenPasswords* c_getPass, bool* isDecOK);
void PasswordToKey(std::string* password);
bool DecryptAes(const std::vector<unsigned char>& cryptedText, std::vector<unsigned char>& decryptedText);
void CalculateHash(std::vector<unsigned char>& hash, const	std::vector<unsigned char>& decryptedText);
void CompareHash(std::vector<unsigned char>& sourceHash, std::vector<unsigned char>& plainText, std::string* pass, bool* isDecOK);
