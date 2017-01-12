#pragma once
#include "stdafx.h"

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less = std::less<T>)
{
	if (arr.size() == 0)
	{
		return false;
	}

	auto maxEl = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (less(*maxEl, *it))
		{
			maxEl = it;
		}
	}
	maxValue = *maxEl;
	return true;
}
