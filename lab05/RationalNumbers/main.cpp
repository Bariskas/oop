#include "stdafx.h"
#include "CRational.h"

using namespace std;

int main()
{
	stringstream ss;
	ss << "1/3  1/5";
	CRational r1;
	CRational r2;
	ss >> r1 >> r2;
	cout << r1 << " " << r2 << endl;
	cout << r1 + r2 << endl;
    return 0;
}

