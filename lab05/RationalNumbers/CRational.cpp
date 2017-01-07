#include "stdafx.h"
#include "NumberUtils.h"
#include "CRational.h"

using namespace std;

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	auto gcd = NumberUtils::Gcd(abs(m_numerator), abs(m_denominator));
	m_numerator /= gcd;
	m_denominator /= gcd;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(GetNumerator()) / GetDenominator();
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-GetNumerator(), GetDenominator());
}

CRational& CRational::operator+=(CRational const& rational)
{
	*this = *this + rational;
	return *this;
}

CRational& CRational::operator-=(CRational const& rational)
{
	*this = *this - rational;
	return *this;
}

CRational& CRational::operator*=(CRational const& rational)
{
	*this = *this * rational;
	return *this;
}

CRational& CRational::operator/=(CRational const& rational)
{
	*this = *this / rational;
	return *this;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int intPart = this->GetNumerator() / this->GetDenominator();
	CRational fractionPart(this->GetNumerator() - intPart *  this->GetDenominator(), this->GetDenominator());
	return pair<int, CRational>(intPart, fractionPart);
}

std::ostream& operator<<(std::ostream& output, CRational const& rational)
{
	output << rational.GetNumerator() << '/' << rational.GetDenominator();
	return output;
}

std::istream& operator >> (std::istream& input, CRational& rational)
{
	string potentialRational;
	input >> potentialRational;

	auto slashPos = potentialRational.find('/');
	if (slashPos == std::string::npos)
	{
		throw invalid_argument("Wrong rational number format.");
	}

	string numeratorStr = potentialRational.substr(0, slashPos);
	string denumeratorStr = potentialRational.substr(slashPos + 1, potentialRational.length() - numeratorStr.length() - 1);

	CRational parsedRational(NumberUtils::StrToInt(numeratorStr), NumberUtils::StrToInt(denumeratorStr));
	swap(rational, parsedRational);

	return input;
}

CRational const operator+(CRational const& leftRational, CRational const& rightRational)
{
	int lcm = NumberUtils::Lcm(leftRational.GetDenominator(), rightRational.GetDenominator());
	int numerator = leftRational.GetNumerator() * (lcm / leftRational.GetDenominator())
		+ rightRational.GetNumerator() * (lcm / rightRational.GetDenominator());
	return CRational(numerator, lcm);
}

CRational const operator-(CRational const& leftRational, CRational const& rightRational)
{
	return leftRational + (-rightRational);
}

CRational const operator*(CRational const& leftRational, CRational const& rightRational)
{
	return CRational(leftRational.GetNumerator() * rightRational.GetNumerator(),
		leftRational.GetDenominator() * rightRational.GetDenominator());
}

CRational const operator/(CRational const& leftRational, CRational const& rightRational)
{
	return leftRational * CRational(rightRational.GetDenominator(), rightRational.GetNumerator());
}

bool operator==(CRational const& leftRational, CRational const& rightRational)
{
	return leftRational.GetNumerator() == rightRational.GetNumerator()
		&& leftRational.GetDenominator() == rightRational.GetDenominator();
}

bool operator!=(CRational const& leftRational, CRational const& rightRational)
{
	return !(leftRational == rightRational);
}

bool operator>=(CRational const& leftRational, CRational const& rightRational)
{
	return !(leftRational < rightRational);
}

bool operator<=(CRational const& leftRational, CRational const& rightRational)
{
	return !(leftRational > rightRational);
}

bool operator>(CRational const& leftRational, CRational const& rightRational)
{
	return leftRational.ToDouble() > rightRational.ToDouble();
}

bool operator<(CRational const& leftRational, CRational const& rightRational)
{
	return leftRational.ToDouble() < rightRational.ToDouble();
}