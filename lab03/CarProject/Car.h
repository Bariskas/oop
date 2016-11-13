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
	~CCar();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
private:
	bool m_isTurnedOn;
	Direction m_direction;
	int m_speed;
	int m_gear;
};

