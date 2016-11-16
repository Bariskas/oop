#pragma once

enum class Direction
{
	Backward,
	Holding,
	Forward
};

class CCar
{
public:
	CCar();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetTransmission(int gear);
	bool SetSpeed(int speed);
	bool IsTurnedOn() const;
	int GetTransmission() const;
	int GetSpeed() const;

private:
	bool CanChangeTransmission(int tranmission) const;
	bool CanChangeSpeed(int speed) const;
	bool IsSpeedAllowedByTransmission(int speed, int transmission) const;
	bool IsTransmissionSupportCurrentDirection(int transmission) const;
	void SetDirection(int speed);

private:
	typedef std::map<int, std::pair<int, int>> TranmissionSpeedMap;
	typedef std::map<Direction, std::string> DirectionNameMap;


	TranmissionSpeedMap m_transmissionSpeedMap;
	bool m_isTurnedOn = false;
	Direction m_direction = Direction::Holding;
	int m_speed = 0;
	int m_transmission = 0;
};

