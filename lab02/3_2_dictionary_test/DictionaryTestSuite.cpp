#include "stdafx.h"
#include "../3_2_dictionary/Dictionary.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Dictionary)

	BOOST_AUTO_TEST_CASE(with_empty_file_dictionary_should_be_empty)
	{
		stringstream inputStream("");
		unordered_map<string, string> dictionary{};
		FillDictionaryFromStream(dictionary, inputStream);
		BOOST_CHECK_EQUAL(dictionary.empty(), true);
	}

BOOST_AUTO_TEST_SUITE_END()