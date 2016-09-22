#define _SCL_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <boost/chrono.hpp>
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>

#define NORMALIZE_ARRAY_INDEX_VALUE 1
#define ADDITIONAL_INDEX_FOR_ENDL 1

using namespace std;

vector<int> findReplacePositions(const string&, const string&);
const char* doReplace(const string&, const string&, const string&);

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
		output << doReplace(inputLine, searchString, replaceString) << endl;
	}

	if (!output.flush())
	{
		cout << "Failed to flush information\n";
		return 1;
	}

	return 0;
}

const char* doReplace(const string& inputLine, const string& searchString, const string& replaceString)
{
	vector<int> replacePositions;

	replacePositions = findReplacePositions(inputLine, searchString);
	if (replacePositions.empty())
	{
		return inputLine.c_str();
	}

	size_t inputLinePos = 0;
	size_t newLineLength = inputLine.length() + (replaceString.length() - searchString.length()) * replacePositions.size();
	char* newLine = new char[newLineLength + ADDITIONAL_INDEX_FOR_ENDL];
	char* newLineCopyPositionPtr = newLine;

	size_t countCharToCopy;
	for (auto nextReplacementPosition : replacePositions)
	{
		countCharToCopy = nextReplacementPosition - inputLinePos;
		inputLine.copy(newLineCopyPositionPtr, countCharToCopy, inputLinePos);
		inputLinePos += countCharToCopy;
		newLineCopyPositionPtr += countCharToCopy;

		replaceString.copy(newLineCopyPositionPtr, replaceString.length(), 0);
		inputLinePos += searchString.length();
		newLineCopyPositionPtr += replaceString.length();
	}

	if (inputLinePos != inputLine.length())
	{
		countCharToCopy = inputLine.length() - inputLinePos + NORMALIZE_ARRAY_INDEX_VALUE;
		inputLine.copy(newLineCopyPositionPtr, countCharToCopy, inputLinePos);
	}
	newLine[newLineLength] = '\0';

	return newLine;
}

vector<int> findReplacePositions(const string& source, const string& searchString)
{
	vector<int> replacePositions;
	auto searchForPattern = boost::algorithm::make_knuth_morris_pratt(searchString);

	auto searchPosition = source.cbegin();
	while ((searchPosition = searchForPattern(searchPosition, source.cend())) != source.cend())
	{
		replacePositions.push_back(searchPosition - source.cbegin());
		searchPosition += searchString.length();
	}

	return replacePositions;
}