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
	stringstream ss();
	ss << "Rectangle 50 50 200 50 00FF00FF 00FFFFFF\n";
		<< "Rectangle 0 0 200 50 AAFFAAFF AAFFBBFF\n"
	<<"Circle 300 300 300 FF0000FF FF0000FF";
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

