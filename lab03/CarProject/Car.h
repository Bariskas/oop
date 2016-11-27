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
	void TurnOnEngine();
	void TurnOffEngine();
	void SetTransmission(int gear);
	void SetSpeed(int speed);
	bool IsTurnedOn() const;
	int GetTransmission() const;
	int GetSpeed() const;
	Direction GetDirection() const;
	std::string GetDirectionAsString() const; // for boost tests

private:
	static std::string DirectionToString(Direction direction);

	bool CanChangeTransmission(int tranmission) const;
	bool CanChangeSpeed(int speed) const;

	bool CheckForTurnedOffEngine() const;
	bool CheckIsSpeedAllowedByTransmission(int speed, int transmission) const;
	bool CheckForTurnedOnEngine() const;
	bool CheckForSupportingCurrentDirectionByTransmission(int transmission) const;
	bool CheckForZeroSpeed() const;
	bool CheckForZeroTransmission() const;
	bool CheckForAlreadySettedTransmission(int tranmission) const;
	bool CheckForIncreasingSpeedNonOnZeroTransmission(int speed) const;
	bool CheckForNonNegativeInputSpeed(int speed) const;

private:
	typedef std::map<int, std::pair<int, int>> TranmissionSpeedMap;
	typedef std::map<Direction, std::string> DirectionNameMap;

	static const TranmissionSpeedMap m_transmissionSpeedMap;
	static const DirectionNameMap m_directionNameMap;

	bool m_isExceptionEnabled = false;
	bool m_isTurnedOn = false;
	int m_speed = 0;
	int m_transmission = 0;
};

