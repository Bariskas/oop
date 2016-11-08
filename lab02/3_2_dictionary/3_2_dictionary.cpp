// 3_2_dictionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

void LoadDictionaryFromFile(unordered_map<string, string>& dictionary, istream&  file);
bool isRussianSentence(const string& word);
bool isEnglishSentence(const string& word);


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
		ifstream dictionaryFile(dictionaryPath);
		if (dictionaryFile.is_open())
		{
			try
			{
				LoadDictionaryFromFile(dictionary, dictionaryFile);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				return 1;
			}
		}
	}

	for (auto pair : dictionary)
	{
		cout << "1: " + pair.first << endl << "2: " + pair.second << endl;
	}

	getchar();

    return 0;
}

void LoadDictionaryFromFile(unordered_map<string, string>& dictionary, istream& file)
{
	string russianSentence;
	string englishSentence;
	while (!file.eof())
	{
		getline(file, russianSentence);
		if (!isRussianSentence(russianSentence))
		{
			throw invalid_argument("Russian sentence contain bad symbols or empty");
		}

		getline(file, englishSentence);
		if (!isEnglishSentence(englishSentence))
		{
			throw invalid_argument("English sentence contain bad symbols or empty");
		}

		boost::trim(russianSentence);
		boost::trim(englishSentence);

		dictionary.insert(make_pair(russianSentence, englishSentence));
	}
}

bool isRussianSentence(const string& word)
{
	return all_of(word.begin(), word.end(), [](char ch) {
		return (ch >= 'À' && ch <= 'ß') || (ch >= 'à' && ch <= 'ÿ') || ch == ' ';
	});
}

bool isEnglishSentence(const string& word)
{
	return all_of(word.begin(), word.end(), [](char ch) {
		return (ch > 'A' && ch < 'Z') || (ch > 'a' && ch < 'z') || ch == ' ';
	});
}