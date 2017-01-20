#include "stdafx.h"
#include "MyString.h"

CMyString::CMyString()
	: m_pString(nullptr)
	, m_size(0)
{
}

CMyString::CMyString(const char* pString)
	: m_size(strlen(pString))
{
	m_pString = new char[m_size + 1]();
	std::copy(pString, pString + m_size, stdext::checked_array_iterator<char*>(m_pString, m_size));
	//m_pString = static_cast<char*>(calloc(m_size, sizeof(char)));
	//memcpy_s(m_pString, m_size, pString, m_size);
}

CMyString::CMyString(const char* pString, size_t length)
	: m_size(length)
{
	//m_pString = static_cast<char*>(calloc(m_size, sizeof(char)));
	//memcpy_s(m_pString, m_size, pString, m_size);
	m_pString = new char[m_size + 1]();
	std::copy(pString, pString + length, stdext::checked_array_iterator<char*>(m_pString, m_size + 1));
}

CMyString::CMyString(CMyString const& other)
	: m_size(other.GetLength())
{
	if (m_size != 0)
	{
		m_pString = new char[m_size + 1]();
		std::copy(other.m_pString, other.m_pString + m_size, stdext::checked_array_iterator<char*>(m_pString, m_size + 1));
		//memcpy_s(m_pString, m_size, other.m_pString, m_size);
	}
}

CMyString::CMyString(CMyString&& other)
	: m_pString(other.m_pString)
	  , m_size(other.GetLength())
{
	delete[] other.m_pString;
}

CMyString::CMyString(std::string const& stlString)
	: m_size(stlString.length())
{
	m_pString = new char[m_size + 1]();
	std::copy(stlString.begin(), stlString.end(), stdext::checked_array_iterator<char*>(m_pString, m_size + 1));
}

CMyString::~CMyString()
{
	delete[] m_pString;
}

size_t CMyString::GetLength() const
{
	return m_size;
}

const char* CMyString::GetStringData() const
{
	return m_pString;
}

CMyString const CMyString::SubString(size_t start, size_t length) const
{
	return CMyString(this->GetStringData(), length);
}

CMyString& CMyString::operator=(CMyString const& myString)
{
	if (this == &myString) {
		return *this;
	}
	CMyString temp(myString);
	m_pString = temp.m_pString;
	m_size = temp.m_size;
	return *this;
}

char CMyString::operator[](size_t index)
{
	return *(m_pString + index);
}

void CMyString::Clear()
{
	delete[] m_pString;
	m_size = 0;
}

CMyString const operator+(CMyString const& leftMyString, CMyString const& rightMyString)
{
	auto result = new char[leftMyString.m_size + rightMyString.m_size + 1]();
	std::copy(leftMyString.m_pString, leftMyString.m_pString + leftMyString.m_size, 
		stdext::checked_array_iterator<char*>(result, leftMyString.m_size));
	std::copy(rightMyString.m_pString, rightMyString.m_pString + rightMyString.m_size,
		stdext::checked_array_iterator<char*>(result + leftMyString.m_size, rightMyString.m_size));
	CMyString myString(result);
	delete[] result;
	return std::move(myString);
}
