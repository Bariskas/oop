#include "stdafx.h"
#include "../3_2_dictionary/Dictionary.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Dictionary)

	BOOST_AUTO_TEST_CASE(empty_dictionary_return_empty_translations)
	{
		unordered_multimap<string, string> dictionary;
		string result = GetTranslate(dictionary, "Hello");
		BOOST_CHECK(result.length() == 0);
	}
	BOOST_AUTO_TEST_CASE(translations_can_be_added)
	{
		unordered_multimap<string, string> dictionary;
		string rusWord = "привет";
		string engWord = "hello";
		AddTranslateToDictionary(dictionary, rusWord, engWord);
		string result = GetTranslate(dictionary, rusWord);
		BOOST_CHECK_EQUAL(result, engWord);
	}
BOOST_AUTO_TEST_SUITE_END()