#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

/*
Х	У(двойна€ кавычка)  замен€етс€ на &quot;
Х	С(апостроф) замен€етс€ на &apos;
Х	< (знак меньше) замен€етс€ на &lt;
Х	>(знак больше) замен€етс€ на &gt;
Х	& (амперсанд)замен€етс€ на &amp;
*/

void DecodeHtmlEntities(const string& toDecode)
{
	static map<string, string> htmlEntities = {
		{"&quot;", "\""}, {"&apos;", "\'"}, {"&lt;", "<"}, {"&gt;", ">"}, {"&amp;", "&"}
	}; 

	string result;
	result.reserve(toDecode.length());

	for (auto it = toDecode.begin(); it != toDecode.end(); ++it)
	{
		if (*it != '&')
		{
			result.push_back(*it);
		}
		else
		{
			for (const auto& entity : htmlEntities)
			{
				toDecode.compare(it - toDecode.begin(), entity.first.length(), entity.first);
			}
		}
	}

}