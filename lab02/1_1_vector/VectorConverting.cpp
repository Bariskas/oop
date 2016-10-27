#include "VectorConverting.h"

using namespace std;

void ConvertVector(vector<double>& inputVector)
{
	DoubleOddDecreaseEven(inputVector);

	sort(inputVector.begin(), inputVector.end());
}

void DoubleOddDecreaseEven(vector<double>& inputVector)
{
	double sumPositiveValues = CalculatePositiveElementSum(inputVector);

	int index = 0;
	for_each(inputVector.begin(), inputVector.end(),
		[&index, &sumPositiveValues](double& value) {
			value = (index % 2) == 0 ? value * 2 : value - sumPositiveValues;
			++index; 
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