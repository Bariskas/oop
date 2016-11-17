#pragma once


class CCar;
enum class Direction;

class CRemoteControl
{
public:
	CRemoteControl(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool Info(std::istream& args);
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetSpeed(std::istream& args);
	bool SetGear(std::istream& args);
	std::string DirectionToString(Direction direction);
private:
	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;
	typedef std::map<Direction, std::string> DirectionNameMap;

	static const DirectionNameMap m_directionNameMap;
	ActionMap m_actionMap;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
};

