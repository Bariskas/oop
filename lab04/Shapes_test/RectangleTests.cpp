#include "stdafx.h"
#include "../Shapes/SfmlUtils.h"
#include "../Shapes/ShapeUtils.h"
#include "../Shapes/CCanvas.h"
#include "../Shapes/CRectangle.h"

using namespace std;

struct RectangleFixture
{
	const CPoint leftTopPoint = CPoint(0, 5);
	double width = 10;
	double height = 5;
	const string outlineColor = "0000FFFF";
	const string fillColor = "FF00FFFF";
	const CRectangle rectangle;
	RectangleFixture()
		: rectangle(leftTopPoint, width, height, outlineColor, fillColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, RectangleFixture)
	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const IShape*>(&rectangle));
	}

	BOOST_AUTO_TEST_CASE(is_a_solid_body)
	{
		BOOST_CHECK(static_cast<const ISolidShape*>(&rectangle));
	}

	BOOST_AUTO_TEST_CASE(has_height_width_and_leftTopVertex)
	{
		BOOST_CHECK(rectangle.GetLeftTop() == CPoint(0, 5));
		BOOST_CHECK(rectangle.GetWidth() == 10);
		BOOST_CHECK(rectangle.GetHeight() == 5);
		BOOST_CHECK(rectangle.GetRightBottom() == CPoint(10, 0));
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetOutlineColor(), outlineColor);
	}

	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK_EQUAL(rectangle.GetFillColor(), fillColor);
	}

	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(rectangle.GetArea(), 50, DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(has_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(rectangle.GetPerimeter(), 30, DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = "Shape: rectangle Area: 50 Perimeter: 30\nwidth: 10 height: 5 left top point: 0:5\n";
		string st = rectangle.ToString();
		BOOST_CHECK_EQUAL(rectangle.ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()