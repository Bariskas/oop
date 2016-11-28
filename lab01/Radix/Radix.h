#pragma once

#include <string>
#include <iostream>
#include <limits>
#include <boost/format.hpp>

std::string ChangeRadix(const std::string& sourceRadix, const std::string& destRadix, const std::string& value);
unsigned StringToNumber(const std::string& stringToConvert, int sourceRadix = 10);
std::string NumberToString(unsigned value, unsigned radix);
int CharToNumber(char input);
char NumberToChar(int input);
bool IsMultiplicationOverflow(unsigned firstMultiplier, unsigned secondMultiplier);
bool IsAdditionOverflow(unsigned firstArg, unsigned secondArg);
bool IsValidRadix(int radix);
unsigned MultiplicationWithOverflowCheck(unsigned arg1, unsigned arg2);
unsigned AdditionWithOverflowCheck(unsigned arg1, unsigned arg2);