#ifndef _CPLUS_H
#define _CPLUS_H
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include "Cplusplus.h"

class CPlus{

public:
	CPlus();
	~CPlus();
	CPlus(const CPlus &);
	CPlus &operator =(const CPlus &);

	void SetRet(int n){ m_nRet = n;}
	int GetRet(){ return m_nRet;}

	void SetFlag(char *sFlag){strcpy(m_sFlag,sFlag);}
	char * GetFlag(){return m_sFlag;}

	CPlus getCplus() const 
	{
		CPlus c;
		return c;
	}

private:
		int m_nRet;
		char *m_sFlag;

};



#endif //CPLUS_H