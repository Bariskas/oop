#include "stdafx.h"
#include "CSportsman.h"
#include "FindMaxEx.h"

using namespace std;

int main()
{
	const vector<CSportsman> sportsmans = {
		CSportsman("Fat Boris", 150, 90),
		CSportsman("Tall Boris", 200, 50),
		CSportsman("Simple Boris", 175, 70),
	};
	CSportsman tallestSportsman;
	FindMax(sportsmans, tallestSportsman, CSportsman::LessHeight);
	cout << "The tallest sportsman is " << tallestSportsman.fullName 
		<< " with height: " << tallestSportsman.height << endl;
	CSportsman fattestSportsman;
	FindMax(sportsmans, fattestSportsman, CSportsman::LessWeight);
	cout << "The fattest sportsman is " << fattestSportsman.fullName
		<< " with weight: " << fattestSportsman.weight << endl;
    return 0;
}

