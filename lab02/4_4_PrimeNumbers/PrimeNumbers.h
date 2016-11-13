#pragma once
#include "stdafx.h"

std::set<int> GetPrimeNumbers(int upperBound);
void WeedOutComplexNumbers(std::vector<bool>& primeFlags, int primeNumberIndex);