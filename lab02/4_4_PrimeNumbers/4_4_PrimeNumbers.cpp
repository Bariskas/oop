// 4_4_PrimeNumbers.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "PrimeNumbers.h"

using namespace std;

static const int UPPER_BOUND = 100000000;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong arguments: <upperBound>" << endl;
	}

	set<int> primeNumbers = GetPrimeNumbers(atoi(argv[1]));

	for (auto &primeNumber : primeNumbers)
	{
		cout << primeNumber << " ";
	}

	getchar();
    return 0;
}

