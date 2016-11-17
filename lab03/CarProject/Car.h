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
	CCar(bool enableException);
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetTransmission(int gear);
	bool SetSpeed(int speed);
	bool IsTurnedOn() const;
	int GetTransmission() const;
	int GetSpeed() const;
	std::string GetDirection() const;

private:
	bool CanChangeTransmission(int tranmission) const;
	bool CanChangeSpeed(int speed) const;
	void SetDirection(int speed);
	bool BeepBeepException(const std::string& exceptionText) const;

	bool CheckForTurnedOffEngine() const;
	bool CheckIsSpeedAllowedByTransmission(int speed, int transmission) const;
	bool CheckForTurnedOnEngine() const;
	bool CheckForSupportingCurrentDirectionByTransmission(int transmission) const;
	bool CheckForZeroSpeed() const;
	bool CheckForZeroTransmission() const;
	bool CheckForNonNegativeInputSpeed(int speed) const;
	bool CheckForAlreadySettedTransmission(int tranmission) const;
	bool CheckForIncreasingSpeedNonOnZeroTransmission(int speed) const;

private:
	typedef std::map<int, std::pair<int, int>> TranmissionSpeedMap;
	typedef std::map<Direction, std::string> DirectionNameMap;

	TranmissionSpeedMap m_transmissionSpeedMap;
	DirectionNameMap m_directionNameMap;
	bool m_isExceptionEnabled = false;
	bool m_isTurnedOn = false;
	Direction m_direction = Direction::Holding;
	int m_speed = 0;
	int m_transmission = 0;
};

