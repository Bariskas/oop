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
	double sumPositiveValues = std::accumulate(inputVector.begin(), inputVector.end(), 0.,
		[] (double sum, double value) {
			return value >= 0. ? sum += value : sum;
		}
	);

	return sumPositiveValues;
}