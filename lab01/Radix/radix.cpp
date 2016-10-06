#include <string>
#include <iostream>
#include <map>  
#include <limits>

using namespace std;

string ChangeRadix(const unsigned long long& sourceRadix, const unsigned long long& destinationRadix, const unsigned long long& value);
unsigned long long StringToDec(const string& stringToConvert, const int& sourceRadix = 10);
string DecToString(unsigned long long value, const int& radix);
int CharToDec(char input);
char DecToChar(int input);
bool IsMultiplicationOverflow(unsigned long long firstMultiplier, unsigned long long secondMultiplier);
bool IsAdditionOverflow(unsigned long long firstArg, unsigned long long secondArg);

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Must be 3 arguments: <source notation> <destination notation> <value>" << endl;
		return 1;
	}

	// TODO: validate <source notation> <destination notation>
	int sourceRadix;
	try
	{
		sourceRadix = StringToDec(argv[1]);
	}
	catch (exception(e))
	{
		cout << e.what() << endl;
		return 1;
	}
	
	int destinationRadix;
	try
	{
		destinationRadix = StringToDec(argv[2]);
	}
	catch (exception(e))
	{
		cout << e.what() << endl;
		return 1;
	}

	unsigned long long value;
	try
	{
		value = StringToDec(argv[3], sourceRadix);
	}
	catch (exception(e))
	{
		cout << e.what() << endl;
		return 1;
	}
	// TODO: validate <value>

	string result = ChangeRadix(sourceRadix, destinationRadix, value);
	cout << result << endl;
	getchar();
	return 0;
}

string ChangeRadix(const unsigned long long& sourceRadix, const unsigned long long& destinationRadix, const unsigned long long& value)
{
	return DecToString(value, destinationRadix);
}

unsigned long long StringToDec(const string& stringToConvert, const int& radix)
{
	unsigned long long result;
	
	int length = stringToConvert.length();
	result = CharToDec(stringToConvert[0]);
	for (int i = 1; i < length; ++i)
	{
		if (IsMultiplicationOverflow(radix, result))
		{
			throw overflow_error("Overflow error while converting " + stringToConvert);
		}
		result *= radix;
		int nextDigit = CharToDec(stringToConvert[i]);
		if (IsAdditionOverflow(result, nextDigit))
		{
			throw overflow_error("Overflow error while converting " + stringToConvert);
		}
		result += nextDigit;
	}
	return result;
}

string DecToString(unsigned long long number, const int& radix)
{
	string result;
	//TODO: reserve
	while (number >= radix)
	{
		int modPart = number % radix;
		result += to_string(modPart);
		number = number / radix;
	}
	if (number != 0)
	{
		result += DecToChar(number);
	}
	reverse(result.begin(), result.end());
	return result;
}

int CharToDec(char input)
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

char DecToChar(int input)
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

bool IsMultiplicationOverflow(unsigned long long firstArg, unsigned long long secondArg)
{
	bool isOverflow = false;
	if ((numeric_limits<unsigned long long>::max() / firstArg) < secondArg)
	{
		isOverflow = true;
	}
	return isOverflow;
}

bool IsAdditionOverflow(unsigned long long firstArg, unsigned long long secondArg)
{
	bool isOverflow = false;
	if ((numeric_limits<unsigned long long>::max() - firstArg) < secondArg)
	{
		isOverflow = true;
	}
	return isOverflow;
}