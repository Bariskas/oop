#include "stdafx.h"
#include "Dictionary.h"
#include <Windows.h>

using namespace std;

bool InitDictionary(unordered_multimap<string, string>& dictionary,
	std::string const& dictionaryPath);
bool AddTranslate(unordered_multimap<string, string>& dictionary,
	string& wordToAdd);
bool SaveDictionaryInFile(unordered_multimap<string, string>& dictionary,
	std::string const& dictionaryFilePath);

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");

	if (argc != 2)
	{
		cout << "Wrong arguments count";
		return false;
	}
	string dictionaryPath = argv[1];

	unordered_multimap<string, string> dictionary{};
	InitDictionary(dictionary, argv[1]);
	for (auto pair : dictionary)
	{
		cout << "1: " + pair.first << endl << "2: " + pair.second << endl;
	}
	string userInput;
	bool newTranslateAdded = false;
	while (userInput != "...")
	{
		cout << ">";
		getline(cin, userInput);
		if (userInput.empty() || userInput == "...")
		{
			continue;
		}
		auto translate = GetTranslate(dictionary, userInput);
		if (translate.empty())
		{
			if (AddTranslate(dictionary, userInput))
			{
				newTranslateAdded = true;
			}
		}
		else
		{
			cout << translate << endl;
		}
	}


	if (newTranslateAdded)
	{
		cout << "Y(y) to save new translations" << endl;
		cout << '>';
		char userInput;
		cin >> userInput;
		if (::tolower(userInput) == 'y')
		{
			if (!SaveDictionaryInFile(dictionary, dictionaryPath))
			{
				return 1;
			}
		}
	}

    return 0;
}

bool InitDictionary(unordered_multimap<string, string>& dictionary,
	std::string const& dictionaryPath)
{
	if (dictionaryPath != "")
	{
		try
		{
			ifstream dictionaryFileStream(dictionaryPath);
			LoadDictionaryFromFile(dictionary, dictionaryFileStream);
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
			return false;
		}
	}

	return true;
}

bool AddTranslate(unordered_multimap<string, string>& dictionary,
	string& wordToAdd)
{
	cout << "No such word in dictionary. Write translate or skip." << endl;
	cout << '>';
	string userInput;
	getline(cin, userInput);
	bool isAdded = false;
	if (!userInput.empty())
	{
		AddTranslateToDictionary(dictionary, wordToAdd, userInput);
		isAdded = true;
	}
	return isAdded;

}

bool SaveDictionaryInFile(unordered_multimap<string, string>& dictionary, std::string const& dictionaryPath)
{
	ofstream os;
	os.open(dictionaryPath);
	if (os.is_open())
	{
		for (auto it : dictionary)
		{
			if (IsRussianSentence(it.first))
			{
				os << it.first << endl << it.second << endl;
			}
		}
		if (!os.flush())
		{
			cout << "Save unsuccessful.";
			return false;
		}
		cout << "Save success.";
	}
	return true;
}
