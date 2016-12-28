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
	CRational const operator+(CRational const& rational)const;
	CRational const operator-(CRational const& rational)const;
	CRational& operator+=(CRational const& rational);
	CRational& operator-=(CRational const& rational);
	CRational const operator*(CRational const& rational)const;
	CRational const operator/(CRational const& rational)const;
	CRational& operator*=(CRational const& rational);
	CRational& operator/=(CRational const& rational);
	bool operator==(CRational const& rational)const;
	bool operator!=(CRational const& rational)const;
	bool operator<(CRational const& rational)const;
	bool operator<=(CRational const& rational)const;
	bool operator>(CRational const& rational)const;
	bool operator>=(CRational const& rational)const;

	std::pair<int, CRational> ToCompoundFraction()const;
private:
	int m_numerator;
	int m_denominator;
	static int Gcd(int a, int b);
	static int Lcm(int a, int b);
};

std::ostream& operator<<(std::ostream& output, CRational const& rational);
std::istream& operator>>(std::istream& input, CRational& rational);
int StrToInt(std::string const& str);

CRational const operator+(int integer, CRational const& rational);
CRational const operator-(int integer, CRational const& rational);
CRational const operator*(int integer, CRational const& rational);
CRational const operator/(int integer, CRational const& rational);
CRational const operator==(int integer, CRational const& rational);
CRational const operator!=(int integer, CRational const& rational);
CRational const operator>=(int integer, CRational const& rational);
CRational const operator<=(int integer, CRational const& rational);
CRational const operator>(int integer, CRational const& rational);
CRational const operator<(int integer, CRational const& rational);