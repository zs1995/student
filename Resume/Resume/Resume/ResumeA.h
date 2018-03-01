#ifndef RESUMEA_H
#define RESUMEA_H

#include "Resume.h"

class ResumeA:public Resume
{
public:
	ResumeA(const char* str);
	ResumeA(const ResumeA &);
	~ResumeA();
	ResumeA* Clone();
	void Show();
};

#endif