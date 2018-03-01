#ifndef SINGLETONA_H
#define SINGLETONA_H
#include "Singleton.h"

class SingletonA:public Singleton
{
	friend class Singleton;
public:
	void Show(){cout << "SingletonA" <<endl;}
private:
	SingletonA(){}
};

#endif