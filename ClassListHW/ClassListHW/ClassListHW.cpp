#include <iostream>
#include "List.h"


int main()
{

	util::List list;
	list.PushBack(9);
	list.PushBack(8);
	list.PushBack(7);
	list.PushBack(6);
	//list.PushBack(5);
	//list.PushBack(4);
	//list.PushBack(3);
	//list.PushBack(2);
	//list.PushBack(1);
	//list.PushBack(0);
	//list.PushBack(10);
	//list.PopBack();
	std::cout << list.Size() << std::endl;
	list.ShowList();
	//std::cout << curList.PopBack() << std::endl;
	//list.ShowList();
}