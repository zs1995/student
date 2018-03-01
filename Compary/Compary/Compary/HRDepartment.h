#ifndef HRDEPARTMENT_H
#define HRDEPARTMENT_H

#include "Compary.h"

class HRDepartment:public Compary
{
public:
	HRDepartment(string name):Compary(name){}
	virtual ~HRDepartment(){}

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