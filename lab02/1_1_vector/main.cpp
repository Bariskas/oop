#include "VectorConverting.h"

using namespace std;

int main()
{
	vector<double> inputVector(istream_iterator<double>(cin), (istream_iterator<double>()));

	ConvertVector(inputVector);

	cout.setf(ios::fixed);
	cout.precision(3);
	copy(inputVector.begin(), inputVector.end(), ostream_iterator<double>(cout, ", "));

	return 0;
}