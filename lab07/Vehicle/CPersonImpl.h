#pragma once
#include "stdafx.h"

template <class Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl(std::string name)
		: m_name(name)
	{}

	std::string GetName()const
	{
		return m_name;
	}
private:
	std::string m_name;
};