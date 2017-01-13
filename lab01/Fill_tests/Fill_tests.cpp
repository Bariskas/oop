#include "stdafx.h"
#include "../Fill/Filler.h"

using namespace std;

struct Fill_
{
	Filler filler = Filler(5);
	void CompareMaps(stringstream& sourceMap, string expectedResult) const
	{
		stringstream result;
		filler.Fill(sourceMap, result);
		BOOST_CHECK_EQUAL(result.str(), expectedResult);
	}
};

BOOST_FIXTURE_TEST_SUITE(Fill, Fill_)
BOOST_AUTO_TEST_CASE(without_fountain)
{
	stringstream sourceMap(R"(#####
#   #
#   #
#   #
#####)");
	string expectedResult(R"(#####
#   #
#   #
#   #
#####
)");
	CompareMaps(sourceMap, expectedResult);
}
BOOST_AUTO_TEST_CASE(with_surrounded_fountain)
{
	stringstream sourceMap(R"(#####
#   #
#O  #
#   #
#####)");
	string expectedResult(R"(#####
#+++#
#O++#
#+++#
#####
)");
	CompareMaps(sourceMap, expectedResult);
}
BOOST_AUTO_TEST_CASE(with_a_hole_in_the_fence)
{
	stringstream sourceMap(R"(#####
#O  #
## ##)");
	string expectedResult(R"(#####
#O++#
##+##
+++++
+++++
)");
	CompareMaps(sourceMap, expectedResult);
}
BOOST_AUTO_TEST_CASE(with_only_fountain)
{
	stringstream sourceMap(R"(O)");
	string expectedResult(R"(O++++
+++++
+++++
+++++
+++++
)");
	CompareMaps(sourceMap, expectedResult);
}
BOOST_AUTO_TEST_SUITE_END()