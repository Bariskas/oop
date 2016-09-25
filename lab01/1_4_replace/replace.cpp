#define _SCL_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>

using namespace std;

vector<size_t> FindSubstringPositions(const string& sourceString, const string& substring);
string Replace(const string& inputLine, const string& searchString, const string& replaceString);

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Must be 4 arguments: <sourceFile> <destinationFile> <stringToReplace> <newString>" << endl;
		return 1;
	}

	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	ofstream output(argv[2]);
	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	string searchString = argv[3];
	if (searchString.empty())
	{
		cout << "string for replacement must be not empty" << endl;
		return 1;
	}

	string replaceString = argv[4];

	string inputLine;
	while (getline(input, inputLine))
	{
		output << Replace(inputLine, searchString, replaceString) << endl;
	}

	if (!output.flush())
	{
		cout << "Failed to flush information\n";
		return 1;
	}

	return 0;
}

string Replace(const string& inputLine, const string& searchString, const string& replaceString)
{
	vector<size_t> replacePositions = FindSubstringPositions(inputLine, searchString);
	if (replacePositions.empty())
	{
		return inputLine;
	}

	size_t newLineLength = inputLine.length() + (replaceString.length() - searchString.length()) * replacePositions.size();
	string newLine;
	newLine.reserve(newLineLength);

	auto inputLineIt = inputLine.begin();
	for (auto replacePositionIt : replacePositions)
	{
		newLine.append(inputLineIt, inputLine.begin() + replacePositionIt);
		newLine.append(replaceString);
		inputLineIt = inputLine.begin() + replacePositionIt + searchString.length();
	}

	if (inputLineIt != inputLine.end())
	{
		newLine.append(inputLineIt, inputLine.end());
	}

	return newLine;
}

vector<size_t> FindSubstringPositions(const string& source, const string& substring)
{
	vector<size_t> replacePositions;
	auto searchForPattern = boost::algorithm::make_knuth_morris_pratt(substring);

	auto searchPosition = source.cbegin();
	while ((searchPosition = searchForPattern(searchPosition, source.cend())) != source.cend())
	{
		replacePositions.push_back(searchPosition - source.cbegin());
		searchPosition += substring.length();
	}

	return replacePositions;
}