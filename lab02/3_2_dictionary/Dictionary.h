#pragma once

void LoadDictionaryFromFile(std::unordered_map<std::string, std::string>& dictionary, const std::string&  dictionaryFilePath);
void FillDictionaryFromStream(std::unordered_map<std::string, std::string>& dictionary, std::istream& stream);
bool isRussianSentence(const std::string& word);
bool isEnglishSentence(const std::string& word);
