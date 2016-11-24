// TestProjects.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

void testStreamString()
{
	string ts;
	stringstream ss("123   ");
	ss >> ts;
	stringstream ss2(ts);
	assert(ss2.str() == "123   ");
}

void testStreamNumber()
{
	int testNumber;
	stringstream ss("123   ");
	ss >> testNumber;
	cout << ss.str() << endl;
	cout << testNumber << endl;
	cout << ss.good() << endl;
	cout << ss.eof() << endl;
	cout << ss.fail() << endl;
	cout << ss.bad() << endl;
	assert(ss.str() == "");
}

void testSpaceStream()
{
	string s;
	stringstream ss(" ");
	ss >> s;
	//getline(ss, s);
	cout << ss.str() << endl;
	cout << ss.good() << endl;
	cout << ss.eof() << endl;
	cout << ss.fail() << endl;
	cout << ss.bad() << endl;
	assert(s == "");
	assert(ss.str() == " ");
}

void testSpaceIntStream()
{
	int s;
	stringstream ss(" ");
	ss >> s;
	cout << s << endl;
	cout << ss.str() << endl;
	cout << ss.good() << endl;
	cout << ss.eof() << endl;
	cout << ss.fail() << endl;
	cout << ss.bad() << endl;
	assert(ss.str() == " ");
}

void testTwiceRead()
{
	stringstream("hey");
	string first, second;
	cout << << ss.good() << endl;
	cout << << ss.eof() << endl;
	cout << << ss.fail() << endl;
	cout << << ss.bad() << endl;
}

int main()
{
	testTwiceRead();
	getchar();
	return 0;
}