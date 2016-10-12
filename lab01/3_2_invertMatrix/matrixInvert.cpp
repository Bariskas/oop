#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Must be 1 argument: <matrix file1>" << endl;
		return 1;
	}

	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "failed to open " << argv[1] << " for reading\n";
		return 1;
	}
	return 0;
}