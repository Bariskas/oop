#pragma once
#include <iostream>
#include <istream>
#include <algorithm>
#include <vector>  
#include <string>
#include <sstream>
#include <cstdio>
#include <iterator> 

void ConvertVector();

std::vector<double> GetVectorFromCin(std::istream& inputStream);

double CalculatePositiveElementSum(const std::vector<double>& inputVector);
void DoubleOddDecreaseEven(std::vector<double>& inputVector);
void SortAndOutputVector(std::vector<double>& inputVector);