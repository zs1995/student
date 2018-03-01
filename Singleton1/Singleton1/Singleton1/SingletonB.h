#ifndef SINGLETONB_H
#define SINGLETONB_H
#include "Singleton.h"

class SingletonB:public Singleton
{
	friend class Singleton;
public:
	void Show(){cout << "SingletonB" <<endl;}
private:
	SingletonB(){}
};

#endif