#include "stdafx.h"
#include "NumberUtils.h"

using namespace std;

int NumberUtils::Gcd(int a, int b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}
	return a;
}

int NumberUtils::Lcm(int a, int b)
{
	return a / Gcd(a, b) * b;
}

int NumberUtils::StrToInt(std::string const& str)
{
	bool isAllDigits = all_of(str.begin(), str.end(), [](char ch) {return isdigit(ch); });
	if (!isAllDigits)
	{
		throw runtime_error("Bad number string " + str);
	}
	return stoi(str);
}
