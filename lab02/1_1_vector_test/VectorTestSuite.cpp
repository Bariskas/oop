#include "stdafx.h"
#include "../1_1_vector/VectorConverting.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(NumericConverterTestSuite)

	BOOST_AUTO_TEST_CASE(positive_values_should_be_summarized)
	{
		vector<double> testVector = { 2, 3, 4 };
		auto sum = CalculatePositiveElementSum(testVector);
		BOOST_CHECK_EQUAL(sum, 9);
	}

	BOOST_AUTO_TEST_CASE(sum_must_be_zerom)
	{
		vector<double> testVector = { -2, -3, -4 };
		auto sum = CalculatePositiveElementSum(testVector);
		BOOST_CHECK_EQUAL(sum, 0);
	}

	BOOST_AUTO_TEST_CASE(odd_doubled_even_without_sum_of_positives)
	{
		vector<double> testVector = {2, 3, 4};
		ConvertVector(testVector);
		BOOST_CHECK_EQUAL(testVector[0], 4);
		BOOST_CHECK_EQUAL(testVector[1], -6);
		BOOST_CHECK_EQUAL(testVector[2], 8);
	}

	BOOST_AUTO_TEST_CASE(empty_vector_must_process_without_exception)
	{
		vector<double> testVector = {};
		BOOST_CHECK_NO_THROW(ConvertVector(testVector));
		BOOST_CHECK_EQUAL(testVector.size(), 0);
	}

BOOST_AUTO_TEST_SUITE_END()