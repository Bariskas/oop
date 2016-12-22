#include "stdafx.h"
#include "../RationalNumbers/CRational.h"

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
BOOST_AUTO_TEST_CASE(can_be_represent_like_double)
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
BOOST_AUTO_TEST_SUITE_END()
