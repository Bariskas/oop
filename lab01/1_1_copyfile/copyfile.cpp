#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

int main(int argc, char * argv[])
{
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

	char ch;
	while (input.get(ch))
	{
		output.put(ch);
	}

	if (!output.flush())
	{
		cout << "Failed to flush information\n";
		return 1;
	}

	return 0;
}