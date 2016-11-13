#include "stdafx.h"
#include "RemoteControl.h"
#include "Car.h"

using namespace std;

CRemoteControl::CRemoteControl(CCar& car, istream& input, ostream& output) 
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap()
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}