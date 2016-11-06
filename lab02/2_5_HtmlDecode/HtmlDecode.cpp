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

string DecodeHtmlEntities(const string& toDecode)
{
	static map<string, string> htmlEntities = {
		{"&quot;", "\""}, {"&apos;", "\'"}, {"&lt;", "<"}, {"&gt;", ">"}, {"&amp;", "&"}
	}; 

	string result;
	result.reserve(toDecode.length());

	const char* stringToDecode = toDecode.c_str();

	for (size_t i = 0; i < toDecode.size();)
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

	return result;
}