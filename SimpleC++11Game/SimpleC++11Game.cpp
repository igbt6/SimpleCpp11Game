// SimpleC++11Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <iostream>
class Simple
{
private:
	int variable{ 0 };
public:
	Simple()
	{
		std::cout << "Constructed" << std::endl;
	}
	~Simple()
	{
		std::cout << "Destroyed" << std::endl;
	}
};

int main()
{
	using UniqueSimplePtr = std::unique_ptr<Simple>;
	UniqueSimplePtr pSimple1{ new Simple() };
	std::cout << pSimple1.get() << std::endl;
	UniqueSimplePtr pSimple2;
	pSimple2.swap(pSimple1);
	std::cout << pSimple1.get() << std::endl;
	std::cout << pSimple2.get() << std::endl;
	
	using IntSharedPtr = std::shared_ptr<int>;
	IntSharedPtr pIntArray1{ new int[16] };
	IntSharedPtr pIntArray2{ pIntArray1 };
	std::cout << std::endl << pIntArray1.get() << std::endl;
	std::cout << pIntArray2.get() << std::endl;
	getchar();
	return 0;
}
