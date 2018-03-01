#ifndef CONCRETECOMPANY_H
#define CONCRETECOMPANY_H

#include "Compary.h"
#include <list>

class ConcreteCompany:public Compary
{
public:
	ConcreteCompany(string name):Compary(name){}
	virtual ~ConcreteCompany(){}

	void Add(Compary* pCom){m_listCompary.push_back(pCom);}

	void Show(int depth)
	{
		for(int i=0; i<depth; i++)
			cout << "-";
		cout << m_name <<endl;
		list<Compary *>::iterator iter = m_listCompary.begin();

		for(;iter != m_listCompary.end();iter++)
		{
			(*iter)->Show(depth + 2);
		}
	}

private:
	list<Compary *> m_listCompary;
};


#endif