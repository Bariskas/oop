#include "stdafx.h"
#include "Dictionary.h"

using namespace std;

void LoadDictionaryFromFile(unordered_map<string, string>& dictionary, const string& dictionaryFilePath)
{
	ifstream dictionaryFileStream(dictionaryFilePath);
	if (dictionaryFileStream.is_open())
	{
		FillDictionaryFromStream(dictionary, dictionaryFileStream);
	}
}

void FillDictionaryFromStream(unordered_map<string, string>& dictionary, istream& stream)
{
	if (stream.peek() == std::istream::traits_type::eof())
	{
		return;
	}

	string russianSentence;
	string englishSentence;

	while (!stream.eof())
	{
		getline(stream, russianSentence);
		if (!isRussianSentence(russianSentence))
		{
			throw invalid_argument("Russian sentence contain bad symbols or empty");
		}

		if (stream.eof())
		{
			throw invalid_argument("Wrong dictionary file structure");
		}

		getline(stream, englishSentence);
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