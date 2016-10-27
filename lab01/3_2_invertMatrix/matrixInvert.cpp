#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

typedef double matrix[3][3];

void ProcessFile(ifstream& matrixFileStream);
void GetMatrixFromStream(ifstream& matrixFileStream, matrix& sourceMatrix);
bool GetInvertMatrix(const matrix& sourceMatrix, matrix& invertMatrix);
void GetMinorMatrix(const matrix& sourceMatrix, matrix& minorMatrix);
void TransposeMatrix(matrix& matrixToTranspose);
double CalculateDeterminantForMatrix(const matrix& sourceMatrix);
void MultiplyMatrixOnNumber(matrix& matrixToInvert, double determinant);
void WriteMatrixToConsole(const matrix& matrix);

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Must be 1 argument: <matrix file1>" << endl;
		return 1;
	}

	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	try
	{
		ProcessFile(input);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}

void ProcessFile(ifstream& matrixFileStream)
{
	double sourceMatrix[3][3];
	GetMatrixFromStream(matrixFileStream, sourceMatrix);
	double invertMatrix[3][3];
	if (!GetInvertMatrix(sourceMatrix, invertMatrix))
	{
		throw invalid_argument("Unknown error while inverting");
	}
	WriteMatrixToConsole(invertMatrix);
}

void GetMatrixFromStream(ifstream& matrixFileStream, matrix& sourceMatrix)
{
	int rowIndex = 0;
	string matrixRowLine;
	stringstream stringStream;

	while (rowIndex < 3 && getline(matrixFileStream, matrixRowLine))
	{
		stringStream.str(matrixRowLine);
		stringStream.clear();
		int columnIndex = 0;
		while (stringStream.good() && columnIndex < 3)
		{
			double matrixElement;
			stringStream >> matrixElement;

			if (stringStream.fail())
			{
				throw invalid_argument("matrix elements must be numbers");
			}

			sourceMatrix[rowIndex][columnIndex++] = matrixElement;
		}

		if (columnIndex != 3)
		{
			throw invalid_argument("must be 3 element in row");
		}

		++rowIndex;
	}

	if (rowIndex != 3)
	{
		throw invalid_argument("must be 3 rows");
	}
}

bool GetInvertMatrix(const matrix& sourceMatrix, matrix& invertMatrix)
{
	double determinant = CalculateDeterminantForMatrix(sourceMatrix);
	
	if (abs(determinant) <= DBL_EPSILON)
	{
		return false;
	}

	GetMinorMatrix(sourceMatrix, invertMatrix);
	TransposeMatrix(invertMatrix);
	double revertDeterminant = 1 / determinant;
	MultiplyMatrixOnNumber(invertMatrix, revertDeterminant);
	return true;
}

void GetMinorMatrix(const matrix& sourceMatrix, matrix& minorMatrix)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			minorMatrix[i][j] = sourceMatrix[(i + 1) % 3][(j + 1) % 3] * sourceMatrix[(i + 2) % 3][(j + 2) % 3] -
				sourceMatrix[(i + 2) % 3][(j + 1) % 3] * sourceMatrix[(i + 1) % 3][(j + 2) % 3];
		}
	}
}

void TransposeMatrix(matrix& matrixToTranspose)
{
	swap(matrixToTranspose[0][1], matrixToTranspose[1][0]);
	swap(matrixToTranspose[0][2], matrixToTranspose[2][0]);
	swap(matrixToTranspose[1][2], matrixToTranspose[2][1]);
}

void MultiplyMatrixOnNumber(matrix& matrixToMultiply, double number)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			matrixToMultiply[i][j] *= number;
		}
	}
}

void WriteMatrixToConsole(const matrix& matrix)
{
	cout.setf(ios::fixed);
	cout.precision(3);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

double CalculateDeterminantForMatrix(const matrix& sourceMatrix)
{
	const double(&sm)[3][3] = sourceMatrix;
	double determinant = (sm[0][0] * sm[1][1] * sm[2][2]) + (sm[0][1] * sm[1][2] * sm[2][0]) + (sm[0][2] * sm[1][0] * sm[2][1]) -
		(sm[0][2] * sm[1][1] * sm[2][0]) - (sm[0][0] * sm[2][1] * sm[1][2]) - (sm[1][0] * sm[0][1] * sm[2][2]);
	return determinant;
}