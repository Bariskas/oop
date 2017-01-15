#include "stdafx.h"
#include "Dictionary.h"

using namespace std;

void FillDictionaryFromStream(unordered_multimap<string, string>& dictionary, istream& stream)
{
	if (stream.peek() == std::istream::traits_type::eof())
	{
		return;
	}
	
	bool isTranslateNow = false;
	
	string russianSentence;
	string englishSentence;

	while (!stream.eof())
	{
		GetNextSentence(stream, russianSentence, englishSentence);
		if (stream.eof())
		{
			throw invalid_argument("Wrong dictionary file structure");
		}
		GetNextSentence(stream, russianSentence, englishSentence);

		boost::trim(russianSentence);
		boost::trim(englishSentence);
		string russianLowSentence = russianSentence;
		string englishLowSentence = englishSentence;
		boost::algorithm::to_lower(russianLowSentence, std::locale(""));
		boost::algorithm::to_lower(englishLowSentence, std::locale(""));
		dictionary.insert(make_pair(russianLowSentence, englishSentence));
		dictionary.insert(make_pair(englishLowSentence, russianSentence));
	}
}

void GetNextSentence(std::istream& inputStream, std::string& russianSentence, std::string& englishSentence)
{
	string tempString;
	getline(inputStream, tempString);
	if (IsRussianSentence(tempString))
	{
		russianSentence = tempString;
	}
	else if (IsEnglishSentence(tempString))
	{
		englishSentence = tempString;
	}
}

std::string GetTranslate(std::unordered_multimap<std::string, std::string>& dictionary, 
	std::string const& wordForTranslate)
{
	string word;
	transform(wordForTranslate.begin(), wordForTranslate.end(),
		back_inserter(word), ::tolower);
	auto translations = dictionary.equal_range(word);
	string result;
	for (auto it = translations.first; it != translations.second; ++it)
	{
		result += it->second + " ";
	}
	return result.substr(0, result.length() - 1);
}

void AddTranslateToDictionary(std::unordered_multimap<std::string, std::string>& dictionary, std::string& wordToAdd, std::string& translate)
{
	boost::trim(wordToAdd);
	boost::trim(translate);
	string wordToAddLow = wordToAdd;
	string translateLow = translate;
	boost::algorithm::to_lower(wordToAddLow, std::locale(""));
	boost::algorithm::to_lower(translateLow, std::locale(""));
	dictionary.insert(make_pair(wordToAddLow, translate));
	dictionary.insert(make_pair(translateLow, wordToAddLow));
}

bool IsRussianSentence(const string& word)
{
	return all_of(word.begin(), word.end(), [](char ch) {
		return (ch >= 'À' && ch <= 'ß') || (ch >= 'à' && ch <= 'ÿ') || ch == ' '
			|| ch == '¸' || ch == '¨';
	}) && word.length() != 0;
}

bool IsEnglishSentence(const string& word)
{
	return all_of(word.begin(), word.end(), [](char ch) {
		return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == ' ';
	}) && word.length() != 0;
}