#define _SCL_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <boost/chrono.hpp>
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>

using namespace std;

vector<int> findReplacePositions(const string&, const string&);
const char* doReplace(const string&, const string&, const string&);

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Arguments: <sourceFile> <destinationFile> <stringToReplace> <newString>" << endl;
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

	string stringForReplacement = argv[3];
	if (stringForReplacement.empty())
	{
		cout << "string for replacement must be not empty" << endl;
	}

	string replacementString = argv[4];

	string inputLine;
	while (getline(input, inputLine))
	{
		output << doReplace(inputLine, stringForReplacement, replacementString) << endl;
	}

	if (!output.flush())
	{
		cout << "Failed to flush information\n";
		return 1;
	}

	return 0;
}

const char* doReplace(const string& inputLine, const string& stringForReplacement, const string& replacementString)
{
	vector<int> replacePositions;

	replacePositions = findReplacePositions(inputLine, stringForReplacement);
	if (replacePositions.empty())
	{
		return inputLine.c_str();
	}

	size_t inputLinePos = 0;
	size_t newLineLength = inputLine.length() + (replacementString.length() - stringForReplacement.length()) * replacePositions.size();
	char* newLine = new char[newLineLength + 1];
	char* newLineCopyPtr = newLine;

	size_t countCharToCopy;
	for (auto nextReplacementPosition : replacePositions)
	{
		countCharToCopy = nextReplacementPosition - inputLinePos;
		inputLine.copy(newLineCopyPtr, countCharToCopy, inputLinePos);
		inputLinePos += countCharToCopy;
		newLineCopyPtr += countCharToCopy;

		replacementString.copy(newLineCopyPtr, replacementString.length(), 0);
		inputLinePos += stringForReplacement.length();
		newLineCopyPtr += replacementString.length();
	}

	cout << inputLine.length() << "  " << inputLinePos << " " << newLineLength << endl;
	if (inputLinePos != inputLine.length())
	{
		countCharToCopy = inputLine.length() - inputLinePos + 1;
		inputLine.copy(newLineCopyPtr, countCharToCopy, inputLinePos);
	}
	newLine[newLineLength] = '\0';

	return newLine;
}

vector<int> findReplacePositions(const string& source, const string& stringToFind)
{
	vector<int> replacePositions;
	auto searchForPattern = boost::algorithm::make_knuth_morris_pratt(stringToFind);

	auto pos = source.cbegin();
	while ((pos = searchForPattern(pos, source.cend())) != source.cend())
	{
		replacePositions.push_back(pos - source.cbegin());
		pos += stringToFind.length();
	}

	return replacePositions;
}