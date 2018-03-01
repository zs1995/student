#include <iostream>
enum CTYPE{COREA,COREB};

class SingleCore
{
public:
	virtual void show() = 0;
}

class SingleCoreA:public SingleCore
{
public:
	void show(){ std::cout<<"SingleCore A"<<std::endl;}
}

class SingleCoreB:public SingleCore
{
public:
	void show(){ std::cout<<"SingleCore B"<<std::endl;}
}

class Factory
{
public:

	virtual SingleCore *CreateSingleCore() = 0;
/*	SingleCore* CreateSingleCore(enum CTYPE ctype)
	{
		if(ctype == COREA)
			return new SingleCoreA();
		else if(ctype == COREB)
			return new SingleCoreB();
		else
			return NULL;
	} */
}

class FactoryA:public Factory
{
public:
	SingleCoreA* CreateSingleCore(){return new SingleCoreA;}
};

class FactoryB:public Factory
{
public:
	SingleCoreB* CreateSingleCore(){return new SingleCoreB;}
};
