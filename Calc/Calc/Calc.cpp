#include <iostream>
//#include "CalcImpl.h"
#include <windows.h>

typedef bool(*isDebuggerPresent)();


int main()
{
	
	HMODULE a = LoadLibraryA("Kernel32.dll");
	void* b = GetProcAddress(a, "IsDebuggerPresent");
	isDebuggerPresent c = static_cast<isDebuggerPresent>(b);
	
	std::cout << c() << std::endl;

	//std::cout << add(10, 20) << std::endl;

	//std::cout << Add(10, 20) << std::endl;


}


/*
#include <iostream>
//#include "CalcImpl.h"
#include <windows.h>

typedef int(*Add)(int, int);


int main()
{
	
	HMODULE a = LoadLibraryA("CalcDLL.dll");
	void* b = GetProcAddress(a, "Add");
	Add add = static_cast<Add>(b);

	std::cout << add(10, 20) << std::endl;

	//std::cout << Add(10, 20) << std::endl;


}
*/