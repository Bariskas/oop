#include <string>
#include <iostream>
#include <map>  
#include <limits>
#include <boost/format.hpp>

using namespace std;

unsigned int StringToNumber(const string& stringToConvert, const int& sourceRadix = 10);
string NumberToString(unsigned int value, const int& radix);
int CharToNumber(const char& input);
char NumberToChar(const int& input);
bool IsMultiplicationOverflow(unsigned int firstMultiplier, unsigned int secondMultiplier);
bool IsAdditionOverflow(unsigned int firstArg, unsigned int secondArg);
bool IsValidRadix(int radix);

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Must be 3 arguments: <source notation> <destination notation> <value>" << endl;
		return 1;
	}

	int sourceRadix;
	int destinationRadix;
	unsigned int value;
	try
	{
		sourceRadix = StringToNumber(argv[1]);
		destinationRadix = StringToNumber(argv[2]);
		value = StringToNumber(argv[3], sourceRadix);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	cout << NumberToString(value, destinationRadix) << endl;
	return 0;
}

unsigned int StringToNumber(const string& stringToConvert, const int& radix)
{
	if (stringToConvert == "")
	{
		throw invalid_argument("Converting string to number failed. Converting string can't be empty");
	}
	if (radix > 36 || radix < 2)
	{
		throw invalid_argument("Radix must be between 2 and 36");
	}
	unsigned int result;
	
	size_t length = stringToConvert.length();
	result = CharToNumber(stringToConvert[0]);
	if (result >= radix)
	{
		auto exceptionString = (boost::format("Converting string contain wrong symbol %1%") % stringToConvert[0]).str();
		throw invalid_argument(exceptionString);
	}
	for (int i = 1; i < length; ++i)
	{
		if (IsMultiplicationOverflow(radix, result))
		{
			throw overflow_error("Overflow error while converting " + stringToConvert);
		}
		result *= radix;
		int nextDigit = CharToNumber(stringToConvert[i]);
		if (nextDigit >= radix)
		{
			auto exceptionString = (boost::format("Converting string contain wrong symbol %1%") % stringToConvert[i]).str();
			throw invalid_argument(exceptionString);
		}
		if (IsAdditionOverflow(result, nextDigit))
		{
			throw overflow_error("Overflow error while converting " + stringToConvert);
		}
		result += nextDigit;
	}
	return result;
}

string NumberToString(unsigned int number, const int& radix)
{
	if (radix > 36 || radix < 2)
	{
		throw invalid_argument("Radix must be between 2 and 36");
	}
	string result;
	while (number >= radix)
	{
		int modPart = number % radix;
		result += to_string(modPart);
		number = number / radix;
	}
	if (number != 0)
	{
		result += NumberToChar(number);
	}
	reverse(result.begin(), result.end());
	return result;
}

int CharToNumber(const char& input)
{
	int result;
	if (isdigit(input))
	{
		result = input - '0';
	}
	else
	{
		result = input - 'A' + 10;
	}
	return result;
}

char NumberToChar(const int& input)
{
	char result;
	if (input < 10)
	{
		result = input + '0';
	}
	else
	{
		result = input + 'A' - 10;
	}
	return result;
}

bool IsMultiplicationOverflow(unsigned int firstArg, unsigned int secondArg)
{
	bool isOverflow = false;
	if ((numeric_limits<unsigned int>::max() / firstArg) < secondArg)
	{
		isOverflow = true;
	}
	return isOverflow;
}

bool IsAdditionOverflow(unsigned int firstArg, unsigned int secondArg)
{
	bool isOverflow = false;
	if ((numeric_limits<unsigned int>::max() - firstArg) < secondArg)
	{
		isOverflow = true;
	}
	return isOverflow;
}

bool IsValidRadix(int radix)
{
	bool isValid = true;
	if (radix > 36 || radix < 2)
	{
		isValid = false;
	}
	return isValid;
}