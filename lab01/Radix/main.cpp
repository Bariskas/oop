#include "Radix.h"

using namespace std;

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