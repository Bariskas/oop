// 2_5_HtmlDecode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

int main()
{
	string toDecode;
	cin >> toDecode;
	DecodeHtmlEntities(toDecode);
    return 0;
}

