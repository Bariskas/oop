#include "stdafx.h"
#include "../CMyString/MyString.h"

BOOST_AUTO_TEST_SUITE(MyString)
	BOOST_AUTO_TEST_CASE(Can_initialized_by_string_literal)
	{
		CMyString testString("heh");
		BOOST_CHECK_EQUAL(testString[0], 'h');
		BOOST_CHECK_EQUAL(testString[1], 'e');
		BOOST_CHECK_EQUAL(testString[2], 'h');
		BOOST_CHECK_EQUAL(testString[3], '\0');
		BOOST_CHECK_EQUAL(testString.GetLength(), 3);
	}
	BOOST_AUTO_TEST_SUITE(Assignment)
		BOOST_AUTO_TEST_CASE(Can_assignee_other_cmystring)
		{
			CMyString initializedMyString("heh");
			CMyString testString = initializedMyString;
			BOOST_CHECK_EQUAL(testString[0], 'h');
			BOOST_CHECK_EQUAL(testString[1], 'e');
			BOOST_CHECK_EQUAL(testString[2], 'h');
			BOOST_CHECK_EQUAL(testString[3], '\0');
			BOOST_CHECK_EQUAL(testString.GetLength(), 3);
		}
		BOOST_AUTO_TEST_CASE(Can_assignee_string_literal)
		{
			CMyString testString = "heh";
			BOOST_CHECK_EQUAL(testString[0], 'h');
			BOOST_CHECK_EQUAL(testString[1], 'e');
			BOOST_CHECK_EQUAL(testString[2], 'h');
			BOOST_CHECK_EQUAL(testString[3], '\0');
			BOOST_CHECK_EQUAL(testString.GetLength(), 3);
		}
		BOOST_AUTO_TEST_CASE(Can_assignee_stl_string)
		{
			std::string stlString{ "heh" };
			CMyString testString = stlString;
			BOOST_CHECK_EQUAL(testString[0], 'h');
			BOOST_CHECK_EQUAL(testString[1], 'e');
			BOOST_CHECK_EQUAL(testString[2], 'h');
			BOOST_CHECK_EQUAL(testString[3], '\0');
			BOOST_CHECK_EQUAL(testString.GetLength(), 3);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(Can_be_summirized)
	{
		CMyString myString1("heh");
		CMyString myString2("hoh");
		CMyString sumResult = myString1 + myString2;
		BOOST_CHECK_EQUAL(sumResult[0], 'h');
		BOOST_CHECK_EQUAL(sumResult[1], 'e');
		BOOST_CHECK_EQUAL(sumResult[2], 'h');
		BOOST_CHECK_EQUAL(sumResult[3], 'h');
		BOOST_CHECK_EQUAL(sumResult[4], 'o');
		BOOST_CHECK_EQUAL(sumResult[5], 'h');
		BOOST_CHECK_EQUAL(sumResult[6], '\0');
		BOOST_CHECK_EQUAL(sumResult.GetLength(), 6);
	}
BOOST_AUTO_TEST_SUITE_END()