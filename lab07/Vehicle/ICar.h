#pragma once
#include "IVehicle.h"

template<typename Passenger>
class ICar : IVehicle<Passenger>
{
public:
	virtual ~ICar() {};
	virtual MakeOfTheCar GetMakeOfTheCar()const = 0;
};

