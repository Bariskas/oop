#pragma once
#include "CPersonImpl.h"
#include "IPoliceMan.h"

class CPoliceMan : public CPersonImpl<IPoliceMan>
{
public:
	CPoliceMan(std::string name, std::string departamentName)
		: CPersonImpl(name)
		, m_departamentName(departamentName)
	{}

	std::string GetDepartmentName()const final
	{
		return m_departamentName;
	}
private:
	std::string m_departamentName;
};
