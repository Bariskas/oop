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

string DecodeHtmlEntities(const string& toDecode)
{
	static map<string, string> htmlEntities = {
		{"&quot;", "\""}, {"&apos;", "\'"}, {"&lt;", "<"}, {"&gt;", ">"}, {"&amp;", "&"}
	}; 

	string result;
	result.reserve(toDecode.length());

	const char* stringToDecode = toDecode.c_str();

	for (auto i = 0; i < toDecode.size();)
	{
		if (stringToDecode[i] == '&')
		{
			bool isEntityDetected = false;
			for (auto& entity : htmlEntities)
			{
				auto codedHtmlEntity = get<0>(entity);
				auto codedHtmlEntitySize = codedHtmlEntity.size();
				if (std::strncmp(stringToDecode + i, codedHtmlEntity.c_str(), codedHtmlEntitySize) == 0)
				{
					result.append(get<1>(entity));
					i += codedHtmlEntitySize;
					isEntityDetected = true;
				}
			}
			if (!isEntityDetected)
			{
				result.push_back(stringToDecode[i]);
				i++;
			}
		}
		else
		{
			result.push_back(stringToDecode[i]);
			++i;
		}

	}

	cout << result << endl;
	return result;
}