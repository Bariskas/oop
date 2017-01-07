#pragma once

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);
	int GetNumerator()const;
	int GetDenominator()const;
	double ToDouble()const;

	CRational const operator+()const;
	CRational const operator-()const;
	CRational& operator+=(CRational const& rational);
	CRational& operator-=(CRational const& rational);
	CRational& operator*=(CRational const& rational);
	CRational& operator/=(CRational const& rational);

	std::pair<int, CRational> ToCompoundFraction()const;
private:
	int m_numerator;
	int m_denominator;
};

std::ostream& operator<<(std::ostream& output, CRational const& rational);
std::istream& operator>>(std::istream& input, CRational& rational);

CRational const operator+(CRational const& leftRational, CRational const& rightRational);
CRational const operator-(CRational const& leftRational, CRational const& rightRational);
CRational const operator*(CRational const& leftRational, CRational const& rightRational);
CRational const operator/(CRational const& leftRational, CRational const& rightRational);
bool operator==(CRational const& leftRational, CRational const& rightRational);
bool operator!=(CRational const& leftRational, CRational const& rightRational);
bool operator>=(CRational const& leftRational, CRational const& rightRational);
bool operator<=(CRational const& leftRational, CRational const& rightRational);
bool operator>(CRational const& leftRational, CRational const& rightRational);
bool operator<(CRational const& leftRational, CRational const& rightRational);