#include "Cplusplus.h"

Cplusplus::Cplusplus()
{

}

Cplusplus::~Cplusplus()
{

}

Cplusplus::Cplusplus(const Cplusplus& rt)
{
	m_nPlusRet = rt.m_nPlusRet;
}

Cplusplus & Cplusplus::operator=(const Cplusplus& rt)
{
	if(this == &rt)
		return *this;

	m_nPlusRet = rt.m_nPlusRet;
	return *this;

}