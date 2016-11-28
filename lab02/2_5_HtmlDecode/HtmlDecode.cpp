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
	static vector<pair<string, string>> htmlEntities = {
		{"&quot;", "\""}, {"&apos;", "\'"}, {"&lt;", "<"}, {"&gt;", ">"}, {"&amp;", "&"}
	}; 

	string result;
	result.reserve(toDecode.length());

	for (size_t i = 0; i < toDecode.size();)
	{
		if (toDecode[i] == '&')
		{
			bool isEntityDetected = false;

			auto it = find_if(htmlEntities.begin(), htmlEntities.end(), [&](pair<string, string> & entity) {
				return (toDecode.compare(i, entity.first.length(), entity.first) == 0);
			});

			if (it != htmlEntities.end())
			{
				i += it->first.length();
				isEntityDetected = true;
				result.append(it->second);
			}
			else
			{
				result.push_back(toDecode[i]);
				i++;
			}
		}
		else
		{
			result.push_back(toDecode[i]);
			++i;
		}
	}

	return result;
}