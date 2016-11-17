// CarProject.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "RemoteControl.h"
#include "Car.h"

using namespace std;

int main()
{
	bool enableException = true;
	CCar car(enableException);
	CRemoteControl remoteControl(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		try
		{
			if (!remoteControl.HandleCommand())
			{
				cout << "Unknown command!" << endl;
			}
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}
    return 0;
}

