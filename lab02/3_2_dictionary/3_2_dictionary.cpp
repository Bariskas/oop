// 3_2_dictionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

void LoadDictionaryFromFile(unordered_map<string, string>& dictionary, istream&  file);

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

	unordered_map<string, string> dictionary{};
	if (dictionaryPath != "")
	{
		ifstream dictionaryFile(dictionaryPath);
		if (dictionaryFile.is_open())
		{
			LoadDictionaryFromFile(dictionary, dictionary);
		}
	}

    return 0;
}

void LoadDictionaryFromFile(unordered_map<string, string> dictionary, istream file)
{
	file.getline();
}