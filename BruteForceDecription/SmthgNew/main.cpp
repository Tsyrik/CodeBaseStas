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

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	std::ios_base::sync_with_stdio(false);
	std::cerr.imbue(std::locale(""));  // get pretty local formatting for numeric values


	Decrypt();


	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cerr << "Found in " << long double(duration.count() / 1000.0) << " seconds.\r\n";
}