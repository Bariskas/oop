#pragma once
#include "IRacer.h"
#include "CPersonImpl.h"

class CRacer : public CPersonImpl<IRacer>
{
public:
	CRacer(std::string name, size_t awardsCount)
		: CPersonImpl(name)
		, m_awardsCount(awardsCount)
	{}

	size_t GetAwardsCount()const final
	{
		return m_awardsCount;
	}
private:
	size_t m_awardsCount;
};
