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
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
    return 0;
}

