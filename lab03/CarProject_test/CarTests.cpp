#include "stdafx.h"
#include "../CarProject/Car.h"

struct CarTexture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(CarTestSuite, CarTexture)

	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK_EQUAL(car.IsTurnedOn(), false);
	}

	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK_EQUAL(car.IsTurnedOn(), true);
	}

	BOOST_AUTO_TEST_CASE(speed_and_transmission_0_by_default)
	{
		BOOST_CHECK_EQUAL(car.GetTransmission(), 0);
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

	BOOST_AUTO_TEST_CASE(cant_change_speed_or_transmission)
	{
		BOOST_CHECK(!car.SetSpeed(1));
		BOOST_CHECK(!car.SetTransmission(1));
	}

	struct when_turned_on_ : CarTexture
	{
		when_turned_on_()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
		
		BOOST_AUTO_TEST_CASE(cant_be_turned_on_twice_in_a_row)
		{
			BOOST_CHECK(!car.TurnOnEngine());
		}

		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			BOOST_CHECK(car.TurnOffEngine());
			BOOST_CHECK(!car.IsTurnedOn());
		}

		BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_1)
		{
			BOOST_CHECK(car.SetTransmission(1));
			BOOST_CHECK_EQUAL(car.GetTransmission(), 1);
		}

		BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_2)
		{
			BOOST_CHECK(!car.SetTransmission(2));
			BOOST_CHECK_EQUAL(car.GetTransmission(), 0);
		}

		BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_negative_1)
		{
			BOOST_CHECK(car.SetTransmission(-1));
			BOOST_CHECK_EQUAL(car.GetTransmission(), -1);
		}

		BOOST_AUTO_TEST_CASE(speed_cant_be_increased)
		{
			BOOST_CHECK(!car.SetSpeed(1));
			BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
		}

		struct when_change_tranmission_on_1_ : when_turned_on_
		{
			when_change_tranmission_on_1_()
			{
				car.SetTransmission(1);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_change_tranmission_on_1, when_change_tranmission_on_1_)

			BOOST_AUTO_TEST_CASE(speed_can_be_changed_between_0_and_30)
			{
				BOOST_CHECK(car.SetSpeed(20));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
				BOOST_CHECK(car.SetSpeed(0));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
				BOOST_CHECK(!car.SetSpeed(40));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
				BOOST_CHECK(!car.SetSpeed(-10));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
			}

			BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_negative_with_0_speed)
			{
				car.SetSpeed(10);
				BOOST_CHECK(!car.SetTransmission(-1));
				BOOST_CHECK_EQUAL(car.GetTransmission(), 1);
				car.SetSpeed(0);
				BOOST_CHECK(car.SetTransmission(-1));
				BOOST_CHECK_EQUAL(car.GetTransmission(), -1);
			}

			BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_2_speed_between_20_30)
			{
				car.SetSpeed(10);
				BOOST_CHECK(!car.SetTransmission(2));
				BOOST_CHECK_EQUAL(car.GetTransmission(), 1);
				car.SetSpeed(20);
				BOOST_CHECK(car.SetTransmission(2));
				BOOST_CHECK_EQUAL(car.GetTransmission(), 2);
			}

			BOOST_AUTO_TEST_CASE(engine_cant_be_turned_off)
			{
				BOOST_CHECK(!car.TurnOffEngine());
				BOOST_CHECK(car.IsTurnedOn());
			}

		BOOST_AUTO_TEST_SUITE_END()

		struct when_change_tranmission_on_5_ : when_turned_on_
		{
			when_change_tranmission_on_5_()
			{
				car.SetTransmission(1);
				car.SetSpeed(30);
				car.SetTransmission(2);
				car.SetSpeed(50);
				car.SetTransmission(5);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_change_tranmission_on_5, when_change_tranmission_on_5_)
			BOOST_AUTO_TEST_CASE(cant_change_transmission_on_6)
			{
				BOOST_CHECK(!car.SetTransmission(6));
				BOOST_CHECK_EQUAL(car.GetTransmission(), 5);
				car.SetSpeed(150);
				BOOST_CHECK(!car.SetTransmission(6));
				BOOST_CHECK_EQUAL(car.GetTransmission(), 5);
			}

			BOOST_AUTO_TEST_CASE(tranmission_can_be_changed_on_2_3_4)
			{
				BOOST_CHECK(car.SetTransmission(4));
				BOOST_CHECK_EQUAL(car.GetTransmission(), 4);
				car.SetTransmission(5);
				BOOST_CHECK(car.SetTransmission(3));
				BOOST_CHECK_EQUAL(car.GetTransmission(), 3);
				car.SetTransmission(5);
				BOOST_CHECK(car.SetTransmission(2));
				BOOST_CHECK_EQUAL(car.GetTransmission(), 2);
			}

			BOOST_AUTO_TEST_CASE(tranmission_can_be_changed_on_0)
			{
				BOOST_CHECK(car.SetTransmission(0));
				BOOST_CHECK_EQUAL(car.GetTransmission(), 0);
			}

			struct when_change_transmission_on_0_ : when_change_tranmission_on_5_
			{
				when_change_transmission_on_0_()
				{
					car.SetTransmission(0);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(when_change_transmission_on_0, when_change_transmission_on_0_)
				
				BOOST_AUTO_TEST_CASE(cant_increase_speed)
			{
				BOOST_CHECK(!car.SetSpeed(60));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
			}

			BOOST_AUTO_TEST_CASE(can_decrease_speed_for_0)
			{
				BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
				BOOST_CHECK(car.SetSpeed(20));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
				BOOST_CHECK(car.SetSpeed(0));
				BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
			}

			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()