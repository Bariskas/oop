// CMyArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMyArray.h"

int main()
{
	CMyArray<int> myArray{ 1, 3, 5, 2, 4 };
	auto maxValue = *std::max_element(myArray.begin(), myArray.end());
	std::cout << "Max value int array[1, 3, 5, 2, 4] is: " << maxValue << std::endl;
    return 0;
}

