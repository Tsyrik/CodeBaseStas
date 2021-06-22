#pragma once

void ReadFile(const std::string& filePath, std::vector<unsigned char>& buf);
void ExtractHash(std::vector<unsigned char>& hashBuf, std::vector<unsigned char>& buf);
void WriteFile(const std::string& filePath, const std::vector<unsigned char>& buf);
void PasswordToKey(std::string& password);
void CalculateHash(const std::vector<unsigned char>& data, std::vector<unsigned char>& hash);
bool CompareHash(std::vector<unsigned char>& decryptedText, std::vector<unsigned char>& hash, std::vector<unsigned char>& sourceHash);
bool DecryptAes(const std::vector<unsigned char> cryptedText, std::vector<unsigned char>& decryptedText);
void Decrypt();
