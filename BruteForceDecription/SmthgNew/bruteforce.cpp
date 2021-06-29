#include <vector>
#include <mutex>
#include "bruteforce.h"

std::mutex mtxPass;

GenPasswords::GenPasswords()
{
	m_genPass.resize(m_maxSize + 1);
	for (size_t i = 1; i < m_maxSize; m_guessc[i++] = -1) {}
	for (size_t i = 1; i <= m_maxSize; m_genPass[i++] = '\0') {}
};
void GenPasswords::Gen(std::vector<std::string>& retPasswords)
{
	mtxPass.lock();
	retPasswords.clear();
	size_t batchSize = 0;
	for (; m_generatedPasswordsCount < m_totalPasswordsCount && batchSize < m_numberOfPass; ++m_generatedPasswordsCount, ++batchSize)
	{
		size_t i = 0;
		while (m_guessc[i] == m_charCount)
		{
			m_guessc[i] = 0;
			m_guessc[++i] += 1;
		}
		for (size_t j = 0; j <= i; ++j)
		{
			if (j < m_maxSize)
				m_genPass[j] = m_chars[m_guessc[j]];
		}
		m_genPass.resize(4);
		retPasswords.push_back(m_genPass);
		++m_guessc[0];
	}
	mtxPass.unlock();
}