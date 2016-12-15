// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CShapeFactory.h"
#include "CCanvas.h"

using namespace std;

int main()
{
	cout.setf(ios::fixed);
	cout.precision(3);

//	CRectangle rectangle({ 200, 200 }, 100, 100, "ff0000", "00ff00");
//	cout << rectangle.ToString() << endl;
//	string expectedString = "Shape - rectangle\narea = 10000\nperimeter = 400\nleftTopPoint.x = 200\nleftTopPoint.y = 200\nwidth = 100\nheight = 100\noutlineColor = ff0000\nfillColor = 00ff00\n";
//	if (rectangle.ToString() == expectedString)
//	{
//		cout << "NIHUIASEBE" << endl;
//	}
//	else
//	{
//  	cout << expectedString << endl;
//	}
	CCanvas canvas;
	//rectangle.Draw(canvas);
	stringstream ss;
	// ITA TANK, DA
	ss << "Rectangle 20 40 120 20 00FF00FF 00FFFFFF\n"
		<< "Circle 140 50 40 FFFF00FF FF0000FF" << endl
		<< "Circle 140 95 20 FFFF00FF FF0000FF" << endl
		<< "Circle 100 95 20 FFFF00FF FF0000FF" << endl
		<< "Circle 180 95 20 FFFF00FF FF0000FF" << endl
		<< "Rectangle 79 70 122 40 00FF00FF 00FFFFFF\n";
	CShapeFactory factory;
	vector<ShapePtr> shapes = factory.GetShapeFromStream(ss);
	for (auto& shape : shapes)
	{
		shape->Draw(canvas);
	}
	canvas.Display();
	getchar();
    return 0;
}

