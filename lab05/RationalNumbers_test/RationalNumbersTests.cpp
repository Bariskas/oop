#include "stdafx.h"
#include "../RationalNumbers/CRational.h"

using namespace std;

struct RationalNumbersFixture
{
	static void CheckRationalNumberState(CRational rational, int numerator, int denominator)
	{
		BOOST_CHECK_EQUAL(rational.GetNumerator(), numerator);
		BOOST_CHECK_EQUAL(rational.GetDenominator(), denominator);
	}
};

BOOST_FIXTURE_TEST_SUITE(RationalNumbers, RationalNumbersFixture)
BOOST_AUTO_TEST_CASE(constructors_check)
{
	CRational r1;
	CheckRationalNumberState(r1, 0, 1);
	CRational r2(5);
	CheckRationalNumberState(r2, 5, 1);
	CRational r3(5, 6);
	CheckRationalNumberState(r3, 5, 6);
}
BOOST_AUTO_TEST_CASE(can_be_represented_like_double)
{
	CRational r1;
	BOOST_CHECK_CLOSE_FRACTION(r1.ToDouble(), 0, 0.0000001);
	CRational r2(5);
	BOOST_CHECK_CLOSE_FRACTION(r2.ToDouble(), 5, 0.0000001);
	CRational r3(5, 10);
	BOOST_CHECK_CLOSE_FRACTION(r3.ToDouble(), 0.5, 0.0000001);
}
BOOST_AUTO_TEST_CASE(check_unary_plus_operator)
{
	CRational r1(3, 5);
	CheckRationalNumberState(+r1, 3, 5);
}
BOOST_AUTO_TEST_CASE(check_unary_minus_operator)
{
	CRational r1(3, 5);
	CheckRationalNumberState(-r1, -3, 5);
}
BOOST_AUTO_TEST_CASE(check_binary_plus_operator)
{
	CRational r1(1, 2);
	CRational r2(1, 6);
	CheckRationalNumberState(r1 + r2, 2, 3);
	CheckRationalNumberState(r1 + 1, 3, 2);
	CheckRationalNumberState(1 + r1, 3, 2);
}
BOOST_AUTO_TEST_CASE(check_binary_minus_operator)
{
	CRational r1(1, 2);
	CRational r2(1, 6);
	CheckRationalNumberState(r1 - r2, 1, 3);
	CheckRationalNumberState(r1 - 1, -1, 2);
	CheckRationalNumberState(1 - r1, 1, 2);
}
BOOST_AUTO_TEST_CASE(check_pred_plus_operator)
{
	CRational r1(1, 2);
	CRational r2(1, 6);
	CheckRationalNumberState(r1 += r2, 2, 3);
	CRational r3(1, 2);
	CheckRationalNumberState(r3 += 1, 3, 2);
}
BOOST_AUTO_TEST_CASE(check_pred_minus_operator)
{
	CRational r1(1, 2);
	CRational r2(1, 6);
	CheckRationalNumberState(r1 -= r2, 1, 3);
	CRational r3(1, 2);
	CheckRationalNumberState(r3 -= 1, -1, 2);
}
BOOST_AUTO_TEST_CASE(check_multiplication_operator)
{
	CRational r1(1, 2);
	CRational r2(2, 3);
	CheckRationalNumberState(r1 * r2, 1, 3);
	CheckRationalNumberState(r1 * -3, -3, 2);
	CheckRationalNumberState(7 * r2, 14, 3);
}
BOOST_AUTO_TEST_CASE(check_division_operator)
{
	CRational r1(1, 2);
	CRational r2(2, 3);
	CheckRationalNumberState(r1 / r2, 3, 4);
	CheckRationalNumberState(r1 / 5, 1, 10);
	CheckRationalNumberState(7 / r2, 21, 2);
}
BOOST_AUTO_TEST_CASE(check_pred_multiplication_operator)
{
	CRational r1(1, 2);
	CRational r2(2, 3);
	CheckRationalNumberState(r1 *= r2, 1, 3);
	CRational r3(1, 2);
	CheckRationalNumberState(r3 *= 3, 3, 2);
}
BOOST_AUTO_TEST_CASE(check_pred_division_operator)
{
	CRational r1(1, 2);
	CRational r2(2, 3);
	CheckRationalNumberState(r1 /= r2, 3, 4);
	CRational r3(1, 2);
	CheckRationalNumberState(r3 /= 3, 1, 6);
	CRational r4(3, 4);
	CRational r5(3, 8);
	CheckRationalNumberState(r4 /= r5, 2, 1);
}
BOOST_AUTO_TEST_CASE(check_equal_compare_operator)
{
	CRational r1(1, 2);
	CRational r2(1, 2);
	BOOST_CHECK(r1 == r2);
	CRational r3(2, 3);
	BOOST_CHECK(!(r1 == r3));
	CRational r4(4, 1);
	BOOST_CHECK(r4 == 4);
	BOOST_CHECK_EQUAL(r1 == 4, false);
	CRational r5(3, 1);
	BOOST_CHECK_EQUAL(3 == r5, true);
	BOOST_CHECK_EQUAL(3 == r3, false);
}
BOOST_AUTO_TEST_CASE(check_not_equal_compare_operator)
{
	CRational r1(1, 2);
	CRational r2(1, 2);
	BOOST_CHECK_EQUAL(r1 != r2, false);
	CRational r3(2, 3);
	BOOST_CHECK_EQUAL(r1 != r3, true);
	CRational r4(4, 1);
	BOOST_CHECK_EQUAL(r4 != 4, false);
	BOOST_CHECK_EQUAL(r1 != 7, true);
	CRational r5(3, 1);
	BOOST_CHECK_EQUAL(3 != r5, false);
	BOOST_CHECK_EQUAL(3 != r3, true);
}
BOOST_AUTO_TEST_CASE(check_other_compare_operators)
{
	CRational r1(1, 2);
	CRational r2(1, 3);
	BOOST_CHECK_EQUAL(r1 >= r2, true);
	BOOST_CHECK_EQUAL(r1 <= r2, false);
	CRational r3(3);
	BOOST_CHECK_EQUAL(r3 > 2, true);
	BOOST_CHECK_EQUAL(r1 < 7, true);
	BOOST_CHECK_EQUAL(2 > r3, false);
	BOOST_CHECK_EQUAL(7 < r1, false);
	CRational r4(7, 2);
	BOOST_CHECK_EQUAL(3 <= r4, true);
	CRational r5(8, 2);
	BOOST_CHECK_EQUAL(3 >= r5, false);
}
BOOST_AUTO_TEST_CASE(check_input_operator)
{
	CRational testRational;
	stringstream ss("7/15");
	ss >> testRational;
	BOOST_CHECK_EQUAL(testRational.GetDenominator(), 15);
	BOOST_CHECK_EQUAL(testRational.GetNumerator(), 7);
	ss.clear();
	ss.str("7");
	BOOST_CHECK_THROW(ss >> testRational, invalid_argument);
	ss.clear();
	ss.str("7s/5");
	BOOST_CHECK_THROW(ss >> testRational, runtime_error);
}
BOOST_AUTO_TEST_CASE(check_output_operator)
{
	CRational testRational(7, 15);
	stringstream ss;
	ss << testRational;
	BOOST_CHECK_EQUAL(ss.str(), "7/15");
}
BOOST_AUTO_TEST_CASE(check_to_compound_fraction)
{
	CRational testRational(9, 4);
	auto compoundfraction = testRational.ToCompoundFraction();
	BOOST_CHECK_EQUAL(compoundfraction.first, 2);
	BOOST_CHECK_EQUAL(compoundfraction.second, CRational(1, 4));
	CRational testNegativeRational(-9, 4);
	auto negativeCompoundfraction = testNegativeRational.ToCompoundFraction();
	BOOST_CHECK_EQUAL(negativeCompoundfraction.first, -2);
	BOOST_CHECK_EQUAL(negativeCompoundfraction.second, CRational(-1, 4));
}
BOOST_AUTO_TEST_SUITE_END()
