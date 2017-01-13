#pragma once

class Filler
{
	typedef std::vector<std::vector<char>> vector2d;
public:
	Filler(int mapSize = 100);
	void Fill(std::istream& is, std::ostream& os) const;
private:
	void FillNodeMap(vector2d& nodeMap, std::istream& is) const;
	void FindFountains(vector2d const& nodeMap,
		std::vector<std::pair<int, int>>& fountainNodes) const;
	void TurnOnFountain(std::pair<int, int> const& fountainCoordinate, vector2d& nodeMap) const;
private:
	int m_size;
};

