#pragma once
#include "stdafx.h"

enum MakeOfTheCar
{
	BMW,
	MITSUBISHI,
	FORD,
	MERCEDES,
	TOYOTA,
	KIA,
	FERRARI,
	PORSCHE,
	LEXUS,
	NISSAN,
	INIFINITI,
};

template <typename Base, typename Passenger>
class CVehicleImpl : public Base
{
public:
	explicit CVehicleImpl(size_t placeCount)
		: m_placeCount(placeCount)
		, m_passengers()
	{}

	void AddPassenger(std::shared_ptr<Passenger> pPassenger)
	{
		if (!IsFull())
		{
			m_passengers.push_back(pPassenger);
		}
		else
		{
			throw std::logic_error("Vehicle is full");
		}
	}

	Passenger const& GetPassenger(size_t index)const
	{
		return *m_passengers[index];
	}

	void RemovePassenger(size_t index)
	{
		m_passengers.erase(m_passengers.begin() + index);
	}

	bool IsEmpty()const
	{
		return m_passengers.size() == 0;
	};

	bool IsFull()const
	{
		return m_placeCount == m_passengers.size();
	}

	size_t GetPlaceCount()const
	{
		return m_placeCount;
	}

	size_t GetPassengerCount()const
	{
		return m_passengers.size();
	}

	void RemoveAllPassengers()
	{
		m_passengers.clear();
	}
private:
	size_t m_placeCount;
	std::vector<std::shared_ptr<Passenger>> m_passengers;
};