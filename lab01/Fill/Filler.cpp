#include "stdafx.h"
#include "Filler.h"
#include <locale>
#include <queue>

using namespace std;

Filler::Filler(int mapSize)
	: m_size(mapSize)
{}

void Filler::Fill(std::istream& is, std::ostream& os) const
{
	vector2d nodeMap(m_size, vector<char>(m_size, ' '));
	FillNodeMap(nodeMap, is);

	vector<pair<int, int>> fountainNodes{};
	fountainNodes.reserve(10);
	FindFountains(nodeMap, fountainNodes);
	for (auto fountainCoordinate : fountainNodes)
	{
		TurnOnFountain(fountainCoordinate, nodeMap);
	}
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			os << nodeMap[i][j];
		}
		os << endl;
	}
}

void Filler::FillNodeMap(vector2d& nodeMap, std::istream& is) const
{
	string bufferStr;
	for (int i = 0; i < m_size && !is.eof(); ++i)
	{
		getline(is, bufferStr);
		for (int j = 0; j < m_size && j < bufferStr.length(); ++j)
		{
			nodeMap[i][j] = bufferStr[j];
		}
	}
}

void Filler::FindFountains(vector2d const& nodeMap, std::vector<pair<int, int>>& fountainNodes) const
{
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			if (nodeMap[i][j] == 'O')
			{
				fountainNodes.push_back(std::pair<int, int>(i, j));
			}
		}
	}
}

void Filler::TurnOnFountain(std::pair<int, int> const& fountainCoordinate, vector2d& nodeMap) const
{
	queue<pair<int, int>> nodes;
	nodes.push(fountainCoordinate);
	while (!nodes.empty())
	{
		auto node = nodes.front();
		nodes.pop();
		char nodeValue = nodeMap[node.first][node.second];
		if (nodeValue == 'O' || nodeValue == ' ')
		{
			auto y = node.first;
			auto leftX = node.second;
			auto rightX = node.second;
			while (leftX > 0 && 
				nodeMap[y][leftX - 1] != '#')
			{
				--leftX;
			}
			while (rightX < m_size - 1 && 
				nodeMap[y][rightX + 1] != '#')
			{
				++rightX;
			}
			for (int i = leftX; i <= rightX; ++i)
			{
				nodeMap[y][i] = (nodeMap[y][i] == 'O')
					? 'O' : '+';
				if (y != m_size - 1 && nodeMap[y + 1][i] == ' ')
				{
					nodes.push(pair<int, int>(y + 1, i));
				}
				if (y != 0 && nodeMap[y - 1][i] == ' ')
				{
					nodes.push(pair<int, int>(y - 1, i));
				}
			}
		}
	}
}
