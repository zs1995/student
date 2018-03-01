#ifndef COMPARY_H
#define COMPARY_H
#include <iostream>
#include <string>

using namespace std;
class Compary
{
public:
	Compary(string name){m_name = name;}

	virtual ~Compary(){}
	virtual void Add(Compary *Comp){};
	virtual void Show(int depth){};
private:
	string m_name;
	friend class ConcreteCompany;
	friend class FinanceDepartment;
	friend class HRDepartment;
};

#endif