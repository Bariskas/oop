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
	BOOST_AUTO_TEST_SUITE(initialization_from_stream)
		BOOST_AUTO_TEST_CASE(check_simple_initialization)
		{
			stringstream ss("ПРивет\nHello\nПривет\nHi");
			unordered_multimap<string, string> dictionary;
			FillDictionaryFromStream(dictionary, ss);
			string result = GetTranslate(dictionary, "Привет");
			BOOST_CHECK_EQUAL(result, "Hello Hi");
		}
		BOOST_AUTO_TEST_CASE(check_initialization_with_yo)
		{
			stringstream ss("ПРивет\nHello\nСловоёб\nSlovoeb");
			unordered_multimap<string, string> dictionary;
			FillDictionaryFromStream(dictionary, ss);
			string result = GetTranslate(dictionary, "СЛовоёб");
			BOOST_CHECK_EQUAL(result, "Slovoeb");
		}
		BOOST_AUTO_TEST_CASE(odd_count_words_triggers_exception)
		{
			stringstream ss("ПРивет\nHello\nПривет\nHi\nКек");
			unordered_multimap<string, string> dictionary;
			BOOST_CHECK_THROW(FillDictionaryFromStream(dictionary, ss), invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(empty_stream_doesnt_triggers_exception)
		{
			stringstream ss("");
			unordered_multimap<string, string> dictionary;
			BOOST_CHECK_NO_THROW(FillDictionaryFromStream(dictionary, ss));
			BOOST_CHECK(dictionary.empty());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()