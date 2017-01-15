#include "stdafx.h"
#include "../4_4_PrimeNumbers/PrimeNumbers.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GetPrimeNumbers_function)
BOOST_AUTO_TEST_CASE(should_be_2_3_5_numbers_with_6_upperbound)
{
	auto set = GetPrimeNumbers(6);
	std::set<int> exp = { 2, 3, 5 };
	BOOST_CHECK(set == exp);
}
#ifdef _DEBUG
#else
BOOST_AUTO_TEST_CASE(should_be_5761455_elements_with_100000000_upperbound)
{
	auto set = GetPrimeNumbers(100000000);
	BOOST_CHECK(set.size() == 5761455);
}
#endif
BOOST_AUTO_TEST_SUITE_END()