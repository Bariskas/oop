#include "stdafx.h"
#include "Car.h"

using namespace std;

const CCar::TranmissionSpeedMap CCar::m_transmissionSpeedMap{
	{ -1,{ 0, 20 } },
	{ 0,{ INT_MIN, INT_MAX } },
	{ 1,{ 0, 30 } },
	{ 2,{ 20, 50 } },
	{ 3,{ 30, 60 } },
	{ 4,{ 40, 90 } },
	{ 5,{ 50, 150 } }
};

const CCar::DirectionNameMap CCar::m_directionNameMap{
	{ Direction::Backward, "Backward" },
	{ Direction::Forward, "Forward" },
	{ Direction::Holding, "Holding" }
};

bool CCar::IsTurnedOn() const
{
	return m_isTurnedOn;
}

void CCar::TurnOnEngine()
{
	if (CheckForTurnedOffEngine())
	{
		m_isTurnedOn = true;
	}
}

void CCar::TurnOffEngine()
{
	if (CheckForTurnedOnEngine()
		&& CheckForZeroSpeed()
		&& CheckForZeroTransmission())
	{
		m_isTurnedOn = false;
	}
}

void CCar::SetTransmission(int transmission)
{
	if (CanChangeTransmission(transmission))
	{
		m_transmission = transmission;
	}
}

void CCar::SetSpeed(int speed)
{
	if (CanChangeSpeed(speed))
	{
		m_speed = (m_transmission == -1 || GetDirection() == Direction::Backward) ? -speed : speed;
	}
}

int CCar::GetSpeed() const
{
	return abs(m_speed);
}

int CCar::GetTransmission() const
{
	return m_transmission;
}

Direction CCar::GetDirection() const
{
	Direction direction = Direction::Holding;
	if (m_speed < 0)
	{
		direction = Direction::Backward;
	}
	else if (m_speed > 0)
	{
		direction = Direction::Forward;
	}
	return direction;
}

bool CCar::CanChangeTransmission(int transmission) const
{
	bool canChange = false;

	if (CheckForTurnedOnEngine()
		&& CheckForAlreadySetTransmission(transmission)
		&& CheckIsSpeedAllowedByTransmission(GetSpeed(), transmission)
		&& CheckForSupportingCurrentDirectionByTransmission(transmission))
	{
		canChange = true;
	}

	return canChange;
}

bool CCar::CanChangeSpeed(int speed) const
{
	bool canChange = false;

	if (CheckForTurnedOnEngine()
		&& CheckForNonNegativeInputSpeed(speed)
		&& CheckIsSpeedAllowedByTransmission(speed, m_transmission)
		&& CheckForIncreasingSpeedNonOnZeroTransmission(speed))
	{
		canChange = true;
	}

	return canChange;
}

std::string CCar::DirectionToString(Direction direction)
{
	auto it = m_directionNameMap.find(direction);
	return it->second;
}

bool CCar::CheckIsSpeedAllowedByTransmission(int speed, int transmission) const
{
	auto it = m_transmissionSpeedMap.find(transmission);
	if (it == m_transmissionSpeedMap.end())
	{
		throw runtime_error(to_string(transmission) + " not exist");
	}
	if (speed < it->second.first || speed > it->second.second)
	{
		throw runtime_error(to_string(transmission) + " can accept speed between " + to_string(it->second.first)
			+ " and " + to_string(it->second.second) + " ; speed = " + to_string(speed));
	}
	return true;
}

bool CCar::CheckForSupportingCurrentDirectionByTransmission(int transmission) const
{
	if (transmission == -1 && GetDirection() == Direction::Holding
		|| transmission > 0 && GetDirection() != Direction::Backward
		|| transmission == 0)
	{
		return true;
	}
	throw runtime_error(to_string(transmission) + " transmission dont supporting current direction " + DirectionToString(GetDirection()));
}

bool CCar::CheckForTurnedOffEngine() const
{
	if (!m_isTurnedOn)
	{
		return true;
	}
	throw runtime_error("Engine is turned on.");
}

bool CCar::CheckForTurnedOnEngine() const
{
	if (m_isTurnedOn)
	{
		return true;
	}
	throw runtime_error("Engine is turned off.");
}

bool CCar::CheckForZeroSpeed() const
{
	if (m_speed == 0)
	{
		return true;
	}
	throw runtime_error("Car is moving.");
}

bool CCar::CheckForZeroTransmission() const
{
	if (m_transmission == 0)
	{
		return true;
	}
	throw runtime_error("Car have non zero transmission.");
}

bool CCar::CheckForAlreadySetTransmission(int tranmission) const
{
	if (tranmission != m_transmission)
	{
		return true;
	}
	throw runtime_error(to_string(tranmission) + " transmission already setted.");
}

bool CCar::CheckForIncreasingSpeedNonOnZeroTransmission(int speed) const
{
	if (!(m_transmission == 0 && speed > abs(m_speed)))
	{
		return true;
	}
	throw runtime_error("Cant increase speed on zero transmission.");
}

bool CCar::CheckForNonNegativeInputSpeed(int speed) const
{
	if (speed < 0)
	{
		throw runtime_error("Speed can't be negative.");
	}
	return true;
}
