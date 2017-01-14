#include "stdafx.h"
#include "../Shapes/CLineSegment.h"

using namespace std;

struct LineSegmentFixture
{
	const CPoint startPoint = CPoint(0, 5);
	const CPoint endPoint = CPoint(0, 0);
	const string outlineColor = "0000FFFF";
	const CLineSegment lineSegment;
	LineSegmentFixture()
		: lineSegment(startPoint, endPoint, outlineColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegmentFixture)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const IShape*>(&lineSegment));
}

BOOST_AUTO_TEST_CASE(has_start_and_end_points)
{
	BOOST_CHECK(lineSegment.GetStartPoint() == CPoint(0, 5));
	BOOST_CHECK(lineSegment.GetEndPoint() == CPoint(0, 0));
}

BOOST_AUTO_TEST_CASE(has_outline_color)
{
	BOOST_CHECK_EQUAL(lineSegment.GetOutlineColor(), outlineColor);
}

BOOST_AUTO_TEST_CASE(has_area)
{
	BOOST_CHECK_CLOSE_FRACTION(lineSegment.GetArea(), 0, DBL_EPSILON);
}

BOOST_AUTO_TEST_CASE(has_perimeter)
{
	BOOST_CHECK_CLOSE_FRACTION(lineSegment.GetPerimeter(), 5, DBL_EPSILON);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const auto expectedString = "Shape: line Area: 0 Perimeter: 5\nfrom: 0:5 to: 0:0\n";
	string st = lineSegment.ToString();
	BOOST_CHECK_EQUAL(lineSegment.ToString(), expectedString);
}
BOOST_AUTO_TEST_SUITE_END()