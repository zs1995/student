#ifndef FINANCEDEPARTMENT_H
#define FINANCEDEPARTMENT_H

#include "Compary.h"

class FinanceDepartment:public Compary
{
public:
	FinanceDepartment(string name):Compary(name){}
	virtual ~FinanceDepartment(){}

	virtual void Show(int depth)
	{
		for(int i = 0;i<depth;i++)
		{
			cout << "-";
		}
		cout << m_name <<endl;
	}
};

#endif