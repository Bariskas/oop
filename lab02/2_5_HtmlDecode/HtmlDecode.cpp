#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

/*
�	�(������� �������)  ���������� �� &quot;
�	�(��������) ���������� �� &apos;
�	< (���� ������) ���������� �� &lt;
�	>(���� ������) ���������� �� &gt;
�	& (���������)���������� �� &amp;
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