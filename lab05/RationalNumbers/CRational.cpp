#include "stdafx.h"
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
	auto gcd = Gcd(abs(m_numerator), abs(m_denominator));
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

CRational const CRational::operator+(CRational const& rational) const
{
	int lcm = Lcm(GetDenominator(), rational.GetDenominator());
	int numerator = GetNumerator() * (lcm / GetDenominator()) 
		+ rational.GetNumerator() * (lcm / rational.GetDenominator());
	return CRational(numerator, lcm);
}

CRational const CRational::operator-(CRational const& rational) const
{
	return *this + -rational;
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

CRational const CRational::operator*(CRational const& rational) const
{
	return CRational(GetNumerator() * rational.GetNumerator(), 
		GetDenominator() * rational.GetDenominator());
}

CRational const CRational::operator/(CRational const& rational) const
{
	return *this * CRational(rational.GetDenominator(), rational.GetNumerator());
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

bool CRational::operator==(CRational const& rational) const
{
	return this->GetNumerator() == rational.GetNumerator() && this->GetDenominator() == rational.GetDenominator();
}

bool CRational::operator!=(CRational const& rational) const
{
	return !(*this == rational);
}

bool CRational::operator<(CRational const& rational) const
{
	return this->ToDouble() < rational.ToDouble();
}

bool CRational::operator>(CRational const& rational) const
{
	return this->ToDouble() > rational.ToDouble();
}

bool CRational::operator<=(CRational const& rational) const
{
	return !(*this > rational);
}

bool CRational::operator>=(CRational const& rational) const
{
	return !(*this < rational);
}

int CRational::Gcd(int a, int b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}
	return a;
}

int CRational::Lcm(int a, int b)
{
	return a / Gcd(a, b) * b;
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

	CRational parsedRational(StrToInt(numeratorStr), StrToInt(denumeratorStr));
	swap(rational, parsedRational);

	return input;
}

int StrToInt(std::string const& str)
{
	bool isAllDigits = all_of(str.begin(), str.end(), [](char ch) {return isdigit(ch); });
	if (!isAllDigits)
	{
		throw runtime_error("Bad number");
	}
	return stoi(str);
}

CRational const operator+(int integer, CRational const& rational)
{
	return rational + integer;
}

CRational const operator-(int integer, CRational const& rational)
{
	return -rational + integer;
}

CRational const operator*(int integer, CRational const& rational)
{
	return rational * integer;
}

CRational const operator/(int integer, CRational const& rational)
{
	return integer * CRational(rational.GetDenominator(), rational.GetNumerator());
}

CRational const operator==(int integer, CRational const& rational)
{
	return rational == integer;
}

CRational const operator!=(int integer, CRational const& rational)
{
	return rational != integer;
}
