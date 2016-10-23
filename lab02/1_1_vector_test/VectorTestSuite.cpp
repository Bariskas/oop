#include "stdafx.h"
#include "../1_1_vector/VectorConverting.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(NumericConverterTestSuite)

BOOST_AUTO_TEST_CASE(EmptyInput)
{
	stringstream ss("2 3 4");
	vector<double> workVector;
	try
	{
		workVector = GetVectorFromCin(ss);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	BOOST_REQUIRE_EQUAL(workVector[0], 2);
	BOOST_REQUIRE_EQUAL(workVector[1], 3);
	BOOST_REQUIRE_EQUAL(workVector[2], 4);
}

BOOST_AUTO_TEST_CASE(WrongInput)
{
	string exceptionMessage;
	stringstream ss("2пы 3 4");
	vector<double> workVector;
	try
	{
		workVector = GetVectorFromCin(ss);
	}
	catch (const exception& e)
	{
		exceptionMessage = e.what();
	}
	BOOST_REQUIRE_EQUAL(exceptionMessage, "invalid arguments on input");
}

BOOST_AUTO_TEST_SUITE_END()