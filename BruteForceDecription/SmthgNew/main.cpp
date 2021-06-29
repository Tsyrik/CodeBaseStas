#include <vector>
#include <iostream>
#include <thread>
#include <windows.h>
#include <list>
#include <math.h>
#include "bruteforce.h"
#include "SmthgNew.h"
#include <mutex>


#include "openssl/evp.h"
#include <openssl/aes.h>
#include "openssl/sha.h"
#include "openssl/md5.h"

bool isDecOK = false;

void main()
{
	auto start = std::chrono::high_resolution_clock::now();
	std::ios_base::sync_with_stdio(false);
	std::cerr.imbue(std::locale(""));
	try {
		std::vector<unsigned char> chipherText;
		ReadFile("C:/chipher_text_brute_force", chipherText);

		std::vector<unsigned char> sourceHash;
		ExtractHash(sourceHash, chipherText);

		std::vector<std::string> firstThreadContainer;
		std::vector<std::string> secondThreadContainer;
		std::vector<std::string> thirdThreadContainer;
		std::vector<std::string> fourthThreadContainer;
		std::vector<std::string> fifthThreadContainer;
		std::vector<std::string> sixthThreadContainer;
		std::vector<std::string> seventhThreadContainer;
		std::vector<std::string> eighthThreadContainer;

		GenPasswords getPass;



		std::thread first(Decrypt, std::ref(chipherText), std::ref(sourceHash), &firstThreadContainer, &getPass, &isDecOK);
		std::thread second(Decrypt, std::ref(chipherText), std::ref(sourceHash), &secondThreadContainer, &getPass, &isDecOK);
		std::thread third(Decrypt, std::ref(chipherText), std::ref(sourceHash), &thirdThreadContainer, &getPass, &isDecOK);
		std::thread fouthr(Decrypt, std::ref(chipherText), std::ref(sourceHash), &fourthThreadContainer, &getPass, &isDecOK);
		std::thread fifth(Decrypt, std::ref(chipherText), std::ref(sourceHash), &fifthThreadContainer, &getPass, &isDecOK);
		std::thread sixth(Decrypt, std::ref(chipherText), std::ref(sourceHash), &sixthThreadContainer, &getPass, &isDecOK);
		std::thread seventh(Decrypt, std::ref(chipherText), std::ref(sourceHash), &seventhThreadContainer, &getPass, &isDecOK);
		std::thread eighth(Decrypt, std::ref(chipherText), std::ref(sourceHash), &eighthThreadContainer, &getPass, &isDecOK);

		first.join();
		second.join();
		third.join();
		fouthr.join();
		fifth.join();
		sixth.join();
		seventh.join();
		eighth.join();
	}
	catch (const std::runtime_error& ex)
	{
		std::cerr << ex.what();
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cerr << "Found in " << long double(duration.count() / 1000.0) << " seconds.\r\n";
}