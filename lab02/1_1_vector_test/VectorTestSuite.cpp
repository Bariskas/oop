#include "stdafx.h"
#include "../1_1_vector/VectorConverting.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(NumericConverterTestSuite)

	BOOST_AUTO_TEST_CASE(sum_of_positive_values_on_positive_vector)
	{
		vector<double> testVector = { 2, 3, 4 };
		auto sum = CalculatePositiveElementSum(testVector);
		BOOST_CHECK_EQUAL(sum, 9);
	}

	BOOST_AUTO_TEST_CASE(sum_of_positive_values_on_negative_vector)
	{
		vector<double> testVector = { -2, -3, -4 };
		auto sum = CalculatePositiveElementSum(testVector);
		BOOST_CHECK_EQUAL(sum, 0);
	}

	BOOST_AUTO_TEST_CASE(convert_positive_vector_without_sort)
	{
		vector<double> testVector = {2, 3, 4};
		ConvertVector(testVector);
		BOOST_CHECK_EQUAL(testVector[0], 4);
		BOOST_CHECK_EQUAL(testVector[1], -6);
		BOOST_CHECK_EQUAL(testVector[2], 8);
	}

	BOOST_AUTO_TEST_CASE(convert_simple_vector_without_sort)
	{
		vector<double> testVector = { 2, -3, -4, 5 };
		ConvertVector(testVector);
		BOOST_CHECK_EQUAL(testVector[0], 4);
		BOOST_CHECK_EQUAL(testVector[1], -10);
		BOOST_CHECK_EQUAL(testVector[2], -8);
		BOOST_CHECK_EQUAL(testVector[3], -2);
	}

	BOOST_AUTO_TEST_CASE(empty_vector)
	{
		vector<double> testVector = {};
		ConvertVector(testVector);
		BOOST_CHECK_EQUAL(testVector.size(), 0);
	}

BOOST_AUTO_TEST_SUITE_END()