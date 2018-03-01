#include "Cplus.h"
int nIndex = 0;
CPlus::CPlus():m_nRet(10),m_sFlag("myname")
{
	std::cout<<"CPlus |"<<nIndex++<<std::endl;
}

CPlus::~CPlus()
{

}

CPlus::CPlus (const CPlus& rc)
{
	std::cout<<"const CPlus & |"<<nIndex++<<std::endl;
}

CPlus& CPlus::operator = (const CPlus& rc)
{
	if(this == &rc)
		return *this;

	m_nRet = rc.m_nRet;
	return * this;
}

