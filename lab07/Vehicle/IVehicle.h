#pragma once
#include "IBasicVechicle.h"
#include "IPerson.h"

template<typename Passenger>
class IVehicle : public IBasicVechicle
{
public:
	virtual ~IVehicle() {};
	virtual void AddPassenger(std::shared_ptr<Passenger> pPassenger) = 0;
	virtual Passenger const& GetPassenger(size_t index)const = 0;
	virtual void RemovePassenger(size_t index) = 0;
};