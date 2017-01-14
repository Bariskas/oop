#include "stdafx.h"
#include "../Shapes/SfmlUtils.h"
#include "../Shapes/ShapeUtils.h"
#include "../Shapes/CCanvas.h"
#include "../Shapes/CTriangle.h"

using namespace std;

struct TriangleFixture
{
	const CPoint vertex1 = CPoint(0, 0);
	const CPoint vertex2 = CPoint(5, 0);
	const CPoint vertex3 = CPoint(0, 5);
	const string outlineColor = "0000FFFF";
	const string fillColor = "FF00FFFF";
	const CTriangle triangle;
	TriangleFixture()
		: triangle(vertex1, vertex2, vertex3, outlineColor, fillColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Triangle, TriangleFixture)
	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const IShape*>(&triangle));
	}

	BOOST_AUTO_TEST_CASE(is_a_solid_body)
	{
		BOOST_CHECK(static_cast<const ISolidShape*>(&triangle));
	}

	BOOST_AUTO_TEST_CASE(has_vertices)
	{
		BOOST_CHECK(triangle.GetVertex1() == vertex1);
		BOOST_CHECK(triangle.GetVertex2() == vertex2);
		BOOST_CHECK(triangle.GetVertex3() == vertex3);
	}

	BOOST_AUTO_TEST_CASE(has_outline_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), outlineColor);
	}

	BOOST_AUTO_TEST_CASE(has_fill_color)
	{
		BOOST_CHECK_EQUAL(triangle.GetFillColor(), fillColor);
	}

	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(triangle.GetArea(), 12.5, DBL_EPSILON);
	}

	BOOST_AUTO_TEST_CASE(has_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(triangle.GetPerimeter(), 17.0711, 0.0001);
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const auto expectedString = "Shape: triangle Area: 12.5 Perimeter: 17.0711\nvertex1: 0:0 vertex2: 5:0 vertex3: 0:5\n";
		string st = triangle.ToString();
		BOOST_CHECK_EQUAL(triangle.ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()