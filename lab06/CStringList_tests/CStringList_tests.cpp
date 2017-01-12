#include "stdafx.h"
#include "../CStringList/CStringList.h"

struct CStringList_
{
	CStringList list;
	const CStringList& constList = list;
	CStringList_()
	{
		list.Append("1");
		list.Append("2");
		list.Append("3");
	}
};

BOOST_FIXTURE_TEST_SUITE(StringList, CStringList_)
BOOST_AUTO_TEST_CASE(have_iterator)
{
	auto it = list.begin();
	BOOST_CHECK(*it == "1");
	++it;
	BOOST_CHECK(*it == "2");
	++it;
	BOOST_CHECK(*it == "3");
	auto constIt = constList.begin();
	BOOST_CHECK(*constIt == "1");
	++constIt;
	BOOST_CHECK(*constIt == "2");
	++constIt;
	BOOST_CHECK(*constIt == "3");
}
BOOST_AUTO_TEST_CASE(have_reverse_iterator)
{
	auto it = list.rbegin();
	BOOST_CHECK(*it == "3");
}
BOOST_AUTO_TEST_SUITE_END()