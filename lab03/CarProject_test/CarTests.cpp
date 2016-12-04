#include "stdafx.h"
#include "../CarProject/Car.h"

using namespace std;
using namespace std::placeholders;

const string BACKWARD_DIRECTION = "Backward";
const string FORWARD_DIRECTION = "Forward";
const string HOLDING_DIRECTION = "Holding";

struct CarTexture
{
	CCar car;

	void ExpectOperationFailure(const function<void(CCar & obj)> & op) const
	{
		auto clone(car);
		BOOST_CHECK_THROW(op(clone), runtime_error);
		BOOST_CHECK_EQUAL(clone.GetSpeed(), car.GetSpeed());
		BOOST_CHECK_EQUAL(clone.GetTransmission(), car.GetTransmission());
		BOOST_CHECK(clone.GetDirection() == car.GetDirection());
	}

	void ExpectOperationSuccess(const function<void(CCar & obj)> & op, 
		bool expectedEngineState, int expectedSpeed, int expectedTransmission, 
		Direction expectedDirection)
	{
		BOOST_CHECK_NO_THROW(op(car));
		BOOST_CHECK_EQUAL(car.IsTurnedOn(), expectedEngineState);
		BOOST_CHECK_EQUAL(car.GetSpeed(), expectedSpeed);
		BOOST_CHECK_EQUAL(car.GetTransmission(), expectedTransmission);
		BOOST_CHECK(car.GetDirection() == expectedDirection);
	}

	void ExpectCantSetTransmission(int tranmission) const
	{
		ExpectOperationFailure(bind(&CCar::SetTransmission, _1, tranmission));
	}

	void ExpectCanSetTransmission(int tranmission)
	{
		ExpectOperationSuccess(bind(&CCar::SetTransmission, _1, tranmission),
			car.IsTurnedOn(), car.GetSpeed(), tranmission, car.GetDirection());
	}

	void ExpectCantSetSpeed(int speed) const
	{
		ExpectOperationFailure(bind(&CCar::SetSpeed, _1, speed));
	}

	void ExpectCanSetSpeed(int speed, Direction direction)
	{
		ExpectOperationSuccess(bind(&CCar::SetSpeed, _1, speed),
			car.IsTurnedOn(), speed, car.GetTransmission(), direction);
	}

	void ExpectCantTurnOff() const
	{
		ExpectOperationFailure(bind(&CCar::TurnOffEngine, _1));
	}

	void ExpectCanTurnOff()
	{
		ExpectOperationSuccess(bind(&CCar::TurnOffEngine, _1),
			false, car.GetSpeed(), car.GetTransmission(), car.GetDirection());
	}

	void ExpectCantTurnOn() const
	{
		ExpectOperationFailure(bind(&CCar::TurnOnEngine, _1));
	}

	void ExpectCanTurnOn()
	{
		ExpectOperationSuccess(bind(&CCar::TurnOnEngine, _1),
			true, car.GetSpeed(), car.GetTransmission(), car.GetDirection());
	}
};

