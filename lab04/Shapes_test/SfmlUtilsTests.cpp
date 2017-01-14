#include "stdafx.h"
#include "../Shapes/SfmlUtils.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(SfmlUtils)
BOOST_AUTO_TEST_CASE(string_can_ve_converted_to_unsigned_long)
{
	unsigned int color = ColorFromStringToUnsigned("0x00FF00FF");
	BOOST_CHECK_EQUAL(color, 0x00FF00FF);
}
BOOST_AUTO_TEST_SUITE_END()