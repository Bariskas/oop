// 2_5_HtmlDecode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

int main()
{
	vector<string> inputVector(istream_iterator<string>(cin), (istream_iterator<string>()));
	for (auto strToDecode : inputVector)
	{
		cout << DecodeHtmlEntities(strToDecode) << endl;
	}
    return 0;
}

