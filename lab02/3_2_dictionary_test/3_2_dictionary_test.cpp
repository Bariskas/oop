// 3_2_dictionary_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <istream>
#include <algorithm>
#include <vector>  
#include <string>
#include <sstream>
#include <cstdio>
#include <iterator> 
#include <numeric>

using namespace std;

int main(int argc, char* argv[])
{
	string dictionaryPath = "";
	if (argc == 2)
	{
		dictionaryPath = argv[1];
	}
	else if (argc > 0)
	{
		cout << "Wrong arguments";
	}



    return 0;
}

