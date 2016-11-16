#include "stdafx.h"
#include "Car.h"

CCar::CCar() 
	: m_transmissionSpeedMap({
		{-1, {0, 20}},
		{0, {INT_MIN, INT_MAX}},
		{1, {0, 30}},
		{2, {20, 50}},
		{3, {30, 60}},
		{4, {40, 90}},
		{5, {50, 150}}
	}), 
{}

bool CCar::IsTurnedOn() const
{
	return m_isTurnedOn;
}

bool CCar::TurnOnEngine()
{
	bool isTurnedOn = false;

	if (!m_isTurnedOn)
	{
		m_isTurnedOn = true;
		isTurnedOn = true;
	}

	return isTurnedOn;
}

bool CCar::TurnOffEngine()
{
	bool isTurnedOff = false;

	if (m_isTurnedOn
		&& m_speed == 0
		&& m_transmission == 0)
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

bool CCar::CanChangeTransmission(int tranmission) const
{
	bool canChange = false;

	if (m_isTurnedOn
		&& tranmission != m_transmission
		&& IsSpeedAllowedByTransmission(m_speed, tranmission)
		&& IsTransmissionSupportCurrentDirection(tranmission))
	{
		canChange = true;
	}

	return canChange;
}

bool CCar::CanChangeSpeed(int speed) const
{
	bool canChange = false;

	if (m_isTurnedOn
		&& speed >= 0
		&& IsSpeedAllowedByTransmission(speed, m_transmission))
	{
		canChange = true;

		if (m_transmission == 0 && speed > m_speed)
		{
			canChange = false;
		}
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

bool CCar::IsSpeedAllowedByTransmission(int speed, int transmission) const
{
	bool isAllowed = false;

	auto it = m_transmissionSpeedMap.find(transmission);
	if (it != m_transmissionSpeedMap.end()
		&& speed >= it->second.first
		&& speed <= it->second.second)
	{
		isAllowed = true;
	}

	return isAllowed;
}

bool CCar::IsTransmissionSupportCurrentDirection(int transmission) const
{
	bool isSupport = false;;

	if (transmission == -1 && m_direction != Direction::Forward
		|| transmission > 0 && m_direction != Direction::Backward
		|| transmission == 0)
	{
		isSupport = true;
	}

	return isSupport;
}