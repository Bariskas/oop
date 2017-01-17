#pragma once
#include "CVehicleImpl.h"

template <typename Base, typename Passenger>
class CCarImpl : public CVehicleImpl<Base, Passenger>
{
public:
	CCarImpl(size_t placeCount, MakeOfTheCar makeOfTheCar)
		: CVehicleImpl(placeCount)
		, m_makeOfTheCar(makeOfTheCar)
	{}

	MakeOfTheCar GetMakeOfTheCar()const
	{
		return m_makeOfTheCar;
	}
private:
	MakeOfTheCar m_makeOfTheCar;
};