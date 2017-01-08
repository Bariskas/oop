#pragma once

class CSportsman
{
public:
	CSportsman() = default;
	CSportsman(std::string const& fullName, int height, int weight);
	static bool LessHeight(CSportsman const& leftSportsman, CSportsman const& rightSportsman);
	static bool LessWeight(CSportsman const& leftSportsman, CSportsman const& rightSportsman);
	std::string fullName;
	int height;
	int weight;
};
