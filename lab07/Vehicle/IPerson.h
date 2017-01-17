#pragma once
#include "stdafx.h"

class IPerson
{
public:
	virtual ~IPerson() {};
	virtual std::string GetName()const = 0;
};