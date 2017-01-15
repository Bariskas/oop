#pragma once

void FillDictionaryFromStream(std::unordered_multimap<std::string, std::string>& dictionary, std::istream& stream);
void GetNextSentence(std::istream& inputStream, std::string& russianSentence,
	std::string& englishSentence);

std::string GetTranslate(std::unordered_multimap<std::string, std::string>& dictionary, std::string const& wordForTranslate);
void AddTranslateToDictionary(std::unordered_multimap<std::string, std::string>& dictionary, std::string& wordToAdd, std::string& translate);

bool IsRussianSentence(const std::string& word);
bool IsEnglishSentence(const std::string& word);
