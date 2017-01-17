#pragma once
#include "IPerson.h"

class IRacer : public IPerson
{
public:
	virtual ~IRacer() {};
	virtual size_t GetAwardsCount()const = 0;
};
