#include "VectorConverting.h"

using namespace std;

void ConvertVector(vector<double>& inputVector)
{
	double sumPositiveValues = CalculatePositiveElementSum(inputVector);

	bool isEven = false;
	transform(inputVector.begin(), inputVector.end(), inputVector.begin(),
			[&](double value) {
			isEven = !isEven;
			return isEven ? value * 2 : value - sumPositiveValues;
		}
	);
}

double CalculatePositiveElementSum(const vector<double>& inputVector)
{
	double sumPositiveValues = 0;
	for_each(inputVector.begin(), inputVector.end(),
		[&sumPositiveValues](double element) {
			if (element >= 0)
			{
				sumPositiveValues += element;
			}
		}
	);

	return sumPositiveValues;
}