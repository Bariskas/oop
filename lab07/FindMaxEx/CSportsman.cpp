#include "stdafx.h"
#include "CSportsman.h"

CSportsman::CSportsman(std::string const& fullName, int height, int weight)
	: fullName(fullName)
	  , height(height)
	  , weight(weight)
{
}

bool CSportsman::LessHeight(CSportsman const& leftSportsman, CSportsman const& rightSportsman)
{
	return leftSportsman.height < rightSportsman.height;
}

bool CSportsman::LessWeight(CSportsman const& leftSportsman, CSportsman const& rightSportsman)
{
	return leftSportsman.weight < rightSportsman.weight;
}

std::ostream& operator<<(std::ostream& output, CSportsman const& sportsman)
{
	std::cout << "Sportsman name: " << sportsman.fullName << "; height: " << sportsman.height
		<< "; weight: " << sportsman.weight;
	return output;
}
