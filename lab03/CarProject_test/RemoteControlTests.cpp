#include "stdafx.h"
#include "../CarProject/Car.h"
#include "../CarProject/RemoteControl.h"

using namespace std;

struct RemoteControlDependencies
{
	CCar car = CCar();
	stringstream input;
	stringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;

	RemoteControlFixture()
		: remoteControl(car, input, output)
	{

	}

	void VerifyCommandHandling(const string& command, bool isTurnedOn, int expectedSpeed, int expectedGear, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(car.IsTurnedOn(), isTurnedOn);
		BOOST_CHECK_EQUAL(car.GetSpeed(), expectedSpeed);
		BOOST_CHECK_EQUAL(car.GetTransmission(), expectedGear);
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)
	BOOST_AUTO_TEST_CASE(cant_handle_unknow_command)
	{
		output = stringstream();
		input = stringstream("asgASGasgasg");
		BOOST_CHECK(!remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(output.str(), "");
	}

	BOOST_AUTO_TEST_CASE(can_handle_Info_command)
	{
		VerifyCommandHandling("Info", false, 0, 0, "Car is turned off.\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_EngineOn_command)
	{
		VerifyCommandHandling("EngineOn", true, 0, 0, "Car engine is turned on.\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_SetSpeed_command)
	{
		VerifyCommandHandling("SetSpeed 3", false, 0, 0, "Engine is turned off.\n");
		car.TurnOnEngine();
		VerifyCommandHandling("SetSpeed 3", true, 0, 0, "Cant increase speed on zero transmission.\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_EngineOff_command)
	{
		car.TurnOnEngine();
		VerifyCommandHandling("EngineOff", false, 0, 0, "Car engine is turned off.\n");
	}
BOOST_AUTO_TEST_SUITE_END()