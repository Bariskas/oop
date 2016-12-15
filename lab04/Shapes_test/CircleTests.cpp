#include "stdafx.h"
#include "../Shapes/CCircle.h"
#include "../Shapes/CCanvas.h"

using namespace std;

struct CircleFixture
{
	const CPoint center = CPoint(10.0, 10.0);
	const double radius = 5.0;
	const string outlineColor = "0000FFFF";
	const string fillColor = "FF00FFFF";
	const CCircle circle;
	CircleFixture()
		: circle(center, radius, outlineColor, fillColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Circle, CircleFixture)
	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const ISolidShape*>(&circle));
	}

	BOOST_AUTO_TEST_CASE(is_a_solid_body)
	{
		BOOST_CHECK(static_cast<const IShape*>(&circle));
	}

	BOOST_AUTO_TEST_CASE(has_a_center)
	{
		BOOST_CHECK(circle.GetCenter() == center);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(circle.GetOutlineColor(), outlineColor);
	}

	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK_EQUAL(circle.GetFillColor(), fillColor);
	}

	BOOST_AUTO_TEST_CASE(has_radius)
	{
		BOOST_CHECK_CLOSE_FRACTION(circle.GetRadius(), radius, DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(circle.GetArea(), radius * radius * M_PI, DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(has_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(circle.GetPerimeter(), 2.0 * radius * M_PI, DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = "Shape: circle Area: 78.538 Perimeter: 31.416\nCenter: 10.0:10.0 Radius: 5\n";
		string st = circle.ToString();
		BOOST_CHECK_EQUAL(circle.ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()