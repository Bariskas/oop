#include "VectorConverting.h"

using namespace std;

void ConvertVector()
{
	vector<double> workVector;
	try
	{
		workVector = GetVectorFromCin(std::cin);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

	DoubleOddDecreaseEven(workVector);

	SortAndOutputVector(workVector);
}

vector<double> GetVectorFromCin(istream& inputStream)
{
	vector<double> workVector;

	string inputString;
	getline(inputStream, inputString);
	stringstream ss(inputString);
	for (double value; ss >> value;)
	{
		workVector.push_back(value);
	}
	if (!ss.eof() && ss.fail())
	{
		throw runtime_error("invalid arguments on input");
	}

	return workVector;
}

void DoubleOddDecreaseEven(vector<double>& inputVector)
{
	double sumPositiveValues = CalculatePositiveElementSum(inputVector);

	int index = 0;
	// TODO: узнать оформление лямбда функций
	for_each(inputVector.begin(), inputVector.end(),
		[&index, &sumPositiveValues](double& value) 
	{
		value = (index % 2) == 0 ? value * 2 : value - sumPositiveValues;
		++index; 
	});
}

double CalculatePositiveElementSum(const vector<double>& inputVector)
{
	double sumPositiveValues = 0;
	for_each(inputVector.begin(), inputVector.end(),
		[&sumPositiveValues](double element)
	{
		if (element >= 0)
		{
			sumPositiveValues += element;
		}
	}
	);

	return sumPositiveValues;
}

void SortAndOutputVector(vector<double>& inputVector)
{
	sort(inputVector.begin(), inputVector.end());

	cout.setf(ios::fixed);
	cout.precision(3);
	copy(inputVector.begin(), inputVector.end(), ostream_iterator<double>(std::cout, " "));
}