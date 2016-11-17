#include "stdafx.h"
#include "Car.h"

using namespace std;

CCar::CCar()
	: m_transmissionSpeedMap({
		{ -1,{ 0, 20 } },
		{ 0,{ INT_MIN, INT_MAX } },
		{ 1,{ 0, 30 } },
		{ 2,{ 20, 50 } },
		{ 3,{ 30, 60 } },
		{ 4,{ 40, 90 } },
		{ 5,{ 50, 150 } }
	})
	, m_directionNameMap({
		{ Direction::Backward, "Backward" },
		{ Direction::Forward, "Forward" },
		{ Direction::Holding, "Holding" }
	})
	, m_isExceptionEnabled(false)
{}

CCar::CCar(bool enableException = false)
	: m_transmissionSpeedMap({
		{ -1,{ 0, 20 } },
		{ 0,{ INT_MIN, INT_MAX } },
		{ 1,{ 0, 30 } },
		{ 2,{ 20, 50 } },
		{ 3,{ 30, 60 } },
		{ 4,{ 40, 90 } },
		{ 5,{ 50, 150 } }
	})
	, m_directionNameMap({
		{ Direction::Backward, "Backward" },
		{ Direction::Forward, "Forward" },
		{ Direction::Holding, "Holding" }
	})
	, m_isExceptionEnabled(enableException)
{}

bool CCar::IsTurnedOn() const
{
	return m_isTurnedOn;
}

bool CCar::TurnOnEngine()
{
	bool isTurnedOn = false;

	if (CheckForTurnedOffEngine())
	{
		m_isTurnedOn = true;
		isTurnedOn = true;
	}

	return isTurnedOn;
}

bool CCar::TurnOffEngine()
{
	bool isTurnedOff = false;

	if (CheckForTurnedOnEngine()
		&& CheckForZeroSpeed()
		&& CheckForZeroTransmission())
	{
		isTurnedOff = true;
		m_isTurnedOn = false;
	}

	return isTurnedOff;
}

bool CCar::SetTransmission(int transmission)
{
	bool isTranmissionChanged = false;

	if (CanChangeTransmission(transmission))
	{
		m_transmission = transmission;
		isTranmissionChanged = true;
	}

	return isTranmissionChanged;
}

bool CCar::SetSpeed(int speed)
{
	bool isSpeedChanged = false;

	if (CanChangeSpeed(speed))
	{
		m_speed = speed;
		isSpeedChanged = true;
	}
	SetDirection(speed);

	return isSpeedChanged;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

int CCar::GetTransmission() const
{
	return m_transmission;
}

string CCar::GetDirection() const
{
	auto it = m_directionNameMap.find(m_direction);
	return it->second;
}

bool CCar::CanChangeTransmission(int transmission) const
{
	bool canChange = false;

	if (CheckForTurnedOnEngine()
		&& CheckForAlreadySettedTransmission(transmission)
		&& CheckIsSpeedAllowedByTransmission(m_speed, transmission)
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

void CCar::SetDirection(int speed)
{
	if (speed == 0)
	{
		m_direction = Direction::Holding;
	}
	else if (m_transmission != 0)
	{
		if (m_transmission == -1)
		{
			m_direction = Direction::Backward;
		}
		else
		{
			m_direction = Direction::Forward;
		}
	}
}

bool CCar::CheckIsSpeedAllowedByTransmission(int speed, int transmission) const
{
	auto it = m_transmissionSpeedMap.find(transmission);
	if (it == m_transmissionSpeedMap.end())
	{
		return BeepBeepException(to_string(transmission) + " not exist");
	}
	if (speed < it->second.first || speed > it->second.second)
	{
		return BeepBeepException(to_string(transmission) + " can accept speed between " + to_string(it->second.first)
			+ " and " + to_string(it->second.second) + " ; speed = " + to_string(speed));
	}
	return true;
}

bool CCar::CheckForSupportingCurrentDirectionByTransmission(int transmission) const
{
	if (transmission == -1 && m_direction != Direction::Forward
		|| transmission > 0 && m_direction != Direction::Backward
		|| transmission == 0)
	{
		return true;
	}
	return BeepBeepException(to_string(transmission) + " transmission dont supporting current direction " + GetDirection());
}

bool CCar::CheckForTurnedOffEngine() const
{
	if (!m_isTurnedOn)
	{
		return true;
	}
	return BeepBeepException("Engine is turned on!");
}

bool CCar::CheckForTurnedOnEngine() const
{
	if (m_isTurnedOn)
	{
		return true;
	}
	return BeepBeepException("Engine is turned off!");
}

bool CCar::CheckForZeroSpeed() const
{
	if (m_speed == 0)
	{
		return true;
	}
	return BeepBeepException("Car is moving!");
}

bool CCar::CheckForZeroTransmission() const
{
	if (m_transmission == 0)
	{
		return true;
	}
	return BeepBeepException("Car have non zero transmission!");
}

bool CCar::CheckForNonNegativeInputSpeed(int speed) const
{
	if (speed >= 0)
	{
		return true;
	}
	return BeepBeepException("Speed value can't be less then 0!");
}

bool CCar::CheckForAlreadySettedTransmission(int tranmission) const
{
	if (tranmission != m_transmission)
	{
		return true;
	}
	return BeepBeepException(to_string(tranmission) + " transmission already setted.");
}

bool CCar::CheckForIncreasingSpeedNonOnZeroTransmission(int speed) const
{
	if (!(m_transmission == 0 && speed > m_speed))
	{
		return true;
	}
	return BeepBeepException("Cant increase speed on zero transmission!!!!!");
}

bool CCar::BeepBeepException(const string& exceptionText) const
{
	if (m_isExceptionEnabled)
	{
		throw runtime_error(exceptionText);
	}
	return false;
}