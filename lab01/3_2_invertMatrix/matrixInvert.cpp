#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void ProcessFile(ifstream& matrixFileStream);
void GetMatrixFromStream(ifstream& matrixFileStream, double(&sourceMatrix)[3][3]);
void GetInvertMatrix(double(&sourceMatrix)[3][3], double(&invertMatrix)[3][3]);
void GetMinorMatrix(double(&sourceMatrix)[3][3], double(&minorMatrix)[3][3]);
void TransposeMatrix(double(&matrixToTranspose)[3][3]);
void InvertMatrix(double(&matrixToInvert)[3][3], double determinant);
bool IsOnlyDigitString(const std::string &str);

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
	GetInvertMatrix(sourceMatrix, invertMatrix);
}

void GetMatrixFromStream(ifstream& matrixFileStream, double (&sourceMatrix)[3][3])
{
	int rowIndex = 0;
	string matrixRowLine;
	string tempLine;
	stringstream stringStream;

	while (rowIndex < 3 && getline(matrixFileStream, matrixRowLine))
	{
		stringStream.str(matrixRowLine);
		stringStream.clear();
		int columnIndex = 0;
		while (stringStream.good() && columnIndex < 3)
		{
			stringStream >> tempLine;

			if (!IsOnlyDigitString(tempLine))
			{
				throw invalid_argument("elements in matrix must be digits");
			}

			sourceMatrix[rowIndex][columnIndex++] = stod(tempLine);
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

void GetInvertMatrix(double(&sourceMatrix)[3][3], double(&invertMatrix)[3][3])
{
	double (& sm)[3][3] = sourceMatrix;
	double determinant = (sm[0][0] * sm[1][1] * sm[2][2]) + (sm[0][1] * sm[1][2] * sm[2][0]) + (sm[0][2] * sm[1][0] * sm[2][1]) - 
		(sm[0][2] * sm[1][1] * sm[2][0]) - (sm[0][0] * sm[2][1] * sm[1][2]) - (sm[1][0] * sm[0][1] * sm[2][2]);
	
	double minorMatrix[3][3];
	GetMinorMatrix(sourceMatrix, minorMatrix);
	TransposeMatrix(minorMatrix);
	InvertMatrix(minorMatrix, determinant);
}

void GetMinorMatrix(double(&sourceMatrix)[3][3], double(&minorMatrix)[3][3])
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

void TransposeMatrix(double(&matrixToTranspose)[3][3])
{
	swap(matrixToTranspose[0][1], matrixToTranspose[1][0]);
	swap(matrixToTranspose[0][2], matrixToTranspose[2][0]);
	swap(matrixToTranspose[1][2], matrixToTranspose[2][1]);
}

void InvertMatrix(double(&matrixToTranspose)[3][3], double determinant)
{
	double revertDeterminant = 1 / determinant;
	cout.width(0);
	cout.setf(ios::fixed);
	cout.precision(3);
	cout.width(10);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			cout << (matrixToTranspose[i][j] /= revertDeterminant) << " ";
		}
		cout << endl;
	}
}

bool IsOnlyDigitString(const std::string &str)
{
	return all_of(str.begin(), str.end(), [](char i) { return isdigit(i) || i == '-'; });
}