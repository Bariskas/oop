#include "stdafx.h"
#include "../CMyArray/CMyArray.h"

struct MyArray_
{
	CMyArray<int> intArray{ 1,2,3 };
	const CMyArray<int> constIntArray{ 1,2,3 };
	CMyArray<int> emptyArray = CMyArray<int>();
};

BOOST_FIXTURE_TEST_SUITE(MyArray, MyArray_)
BOOST_AUTO_TEST_CASE(can_return_count_of_elements)
{
	BOOST_CHECK_EQUAL(intArray.GetSize(), 3);
	BOOST_CHECK_EQUAL(emptyArray.GetSize(), 0);
}
BOOST_AUTO_TEST_CASE(can_append_elements)
{
	BOOST_CHECK_EQUAL(intArray.GetSize(), 3);
	intArray.Append(4);
	BOOST_CHECK_EQUAL(intArray.GetSize(), 4);
	BOOST_CHECK_EQUAL(intArray.GetBack(), 4);

	BOOST_CHECK_EQUAL(emptyArray.GetSize(), 0);
	emptyArray.Append(1);
	BOOST_CHECK_EQUAL(emptyArray.GetSize(), 1);
	BOOST_CHECK_EQUAL(emptyArray.GetBack(), 1);
}
BOOST_AUTO_TEST_CASE(can_get_elements_with_brackets)
{
	BOOST_CHECK_EQUAL(intArray[0], 1);
	BOOST_CHECK_THROW(intArray[6], std::out_of_range);
}
BOOST_AUTO_TEST_CASE(can_be_resized)
{
	intArray.Resize(10);
	BOOST_CHECK_EQUAL(intArray.GetSize(), 10);
	emptyArray.Resize(10);
	BOOST_CHECK_EQUAL(emptyArray.GetSize(), 10);
}
BOOST_AUTO_TEST_CASE(can_be_cleared)
{
	intArray.Clear();
	BOOST_CHECK_EQUAL(intArray.GetSize(), 0);
	BOOST_CHECK_THROW(intArray[1], std::out_of_range);
}
BOOST_AUTO_TEST_CASE(can_be_сopied)
{
	CMyArray<int> copy(intArray);
	BOOST_CHECK_EQUAL(copy.GetSize(), intArray.GetSize());
	BOOST_CHECK_EQUAL(copy[0], intArray[0]);
	BOOST_CHECK_EQUAL(copy[1], intArray[1]);
	BOOST_CHECK_EQUAL(copy[2], intArray[2]);
	emptyArray = intArray;
	BOOST_CHECK_EQUAL(emptyArray.GetSize(), intArray.GetSize());
	BOOST_CHECK_EQUAL(emptyArray[0], intArray[0]);
	BOOST_CHECK_EQUAL(emptyArray[1], intArray[1]);
	BOOST_CHECK_EQUAL(emptyArray[2], intArray[2]);
	BOOST_CHECK_NO_THROW(intArray = intArray);
	BOOST_CHECK_EQUAL(intArray[0], 1);
	BOOST_CHECK_EQUAL(intArray[1], 2);
	BOOST_CHECK_EQUAL(intArray[2], 3);
}
BOOST_AUTO_TEST_CASE(can_be_moved)
{
	CMyArray<int> tempCopy = intArray;
	CMyArray<int> tempCopy2 = intArray;
	CMyArray<int> movedArray(std::move(tempCopy));
	BOOST_CHECK_EQUAL(movedArray.GetSize(), intArray.GetSize());
	BOOST_CHECK_EQUAL(movedArray[0], intArray[0]);
	BOOST_CHECK_EQUAL(movedArray[1], intArray[1]);
	BOOST_CHECK_EQUAL(movedArray[2], intArray[2]);
	emptyArray = std::move(tempCopy2);
	BOOST_CHECK_EQUAL(emptyArray.GetSize(), intArray.GetSize());
	BOOST_CHECK_EQUAL(emptyArray[0], intArray[0]);
	BOOST_CHECK_EQUAL(emptyArray[1], intArray[1]);
	BOOST_CHECK_EQUAL(emptyArray[2], intArray[2]);
}
BOOST_AUTO_TEST_CASE(have_bidirectional_iterator)
{
	BOOST_CHECK(intArray.begin() != intArray.end());

	int i = 1;
	for(auto it = intArray.begin(); it != intArray.end(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, i++);
	}
	i = 3;
	for (auto it = intArray.rbegin(); it != intArray.rend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, i--);
	}

	i = 1;
	for (auto it = constIntArray.begin(); it != constIntArray.end(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, i++);
	}
	i = 3;
	for (auto it = constIntArray.rbegin(); it != constIntArray.rend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, i--);
	}
	BOOST_CHECK(emptyArray.begin() == emptyArray.end());
}
BOOST_AUTO_TEST_SUITE_END()