#include <string>
#include <iostream>
#include <limits>
#include <boost/format.hpp>

using namespace std;

string ChangeRadix(const string& sourceRadix, const string& destRadix, const string& value);
unsigned StringToNumber(const string& stringToConvert, int sourceRadix = 10);
string NumberToString(unsigned value, unsigned radix);
int CharToNumber(char input);
char NumberToChar(int input);
bool IsMultiplicationOverflow(unsigned firstMultiplier, unsigned secondMultiplier);
bool IsAdditionOverflow(unsigned firstArg, unsigned secondArg);
bool IsValidRadix(int radix);
unsigned MultiplicationWithOverflowCheck(unsigned arg1, unsigned arg2);
unsigned AdditionWithOverflowCheck(unsigned arg1, unsigned arg2);

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Must be 3 arguments: <source notation> <destination notation> <value>" << endl;
		return 1;
	}

	string result;
	try
	{
		result = ChangeRadix(argv[1], argv[2], argv[3]);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	cout << result << endl;
	return 0;
}

string ChangeRadix(const string& sourceRadixStr, const string& destRadixStr, const string& valueStr)
{
	int sourceRadix;
	int destinationRadix;
	unsigned value;
	sourceRadix = StringToNumber(sourceRadixStr);
	destinationRadix = StringToNumber(destRadixStr);

	string result;
	if (valueStr[0] == '+' || valueStr[0] == '-')
	{
		value = StringToNumber(valueStr.c_str() + 1, sourceRadix);
		result = valueStr[0] + NumberToString(value, destinationRadix);
	}
	else
	{
		value = StringToNumber(valueStr, sourceRadix);
		result = NumberToString(value, destinationRadix);
	}

	return result;
}

unsigned StringToNumber(const string& stringToConvert, int radix)
{
	if (stringToConvert == "")
	{
		throw invalid_argument("Converting string to number failed. Converting string can't be empty");
	}
	if (radix > 36 || radix < 2)
	{
		throw invalid_argument("Radix must be between 2 and 36");
	}
	unsigned result;
	
	result = 0;
	for (size_t i = 0; i < stringToConvert.length(); ++i)
	{
		result = MultiplicationWithOverflowCheck(radix, result);
		int nextDigit = CharToNumber(stringToConvert[i]);
		if (nextDigit >= radix)
		{
			auto exceptionString = (boost::format("Converting string contain wrong symbol %1%") % stringToConvert[i]).str();
			throw invalid_argument(exceptionString);
		}
		result = AdditionWithOverflowCheck(result, nextDigit);
	}
	return result;
}

unsigned MultiplicationWithOverflowCheck(unsigned arg1, unsigned arg2)
{
	if (IsMultiplicationOverflow(arg1, arg2))
	{
		throw overflow_error("Overflow error");
	}
	return arg1 * arg2;
}

unsigned AdditionWithOverflowCheck(unsigned arg1, unsigned arg2)
{
	if (IsAdditionOverflow(arg1, arg2))
	{
		throw overflow_error("Overflow error");
	}
	return arg1 + arg2;
}

string NumberToString(unsigned number, unsigned radix)
{
	if (radix > 36 || radix < 2)
	{
		throw invalid_argument("Radix must be between 2 and 36");
	}
	string result;
	while (number >= radix)
	{
		int modPart = number % radix;
		result += NumberToChar(modPart);
		number = number / radix;
	}
	if (number != 0)
	{
		result += NumberToChar(number);
	}
	reverse(result.begin(), result.end());
	return result;
}

int CharToNumber(char input)
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

char NumberToChar(int input)
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

bool IsMultiplicationOverflow(unsigned firstArg, unsigned secondArg)
{
	bool isOverflow = false;
	if ((numeric_limits<unsigned>::max() / firstArg) < secondArg)
	{
		isOverflow = true;
	}
	return isOverflow;
}

bool IsAdditionOverflow(unsigned firstArg, unsigned secondArg)
{
	bool isOverflow = false;
	if ((numeric_limits<unsigned>::max() - firstArg) < secondArg)
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