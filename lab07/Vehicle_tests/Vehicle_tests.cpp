#include "stdafx.h"
#include "../Vehicle/CBus.h"
#include "../Vehicle/CTaxi.h"
#include "../Vehicle/CPoliceCar.h"
#include "../Vehicle/CRacingCar.h"
#include "../Vehicle/CPoliceMan.h"
#include "../Vehicle/CRacer.h"
#include "../Vehicle/CPerson.h"
#include "../Vehicle/CTaxi.h"

struct BeginOfStoryFixture_
{
	std::shared_ptr<CPoliceMan> jhonSmith;
	CPoliceCar jhonSmithCar;
	BeginOfStoryFixture_()
		: jhonSmith(std::make_shared<CPoliceMan>(CPoliceMan("John Smith", "North West police station")))
		, jhonSmithCar(CPoliceCar(5, FORD))
	{}
};

BOOST_FIXTURE_TEST_SUITE(First_chapter_of_little_story, BeginOfStoryFixture_)
	BOOST_AUTO_TEST_CASE(There_are_brave_waiting_friend_policeman)
	{
		BOOST_CHECK(static_cast<const IPoliceMan*>(&*jhonSmith));
	}

	BOOST_AUTO_TEST_CASE(Policeman_with_name_John_Smith)
	{
		BOOST_CHECK_EQUAL(jhonSmith->GetName(), "John Smith");
	}

	BOOST_AUTO_TEST_CASE(John_Smith_from_Nort_West_police_station)
	{
		BOOST_CHECK_EQUAL(jhonSmith->GetDepartmentName(), "North West police station");
	}

	BOOST_AUTO_TEST_CASE(He_sit_in_his_empty_police_car)
	{
		BOOST_CHECK(jhonSmithCar.IsEmpty());
		BOOST_CHECK(static_cast<const IPoliceCar*>(&jhonSmithCar));
		BOOST_CHECK_NO_THROW(jhonSmithCar.AddPassenger(jhonSmith));
		BOOST_CHECK_EQUAL(jhonSmithCar.GetPassengerCount(), 1);
		BOOST_CHECK_EQUAL(jhonSmithCar.GetPassenger(0).GetName(), "John Smith");
	}

	BOOST_AUTO_TEST_CASE(Beatifull_ford_with_5_places)
	{
		BOOST_CHECK_EQUAL(jhonSmithCar.GetPlaceCount(), 5);
		BOOST_CHECK_EQUAL(jhonSmithCar.GetMakeOfTheCar(), FORD);
	}

	struct JimAppearingFixture_ : BeginOfStoryFixture_
	{
		std::shared_ptr<CPoliceMan> jimClark;
		JimAppearingFixture_()
			: BeginOfStoryFixture_()
			, jimClark(std::make_shared<CPoliceMan>(CPoliceMan("Jim Clark", "South East police station")))
		{
			jhonSmithCar.AddPassenger(jhonSmith);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(Jim_Clark_Appearing, JimAppearingFixture_)
		BOOST_AUTO_TEST_CASE(Then_appears_his_friend_the_policeman_Jim_Clark_from_South_East_police_station)
		{
			BOOST_CHECK(static_cast<const IPoliceMan*>(&*jimClark));
			BOOST_CHECK_EQUAL(jimClark->GetName(), "Jim Clark");
			BOOST_CHECK_EQUAL(jimClark->GetDepartmentName(), "South East police station");
		}

		BOOST_AUTO_TEST_CASE(he_sits_in_friends_car)
		{
			BOOST_CHECK_NO_THROW(jhonSmithCar.AddPassenger(jimClark));
			BOOST_CHECK_EQUAL(jhonSmithCar.GetPassengerCount(), 2);
			BOOST_CHECK_EQUAL(jhonSmithCar.GetPassenger(0).GetName(), "John Smith");
			BOOST_CHECK_EQUAL(jhonSmithCar.GetPassenger(1).GetName(), "Jim Clark");
		}

		struct ToughQuarrelFixture_ : JimAppearingFixture_
		{
			ToughQuarrelFixture_()
				: JimAppearingFixture_()
			{
				jhonSmithCar.AddPassenger(jimClark);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(Third_Chapter_Tough_Quarrel, ToughQuarrelFixture_)
			BOOST_AUTO_TEST_CASE(friends_quarrel_and_Jim_leaves_the_car)
			{
				BOOST_CHECK_NO_THROW(jhonSmithCar.RemovePassenger(1));
				BOOST_CHECK_EQUAL(jhonSmithCar.GetPassengerCount(), 1);
				BOOST_CHECK_EQUAL(jhonSmithCar.GetPassenger(0).GetName(), "John Smith");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

struct SecondChapterFixture_
{
	std::shared_ptr<CPoliceMan> jimClark;
	std::shared_ptr<CPerson> radjaGandy;
	std::shared_ptr<CRacer> michaelShumaher;
	CTaxi taxi;
	SecondChapterFixture_()
		: jimClark(std::make_shared<CPoliceMan>(CPoliceMan("Jim Clark", "South East police statio")))
		, radjaGandy(std::make_shared<CPerson>(CPerson("Radja Gandy")))
		, michaelShumaher(std::make_shared<CRacer>(CRacer("Michael Shumaher", 100500)))
		, taxi(CTaxi(2, TOYOTA))
	{
		taxi.AddPassenger(radjaGandy);
		taxi.AddPassenger(michaelShumaher);
	}
};

BOOST_FIXTURE_TEST_SUITE(Second_chapter_of_little_story, SecondChapterFixture_)
	BOOST_AUTO_TEST_CASE(simple_person_Radja_Gandy_exports_Michael_Shumher_in_small_taxi_toyta_with_2_places)
	{
		BOOST_CHECK(static_cast<const CTaxi*>(&taxi));
		BOOST_CHECK(static_cast<const CPerson*>(&*radjaGandy));
		BOOST_CHECK_EQUAL(taxi.GetPassengerCount(), 2);
		BOOST_CHECK(taxi.IsFull());
		BOOST_CHECK_EQUAL(taxi.GetPassenger(0).GetName(), "Radja Gandy");
		BOOST_CHECK_EQUAL(taxi.GetPassenger(1).GetName(), "Michael Shumaher");
	}

	BOOST_AUTO_TEST_CASE(Michael_Shumaher_was_the_greate_racer)
	{
		BOOST_CHECK(static_cast<const CRacer*>(&*michaelShumaher));
		BOOST_CHECK_EQUAL(michaelShumaher->GetAwardsCount(), 100500);
	}

	BOOST_AUTO_TEST_CASE(cruel_attack_by_jim_on_taxi_forces_Gandy_to_leave_from_his_taxi_and_give_place_for_jim)
	{
		BOOST_CHECK_NO_THROW(taxi.RemovePassenger(0));
		BOOST_CHECK(!taxi.IsFull());
		BOOST_CHECK_EQUAL(taxi.GetPassengerCount(), 1);
		BOOST_CHECK_EQUAL(taxi.GetPassenger(0).GetName(), "Michael Shumaher");
	}

	struct MmayhemOfTheLaw_ : SecondChapterFixture_
	{
		MmayhemOfTheLaw_()
			: SecondChapterFixture_()
		{
			taxi.RemovePassenger(0);
		}
	};
	BOOST_FIXTURE_TEST_SUITE(RadjaThrowedOut, MmayhemOfTheLaw_)
		BOOST_AUTO_TEST_CASE(Mad_Jim_rushes_in_the_taxi_to_his_idol)
		{
			BOOST_CHECK_NO_THROW(taxi.AddPassenger(jimClark));
			BOOST_CHECK(taxi.IsFull());
			BOOST_CHECK_EQUAL(taxi.GetPassengerCount(), 2);
			BOOST_CHECK_EQUAL(taxi.GetPassenger(1).GetName(), "Jim Clark");
			BOOST_CHECK_EQUAL(taxi.GetPassenger(0).GetName(), "Michael Shumaher");
		}

		BOOST_AUTO_TEST_CASE(We_see_policeman_and_racer_in_taxi_its_cute)
		{
			BOOST_CHECK(static_cast<const CTaxi*>(&taxi));
			BOOST_CHECK(static_cast<const CPoliceMan*>(&*jimClark));
			BOOST_CHECK(static_cast<const CRacer*>(&*michaelShumaher));
		}

		struct UnsuccessfulRevanche_ : MmayhemOfTheLaw_
		{
			UnsuccessfulRevanche_()
				: MmayhemOfTheLaw_()
			{
				taxi.AddPassenger(jimClark);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(UnsuccessfulRevanche, UnsuccessfulRevanche_)
			BOOST_AUTO_TEST_CASE(Poor_Radja_try_to_put_his_body_in_taxi_but_catch_exception_cause_taxi_is_full)
		{
			BOOST_CHECK_THROW(taxi.AddPassenger(radjaGandy), std::logic_error);
			BOOST_CHECK(taxi.IsFull());
		}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
