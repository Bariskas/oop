#include "stdafx.h"
#include "../4_4_PrimeNumbers/PrimeNumbers.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GetPrimeNumbers_function_tests)

BOOST_AUTO_TEST_CASE(should_be_only_one_prime_number_with_2_upperbound)
{
	auto primeNumbers = GetPrimeNumbers(2);
	BOOST_CHECK(primeNumbers.)
}

BOOST_AUTO_TEST_CASE(sum_of_negative_values_must_be_zero)
{
	vector<double> testVector = { -2, -3, -4 };
	auto sum = CalculatePositiveElementSum(testVector);
	BOOST_CHECK_EQUAL(sum, 0);
}

BOOST_AUTO_TEST_SUITE_END()