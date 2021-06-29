#pragma once
#include <vector>
#include "SmthgNew.h"
#include <thread>
#include <mutex>
#include <list>

class GenPasswords {
public:
	GenPasswords();
	void Gen(std::vector<std::string>* retPasswords);
private:
	static const size_t m_maxSize = 30;
	const size_t m_charCount = 36;
	const size_t m_numberOfPass = 10000;
	const size_t m_maxPasswordLength = 4;
	const std::string m_chars = "abcdefghijklmnopqrstuvwxyz0123456789";
	const double m_totalPasswordsCount = pow(m_charCount, m_maxPasswordLength) + pow(m_charCount, 3) + pow(m_charCount, 2) + pow(m_charCount, 1);
	std::string m_genPass;
	size_t m_generatedPasswordsCount = 0;
	int m_guessc[m_maxSize] = {};
};
