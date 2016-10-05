#include <string>
#include <iostream>
#include <map>  

using namespace std;

string ChangeRadix(const string& sourceRadix, const string& destinationRadix, const string& value);
unsigned long long StringToDec(const string& stringToConvert, const string& sourceRadix);
string DecToString(unsigned long long value, const string& radix);
int CharToDec(char input);
char DecToChar(int input);

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Must be 3 arguments: <source notation> <destination notation> <value>" << endl;
		return 1;
	}

	// TODO: validate <source notation> <destination notation>

	// TODO: validate <value>

	string result = ChangeRadix(argv[1], argv[2], argv[3]);

	return 0;
}

string ChangeRadix(const string& sourceRadix, const string& destinationRadix, const string& value)
{
	unsigned long long result = StringToDec(value, sourceRadix);
	cout << "heh1: " << result << endl;
	string sres = DecToString(result, destinationRadix);
	cout << "heh2: " << sres << endl;
	return "kek";
}

unsigned long long StringToDec(const string& stringToConvert, const string& sourceRadix)
{
	int radix = stoi(sourceRadix);
	unsigned long long result;
	
	int length = stringToConvert.length();
	//cout << "o: " << lastCharIndex << endl;
	//cout << "stringToConvert: " << stringToConvert << endl;
	//cout << "stringToConvert[lastCharIndex]: " << stringToConvert[lastCharIndex] << endl;
	result = CharToDec(stringToConvert[0]);
	for (int i = 1; i < length; ++i)
	{
		result = radix * result + CharToDec(stringToConvert[i]);
		//cout << "op: " << result << endl;
	}
	return result;
}

string DecToString(unsigned long long number, const string& radixStr)
{
	int radix = stoi(radixStr);
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
		result += to_string(number);
	}
	reverse(result.begin(), result.end());
	return result;
}

int CharToDec(char input)
{
	int result;
	cout << "input " << input << endl;
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