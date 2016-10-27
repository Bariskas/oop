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
					//stringToDecode += codedHtmlEntitySize;
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

	/*
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
	*/
	cout << result << endl;
	return result;
}