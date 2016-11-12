#include "stdafx.h"
#include "../1_1_vector/VectorConverting.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CalculatePositiveElementSum_function_test_suite)

	BOOST_AUTO_TEST_CASE(positive_values_should_be_summarized)
	{
		BOOST_CHECK_EQUAL(CalculatePositiveElementSum({ 2, 3, 4 }), 9);
		BOOST_CHECK_EQUAL(CalculatePositiveElementSum({ }), 0);
		BOOST_CHECK_CLOSE_FRACTION(CalculatePositiveElementSum({ 0.5, -0.1, 3.4 }), 3.9, 1e-5);
	}

	BOOST_AUTO_TEST_CASE(sum_of_negative_values_must_be_zero)
	{
		vector<double> testVector = { -2, -3, -4 };
		auto sum = CalculatePositiveElementSum(testVector);
		BOOST_CHECK_EQUAL(sum, 0);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ConvertVector_function_test_suite)

	BOOST_AUTO_TEST_CASE(odd_doubled_even_without_sum_of_positives)
	{
		vector<double> testVector = { 2, 3, 4 };
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