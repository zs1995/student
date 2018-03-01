#ifndef RESUME_H
#define RESUME_H

#include <iostream>

using namespace std;

class Resume
{
protected:
	char *name;
public:
	Resume(){}
	virtual ~Resume(){}
	virtual Resume * Clone(){return NULL;}
	virtual void Set(char *n){}
	virtual void Show(){}
};

#endif