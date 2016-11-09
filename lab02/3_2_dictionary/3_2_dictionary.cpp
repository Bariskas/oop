// 3_2_dictionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	string dictionaryPath = "";
	if (argc == 2)
	{
		dictionaryPath = argv[1];
	}
	else if (argc > 0)
	{
		cout << "Wrong arguments";
	}

	unordered_map<string, string> dictionary{};
	if (dictionaryPath != "")
	{
		try
		{
			LoadDictionaryFromFile(dictionary, dictionaryPath);
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
			return 1;
		}
	}

	for (auto pair : dictionary)
	{
		cout << "1: " + pair.first << endl << "2: " + pair.second << endl;
	}

	getchar();

    return 0;
}