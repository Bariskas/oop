#include "stdafx.h"
#include "../Shapes/ShapeUtils.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/CCircle.h"

using namespace std;

struct ShapeUtilsFixture
{
	ShapePtr rectangle;
	ShapePtr circle;
	ShapePtr triangle;
	vector<ShapePtr> shapes;
	double expectedMaxArea = 400;
	double expectedMinPerimeter = 17.0711;
	ShapeUtilsFixture()
	{
		rectangle = make_shared<CRectangle>(CRectangle(CPoint(20, 0), 20, 20, "FFFFFFF", "FFFFFFF"));
		circle = make_shared<CCircle>(CCircle(CPoint(0, 0), 5, "FFFFFFF", "FFFFFFF"));
		triangle = make_shared<CTriangle>(CTriangle(CPoint(0, 0), CPoint(0, 5), CPoint(5, 0), "FFFFFFF", "FFFFFFF"));
		shapes = vector<ShapePtr>{ rectangle, circle, triangle };
	}
};

BOOST_FIXTURE_TEST_SUITE(ShapeUtils, ShapeUtilsFixture)
BOOST_AUTO_TEST_CASE(distance_beetwen_two_points)
{
	BOOST_CHECK_EQUAL(GetDistanceBeetwen(CPoint(0, 0), CPoint(0, 0)), 0);
	BOOST_CHECK_EQUAL(GetDistanceBeetwen(CPoint(0, 0), CPoint(10, 0)), 10);
}
BOOST_AUTO_TEST_CASE(can_find_shape_with_max_area)
{
	ShapePtr maxAreaShape = GetShapeWithMaxArea(shapes);
	BOOST_CHECK_EQUAL(maxAreaShape->GetArea(), expectedMaxArea);
}
BOOST_AUTO_TEST_CASE(can_find_shape_with_min_perimeter)
{
	ShapePtr minPerimeterShape = GetShapeWithMinPerimeter(shapes);
	BOOST_CHECK_CLOSE_FRACTION(minPerimeterShape->GetPerimeter(), expectedMinPerimeter, 0.0001);
}
BOOST_AUTO_TEST_SUITE_END()