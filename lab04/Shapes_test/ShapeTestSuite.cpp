#include "stdafx.h"

struct ShapeTexture
{

};

BOOST_FIXTURE_TEST_SUITE(Shape, ShapeTexture)
BOOST_AUTO_TEST_CASE(dummy_Test)
{
	BOOST_CHECK(true);
}
BOOST_AUTO_TEST_SUITE_END()