#include "stdafx.h"
#include "../Shapes/CPoint.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Point)
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_doubles)
	{
		CPoint testPoint(6., 5.);
		BOOST_CHECK_EQUAL(testPoint.x, 6);
		BOOST_CHECK_EQUAL(testPoint.y, 5);
	}
	BOOST_AUTO_TEST_CASE(can_be_readed_from_stream)
	{
		stringstream ss("5.5 6.6");
		CPoint testPoint;
		ss >> testPoint;
		BOOST_CHECK_EQUAL(testPoint.x, 5.5);
		BOOST_CHECK_EQUAL(testPoint.y, 6.6);
	}
	BOOST_AUTO_TEST_CASE(can_be_compared_on_equalence)
	{
		CPoint testPoint1(1, 1);
		CPoint testPoint2(2, 2);
		BOOST_CHECK(testPoint1 == testPoint1);
		BOOST_CHECK(!(testPoint1 == testPoint2));
	}
BOOST_AUTO_TEST_SUITE_END()