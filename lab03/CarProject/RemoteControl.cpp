#include "stdafx.h"
#include "RemoteControl.h"
#include "Car.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CCar& car, istream& input, ostream& output) 
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "Info", bind(&CRemoteControl::Info, this, _1) },
		{ "EngineOn", bind(&CRemoteControl::EngineOn, this, _1) },
		{ "EngineOff", bind(&CRemoteControl::EngineOff, this, _1) },
		{ "SetSpeed", bind(&CRemoteControl::SetSpeed, this, _1) },
		{ "SetGear", bind(&CRemoteControl::SetGear, this, _1) }
	})
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
		try
		{
			return it->second(strm);
		}
		catch(const exception& e)
		{
			m_output << e.what() << endl;
			return true;
		}
	}

	return false;
}

bool CRemoteControl::Info(istream& /*args*/)
{
	string info;
	if (m_car.IsTurnedOn())
	{
		info.append("Car is turned on and have \"" + m_car.GetDirection() + "\" direction with " + to_string(m_car.GetTransmission()) + " transmission and speed = " + to_string(m_car.GetSpeed()));
	}
	else
	{
		info.append("Car is turned off");
	}

	m_output << info << endl;

	return true;
}

bool CRemoteControl::EngineOn(istream& /*args*/)
{
	m_car.TurnOnEngine();
	m_output << "Car engine is turned on" << endl;
	return true;
}

bool CRemoteControl::EngineOff(istream& /*args*/)
{
	m_car.TurnOffEngine();
	m_output << "Car engine is turned off" << endl;
	return true;
}

bool CRemoteControl::SetSpeed(istream& args)
{
	int speed;
	args >> speed;
	m_car.SetSpeed(speed);
	m_output << "Car have speed " + to_string(m_car.GetSpeed()) << endl;
	return true;
}

bool CRemoteControl::SetGear(istream& args)
{
	int gear;
	args >> gear;
	m_car.SetTransmission(gear);
	m_output << "Car have transmission " + to_string(m_car.GetTransmission()) << endl;
	return true;
}