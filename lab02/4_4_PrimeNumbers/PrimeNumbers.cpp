#include "stdafx.h"
#include "PrimeNumbers.h"

using namespace std;

std::set<int> GetPrimeNumbers(int upperBound)
{
	vector<bool> primeFlags(upperBound + 1, true);

	if (upperBound >= 2)
	{
		WeedOutComplexNumbers(primeFlags, 2);
	}

	int enoughRightIndex = (int)ceil(sqrt(primeFlags.size()));
	for (int i = 3; i < enoughRightIndex; i += 2)
	{
		if (primeFlags[i])
		{
			WeedOutComplexNumbers(primeFlags, i);
		}
	}

	std::set<int> result;
	for (int i = 2; i < upperBound; ++i)
	{
		if (primeFlags[i])
		{
			result.insert(result.end(), i);
		}
	}
	
	return result;
}

void WeedOutComplexNumbers(vector<bool>& primeFlags, int primeNumberIndex)
{
	for (size_t j = primeNumberIndex * primeNumberIndex; j < primeFlags.size(); j += primeNumberIndex)
	{
		primeFlags[j] = false;
	}
}