BOOST_FIXTURE_TEST_SUITE(Car, CarTexture)
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK_EQUAL(car.IsTurnedOn(), false);
	}

	BOOST_AUTO_TEST_CASE(speed_and_transmission_0_by_default)
	{
		BOOST_CHECK_EQUAL(car.GetTransmission(), 0);
		BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		ExpectCanTurnOn();
	}

	BOOST_AUTO_TEST_CASE(cant_change_speed_or_transmission_by_default)
	{
		ExpectCantSetTransmission(1);
		ExpectCantSetSpeed(1);
		ExpectCantSetTransmission(-1);
		ExpectCantSetSpeed(-1);
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
			BOOST_CHECK_THROW(car.TurnOnEngine(), runtime_error);
			BOOST_CHECK_EQUAL(car.IsTurnedOn(), true);
		}

		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			BOOST_CHECK_NO_THROW(car.TurnOffEngine());
			BOOST_CHECK_EQUAL(car.IsTurnedOn(), false);
		}

		BOOST_AUTO_TEST_CASE(speed_cant_be_changed)
		{
			ExpectCantSetSpeed(1);
			ExpectCantSetSpeed(-1);
		}

		BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_1)
		{
			ExpectCanSetTransmission(1);
		}

		BOOST_AUTO_TEST_CASE(transmission_cant_be_changed_on_2)
		{
			ExpectCantSetTransmission(2);
		}

		BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_negative_1)
		{
			ExpectCanSetTransmission(-1);
		}

		struct when_change_tranmission_on_negative_ : when_turned_on_
		{
			when_change_tranmission_on_negative_()
			{
				car.SetTransmission(-1);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_change_tranmission_on_negative, when_change_tranmission_on_negative_)
			BOOST_AUTO_TEST_CASE(speed_can_be_increased)
			{
				ExpectCanSetSpeed(10, Direction::Backward);
			}

			BOOST_AUTO_TEST_CASE(speed_cant_be_bigger_20)
			{
				ExpectCanSetSpeed(20, Direction::Backward);
				ExpectCantSetSpeed(21);
			}

			BOOST_AUTO_TEST_CASE(car_cant_be_turned_off)
			{
				ExpectCantTurnOff();
			}

			struct when_set_speed_10_on_negative_transmission_ : when_change_tranmission_on_negative_
			{
				when_set_speed_10_on_negative_transmission_()
				{
					car.SetSpeed(10);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(when_set_speed_10_on_negative_transmission, when_set_speed_10_on_negative_transmission_)
				BOOST_AUTO_TEST_CASE(transmission_cant_be_changed_on_1)
				{
					ExpectCantSetTransmission(1);
				}

				BOOST_AUTO_TEST_CASE(direction_must_be_backward)
				{
					BOOST_CHECK_EQUAL(static_cast<int>(car.GetDirection()), static_cast<int>(Direction::Backward));
				}

				BOOST_AUTO_TEST_CASE(car_cant_be_turned_off)
				{
					ExpectCantTurnOff();
				}

				BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_0)
				{
					ExpectCanSetTransmission(0);
				}

				struct when_set_tranmission_to_0_ : when_set_speed_10_on_negative_transmission_
				{
					when_set_tranmission_to_0_()
					{
						car.SetTransmission(0);
					}
				};

				BOOST_FIXTURE_TEST_SUITE(when_set_tranmission_to_0, when_set_tranmission_to_0_)
					BOOST_AUTO_TEST_CASE(speed_cant_be_increased)
					{
						ExpectCantSetSpeed(15);
					}

					BOOST_AUTO_TEST_CASE(speed_can_be_decreased)
					{
						ExpectCanSetSpeed(5, Direction::Backward);
					}

					BOOST_AUTO_TEST_CASE(car_cant_be_turned_off)
					{
						ExpectCantTurnOff();
					}

					struct when_set_speed_to_0_ : when_set_tranmission_to_0_
					{
						when_set_speed_to_0_()
						{
							car.SetSpeed(0);
						}
					};

					BOOST_FIXTURE_TEST_SUITE(when_set_speed_to_0, when_set_speed_to_0_)
						BOOST_AUTO_TEST_CASE(car_can_be_turned_off)
						{
							ExpectCanTurnOff();
						}

						BOOST_AUTO_TEST_CASE(direction_must_be_holding)
						{
							BOOST_CHECK_EQUAL(static_cast<int>(car.GetDirection()), static_cast<int>(Direction::Holding));
						}
					BOOST_AUTO_TEST_SUITE_END()
				BOOST_AUTO_TEST_SUITE_END()
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()

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
				ExpectCanSetSpeed(30, Direction::Forward);
				ExpectCanSetSpeed(0, Direction::Holding);
				ExpectCantSetSpeed(40);
				ExpectCantSetSpeed(-10);
			}

			BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_negative)
			{
				ExpectCanSetTransmission(-1);
			}

			BOOST_AUTO_TEST_CASE(car_cant_be_turned_off)
			{
				ExpectCantTurnOff();
			}

			struct when_change_speed_to_10_on_1_transmission_ : when_change_tranmission_on_1_
			{
				when_change_speed_to_10_on_1_transmission_()
				{
					car.SetSpeed(10);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(when_change_speed_to_10_on_1_transmission, when_change_speed_to_10_on_1_transmission_)
				BOOST_AUTO_TEST_CASE(cant_set_negative_transmission)
				{
					ExpectCantSetTransmission(-1);
				}

				BOOST_AUTO_TEST_CASE(transmission_cant_be_changed_on_2)
				{
					ExpectCantSetTransmission(2);
				}

				BOOST_AUTO_TEST_CASE(direction_must_be_forward)
				{
					BOOST_CHECK_EQUAL(static_cast<int>(car.GetDirection()), static_cast<int>(Direction::Forward));
				}

				BOOST_AUTO_TEST_CASE(car_cant_be_turned_off)
				{
					ExpectCantTurnOff();
				}

				BOOST_AUTO_TEST_CASE(transmission_can_be_changed_on_0)
				{
					ExpectCanSetTransmission(0);
				}

				struct when_set_tranmission_to_0_ : when_change_speed_to_10_on_1_transmission_
				{
					when_set_tranmission_to_0_()
					{
						car.SetTransmission(0);
					}
				};

				BOOST_FIXTURE_TEST_SUITE(when_set_tranmission_to_0, when_set_tranmission_to_0_)
					BOOST_AUTO_TEST_CASE(speed_cant_be_increased)
					{
						ExpectCantSetSpeed(15);
					}

					BOOST_AUTO_TEST_CASE(speed_can_be_decreased)
					{
						ExpectCanSetSpeed(5, Direction::Forward);
					}

					BOOST_AUTO_TEST_CASE(car_cant_be_turned_off)
					{
						ExpectCantTurnOff();
					}

					struct when_set_speed_to_0_ : when_set_tranmission_to_0_
					{
						when_set_speed_to_0_()
						{
							car.SetSpeed(0);
						}
					};

					BOOST_FIXTURE_TEST_SUITE(when_set_speed_to_0, when_set_speed_to_0_)
						BOOST_AUTO_TEST_CASE(car_can_be_turned_off)
						{
							ExpectCanTurnOff();
						}

						BOOST_AUTO_TEST_CASE(direction_must_be_holding)
						{
							BOOST_CHECK_EQUAL(static_cast<int>(car.GetDirection()), static_cast<int>(Direction::Holding));
						}
					BOOST_AUTO_TEST_SUITE_END()
				BOOST_AUTO_TEST_SUITE_END()
			BOOST_AUTO_TEST_SUITE_END()

			struct when_change_speed_to_30_on_1_transmission_ : when_change_tranmission_on_1_
			{
				when_change_speed_to_30_on_1_transmission_()
				{
					car.SetSpeed(30);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(when_change_speed_to_30_on_1_transmission, when_change_speed_to_30_on_1_transmission_)
				BOOST_AUTO_TEST_CASE(can_set_2_tranmission)
				{
					ExpectCanSetTransmission(2);
				}

				BOOST_AUTO_TEST_CASE(can_set_3_tranmission)
				{
					ExpectCanSetTransmission(3);
				}
			BOOST_AUTO_TEST_SUITE_END()
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
			BOOST_AUTO_TEST_CASE(tranmission_can_be_changed_on_2)
			{
				ExpectCanSetTransmission(2);
			}

			BOOST_AUTO_TEST_CASE(tranmission_can_be_changed_on_3)
			{
				ExpectCanSetTransmission(3);
			}

			BOOST_AUTO_TEST_CASE(tranmission_can_be_changed_on_4)
			{
				ExpectCanSetTransmission(4);
			}

			BOOST_AUTO_TEST_CASE(tranmission_can_be_changed_on_0)
			{
				ExpectCanSetTransmission(0);
			}

			BOOST_AUTO_TEST_CASE(speed_can_be_between_50_and_150)
			{
				ExpectCantSetSpeed(40);
				ExpectCantSetSpeed(151);
				ExpectCanSetSpeed(150, Direction::Forward);
				ExpectCanSetSpeed(50, Direction::Forward);
			}

			struct when_change_speed_to_150_ : when_change_tranmission_on_5_
			{
				when_change_speed_to_150_()
				{
					car.SetSpeed(150);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(when_change_speed_to_150, when_change_speed_to_150_)
				BOOST_AUTO_TEST_CASE(cant_change_transmission_on_6)
				{
					ExpectCantSetTransmission(6);
				}

				BOOST_AUTO_TEST_CASE(cant_set_3_tranmission)
				{
					ExpectCantSetTransmission(3);
				}

				BOOST_AUTO_TEST_CASE(cant_set_4_tranmission)
				{
					ExpectCantSetTransmission(4);
				}
			BOOST_AUTO_TEST_SUITE_END()

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
					ExpectCantSetSpeed(70);
				}

				BOOST_AUTO_TEST_CASE(can_decrease_speed_for_0)
				{
					ExpectCanSetSpeed(0, Direction::Holding);
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()