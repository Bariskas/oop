#include "stdafx.h"
#include "../HttpUrl/HttpUrl.h"
#include "../HttpUrl/UrlUtils.h"
#include <boost/test/output_test_stream.hpp>

using namespace std;

struct UrlFixture
{
	void CheckUrlState(CHttpUrl const& url, Protocol expectedProtocol, 
		string const& expectedDomain, int expectedPort,
		string const& expectedDocument) const
	{
		BOOST_CHECK(url.GetProtocol() == expectedProtocol);
		BOOST_CHECK_EQUAL(url.GetDomain() , expectedDomain);
		BOOST_CHECK_EQUAL(url.GetPort(), expectedPort);
		BOOST_CHECK_EQUAL(url.GetDocument(), expectedDocument);
	}

	void CheckUrlState(CHttpUrl const& url, Protocol expectedProtocol,
		string const& expectedDomain, int expectedPort,
		string const& expectedDocument, string const& expectedUrl) const
	{
		CheckUrlState(url, expectedProtocol, expectedDomain, expectedPort, expectedDocument);
		BOOST_CHECK_EQUAL(url.GetURL(), expectedUrl);
	}
};

BOOST_FIXTURE_TEST_SUITE(Url, UrlFixture)
	BOOST_FIXTURE_TEST_SUITE(fail_creation_from_string, UrlFixture)
		BOOST_AUTO_TEST_CASE(with_protocol_only)
		{
			BOOST_CHECK_THROW(CHttpUrl("Http://"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("http://"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("https://"), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(with_wrong_domen)
		{
			BOOST_CHECK_THROW(CHttpUrl(".google"), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(with_wrong_protocol)
		{
			BOOST_CHECK_THROW(CHttpUrl("htp://google.com/"), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(with_wrong_port)
		{
			BOOST_CHECK_THROW(CHttpUrl("http://google.com:65536"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("http://google.com:0/"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("http://google.com:-1/"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("http://google.com:abc/index.txt"), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(with_wrong_document)
		{
			BOOST_CHECK_THROW(CHttpUrl("http://google.com:80/index .txt"), CUrlParsingError);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_FIXTURE_TEST_SUITE(success_creation_from_string, UrlFixture)
		BOOST_AUTO_TEST_CASE(without_protocol_and_without_port)
		{
			CheckUrlState(CHttpUrl("google"), HTTP, "google", 80, "/");
			CheckUrlState(CHttpUrl("google.com"), HTTP, "google.com", 80, "/");
			CheckUrlState(CHttpUrl("google.com/index.html"), HTTP, "google.com", 80, "/index.html");
			CheckUrlState(CHttpUrl("google.com/folder/index.html"), HTTP, "google.com", 80, "/folder/index.html");
		}
		BOOST_AUTO_TEST_CASE(without_protocol)
		{
			CheckUrlState(CHttpUrl("google.com:800"), HTTP, "google.com", 800, "/");
			CheckUrlState(CHttpUrl("google.com:800/index.html"), HTTP, "google.com", 800, "/index.html");
			CheckUrlState(CHttpUrl("google.com:800/folder/index.html"), HTTP, "google.com", 800, "/folder/index.html");
		}
		BOOST_AUTO_TEST_CASE(without_port)
		{
			CheckUrlState(CHttpUrl("http://google.com"), HTTP, "google.com", 80, "/");
			CheckUrlState(CHttpUrl("https://google.com/index.html"), HTTPS, "google.com", 443, "/index.html");
		}
		BOOST_AUTO_TEST_CASE(with_port_and_protocol)
		{
			CheckUrlState(CHttpUrl("https://google.com:80"), HTTPS, "google.com", 80, "/");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_FIXTURE_TEST_SUITE(url_creation_from_parts, UrlFixture)
		BOOST_AUTO_TEST_CASE(with_wrong_domain)
		{
			BOOST_CHECK_THROW(CHttpUrl("google.c", "index.html", HTTP), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("google.c", "index.html", HTTP, 200), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("google.com:80", "index.html", HTTP), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("google.com:80", "index.html", HTTP, 200), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("google", "index.html", HTTP), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("google", "index.html", HTTP, 200), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(with_wrong_document)
		{
			BOOST_CHECK_THROW(CHttpUrl("google.com", "ind ex.html", HTTP), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("google.com", "ind ex.html", HTTP, 200), CUrlParsingError);
		}
		BOOST_AUTO_TEST_CASE(without_port)
		{
			CheckUrlState(CHttpUrl("google.com", "index.html", HTTP), HTTP, "google.com", 80, "/index.html", 
				"http://google.com/index.html");
			CheckUrlState(CHttpUrl("google.com", "/index.html", HTTP), HTTP, "google.com", 80, "/index.html",
				"http://google.com/index.html");
			CheckUrlState(CHttpUrl("google.com", "index.html", HTTPS), HTTPS, "google.com", 443, "/index.html", 
				"https://google.com/index.html");
			CheckUrlState(CHttpUrl("google.com", "/index.html", HTTPS), HTTPS, "google.com", 443, "/index.html", 
				"https://google.com/index.html");
		}
		BOOST_AUTO_TEST_CASE(with_all_parts)
		{
			CheckUrlState(CHttpUrl("google.com", "index.html", HTTP, 200), HTTP, "google.com", 200, "/index.html", 
				"http://google.com:200/index.html");
			CheckUrlState(CHttpUrl("google.com", "/index.html", HTTPS, 200), HTTPS, "google.com", 200, "/index.html", 
				"https://google.com:200/index.html");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(UrlUtils, UrlFixture)
	BOOST_AUTO_TEST_CASE(reading_invalid_urls)
	{
		boost::test_tools::output_test_stream errorOutput;
		stringstream ss("http://google.com:65536/index.html");
		CUrlUtils::ReadAndWriteUrls(ss, cout, errorOutput);
		BOOST_CHECK(errorOutput.is_equal("\"http://google.com:65536/index.html\": Wrong port value\n"));
	}
	BOOST_AUTO_TEST_CASE(write_urls_info)
	{
		boost::test_tools::output_test_stream infoOutput;
		stringstream ss(
			"http://google.com:300/index.html https://www.google.com/opopop/index.html"
		);
		CUrlUtils::ReadAndWriteUrls(ss, infoOutput);
		BOOST_CHECK(infoOutput.is_equal(R"(Url: http://google.com:300/index.html
Protocol: http
Domen: google.com
Port: 300
Document: /index.html
Url: https://www.google.com/opopop/index.html
Protocol: https
Domen: www.google.com
Port: 443
Document: /opopop/index.html
)"));
	}
BOOST_AUTO_TEST_SUITE_END()