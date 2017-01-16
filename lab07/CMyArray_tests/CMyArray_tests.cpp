﻿#include "stdafx.h"
#include "../CMyArray/CMyArray.h"

struct MyArray_
{
	CMyArray<int> intArray{ 1,2,3 };
	const CMyArray<int> constIntArray{ 1,2,3 };
	CMyArray<int> reserveCapacityArray;
	CMyArray<int> emptyArray = CMyArray<int>();
	MyArray_()
	{
		reserveCapacityArray = CMyArray<int>(5);
		reserveCapacityArray.Resize(3);
		reserveCapacityArray[0] = 1;
		reserveCapacityArray[1] = 2;
		reserveCapacityArray[2] = 3;
	}
};

BOOST_FIXTURE_TEST_SUITE(MyArray, MyArray_)
	BOOST_FIXTURE_TEST_SUITE(Constrcturs, MyArray_)
		BOOST_AUTO_TEST_CASE(have_count_constructor)
		{
			CMyArray<int> defaultValuesArray(5);
			for (auto it = defaultValuesArray.begin(); it != defaultValuesArray.end(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, 0);
			}
			BOOST_CHECK_EQUAL(defaultValuesArray.GetSize(), 5);
		}
		BOOST_AUTO_TEST_CASE(have_init_list_constructor)
		{
			CMyArray<int> testArray{1, 2, 3, 4, 5};
			int value = 1;
			for (auto it = testArray.begin(); it != testArray.end(); ++it, ++value)
			{
				BOOST_CHECK_EQUAL(*it, value);
			}
			BOOST_CHECK_EQUAL(testArray.GetSize(), 5);
		}
	BOOST_AUTO_TEST_SUITE_END()
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
BOOST_AUTO_TEST_SUITE(resizing)
	BOOST_AUTO_TEST_CASE(new_size_less_then_initial)
	{
		BOOST_CHECK_EQUAL(intArray.GetCapacity(), 3);
		intArray.Resize(2);
		BOOST_CHECK_EQUAL(intArray.GetSize(), 2);
		BOOST_CHECK_EQUAL(intArray[0], 1);
		BOOST_CHECK_EQUAL(intArray[1], 2);
	}
	BOOST_AUTO_TEST_CASE(new_size_bigger_then_initial_but_less_then_capacity)
	{
		BOOST_CHECK_EQUAL(reserveCapacityArray.GetSize(), 3);
		BOOST_CHECK_EQUAL(reserveCapacityArray.GetCapacity(), 5);
		reserveCapacityArray.Resize(4);
		BOOST_CHECK_EQUAL(reserveCapacityArray.GetSize(), 4);
		BOOST_CHECK_EQUAL(reserveCapacityArray.GetCapacity(), 5);
		BOOST_CHECK_EQUAL(reserveCapacityArray[0], 1);
		BOOST_CHECK_EQUAL(reserveCapacityArray[1], 2);
		BOOST_CHECK_EQUAL(reserveCapacityArray[2], 3);
		BOOST_CHECK_EQUAL(reserveCapacityArray[3], 0);
	}
	BOOST_AUTO_TEST_CASE(new_size_bigger_then_initial)
	{
		BOOST_CHECK_EQUAL(intArray.GetCapacity(), 3);
		intArray.Resize(4);
		BOOST_CHECK_EQUAL(intArray.GetCapacity(), 4);
		BOOST_CHECK_EQUAL(intArray.GetSize(), 4);
		BOOST_CHECK_EQUAL(intArray[0], 1);
		BOOST_CHECK_EQUAL(intArray[1], 2);
		BOOST_CHECK_EQUAL(intArray[2], 3);
		BOOST_CHECK_EQUAL(intArray[3], 0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(can_be_cleared)
{
	intArray.Clear();
	BOOST_CHECK_EQUAL(intArray.GetSize(), 0);
	BOOST_CHECK_THROW(intArray[1], std::out_of_range);
}
BOOST_AUTO_TEST_CASE(can_be_copied)
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