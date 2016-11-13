#pragma once

class CCar;

class CRemoteControl
{
public:
	CRemoteControl(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();
private:
	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;
	
	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};

