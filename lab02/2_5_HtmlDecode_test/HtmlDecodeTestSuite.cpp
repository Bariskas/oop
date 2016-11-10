#include "stdafx.h"
#include "../2_5_HtmlDecode/HtmlDecode.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(HtmlDecodeTestSuite)

	BOOST_AUTO_TEST_CASE(empty_string_should_proccessed_without_exception)
	{
		BOOST_CHECK_NO_THROW(DecodeHtmlEntities(""));
	}

	BOOST_AUTO_TEST_CASE(html_entities_should_be_decoded)
	{
		string result = DecodeHtmlEntities("&amp;&amp;heh");
		BOOST_CHECK_EQUAL(result, "&&heh");
		result = DecodeHtmlEntities("&amp;amp;");
		BOOST_CHECK_EQUAL(result, "&amp;");
		result = DecodeHtmlEntities("123&amp;&amp;");
		BOOST_CHECK_EQUAL(result, "123&1&");
	}

BOOST_AUTO_TEST_SUITE_END()