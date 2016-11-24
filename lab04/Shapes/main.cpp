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

	CRectangle rectangle({ 200, 200 }, 100, 100, "ff0000", "00ff00");
	cout << rectangle.ToString() << endl;
	string expectedString = "Shape - rectangle\narea = 1240.28\nperimeter = 142.2\nleftTopPoint.x = 10.3\nleftTopPoint.y = 20.15\nwidth = 30.7\nheight = 40.4\noutlineColor = 00ff00\nfillColor = ff0000\n";
	if (rectangle.ToString() == expectedString)
	{
		cout << "NIHUIASEBE" << endl;
	}
	else
	{
		cout << expectedString << endl;
	}
	CCanvas canvas;
	//rectangle.Draw(canvas);
	stringstream ss("Rectangle 50 50 200 50 00FF00FF 00FFFFFF\nRectangle 0 0 200 50 AAFFAAFF AAFFBBFF");
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

