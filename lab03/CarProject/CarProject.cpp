// CarProject.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "RemoteControl.h"
#include "Car.h"

using namespace std;

int main()
{
	CCar car;
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

