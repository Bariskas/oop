// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CShapeFactory.h"
#include "CCanvas.h"
#include "ShapeUtils.h"

using namespace std;

int main()
{
	cout.setf(ios::fixed);
	cout.precision(3);

	CCanvas canvas;
	stringstream ss;
	ss << "Rectangle 20 40 120 20 00FF00FF 709E68FF" << endl
		<< "Circle 140 50 40 FFFF00FF 628E79FF" << endl
		<< "Circle 140 95 20 FFFF00FF FF0000FF" << endl
		<< "Circle 100 95 20 FFFF00FF FF0000FF" << endl
		<< "Circle 180 95 20 FFFF00FF FF0000FF" << endl
		<< "Rectangle 79 70 122 40 00FF00FF 466847FF" << endl;
	CShapeFactory factory;
	vector<ShapePtr> shapes = factory.GetShapeFromStream(ss);
	for (auto& shape : shapes)
	{
		shape->Draw(canvas);
	}
	canvas.Display();

	ShapePtr shapeWithMaxArea = GetShapeWithMaxArea(shapes);
	if (shapeWithMaxArea != nullptr)
	{
		cout << "Max area: " << shapeWithMaxArea->GetArea() << endl;
	}
	ShapePtr shapeWithMinPerimeter = GetShapeWithMinPerimeter(shapes);
	if (shapeWithMinPerimeter != nullptr)
	{
		cout << "Min perimeter: " << shapeWithMinPerimeter->GetPerimeter() << endl;
	}
	getchar();
    return 0;
}

