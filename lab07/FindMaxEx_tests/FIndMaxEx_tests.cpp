#include "stdafx.h"
#include "../FindMaxEx/CSportsman.h"
#include "../FindMaxEx/FindMaxEx.h"

using namespace std;

struct FindMax_
{
	static bool BiggerWeight(CSportsman const& s1, CSportsman const& s2)
	{
		return s1.weight > s2.weight;
	}
	static bool TopFullName(CSportsman const& s1, CSportsman const& s2)
	{
		return !lexicographical_compare(s1.fullName.begin(), s1.fullName.end(),
			s2.fullName.begin(), s2.fullName.end(), CaseInsensitiveCharComparison);
	}
	static bool BottomFullName(CSportsman const& s1, CSportsman const& s2)
	{
		return lexicographical_compare(s1.fullName.begin(), s1.fullName.end(),
			s2.fullName.begin(), s2.fullName.end(), CaseInsensitiveCharComparison);
	}
	vector<CSportsman> CSportsmans{
		CSportsman("Fat Boris", 150, 90),
		CSportsman("Tall Boris", 200, 50),
		CSportsman("Simple Boris", 175, 70),
	};
	vector<CSportsman> emptyVector{};
private:
	static bool CaseInsensitiveCharComparison(char c1, char c2)
	{
		return tolower(c1) < tolower(c2);
	}
};

BOOST_FIXTURE_TEST_SUITE(FindMaxEx, FindMax_)
	BOOST_AUTO_TEST_CASE(false_on_empty_input)
	{
		CSportsman result;
		BOOST_CHECK(!FindMax(emptyVector, result, CSportsman::LessHeight));
	}
	BOOST_AUTO_TEST_CASE(max_weight)
	{
		CSportsman result;
		BOOST_CHECK(FindMax(CSportsmans, result, CSportsman::LessWeight));
		BOOST_CHECK_EQUAL(result.weight, 90);
	}
	BOOST_AUTO_TEST_CASE(min_weight)
	{
		CSportsman result;
		BOOST_CHECK(FindMax(CSportsmans, result, BiggerWeight));
		BOOST_CHECK_EQUAL(result.weight, 50);
	}
	BOOST_AUTO_TEST_CASE(max_height)
	{
		CSportsman result;
		BOOST_CHECK(FindMax(CSportsmans, result, CSportsman::LessHeight));
		BOOST_CHECK_EQUAL(result.height, 200);
	}
	BOOST_AUTO_TEST_CASE(first_full_name)
	{
		CSportsman result;
		BOOST_CHECK(FindMax(CSportsmans, result, TopFullName));
		BOOST_CHECK_EQUAL(result.fullName, "Fat Boris");
	}
	BOOST_AUTO_TEST_CASE(last_full_name)
	{
		CSportsman result;
		BOOST_CHECK(FindMax(CSportsmans, result, BottomFullName));
		BOOST_CHECK_EQUAL(result.fullName, "Tall Boris");
	}
BOOST_AUTO_TEST_SUITE_END()