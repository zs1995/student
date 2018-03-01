#ifndef RESUMEB_H
#define RESUMEB_H
#include "Resume.h"

class ResumeB:public Resume
{
public:
	ResumeB(const char* name);
	ResumeB(const ResumeB &);
	~ResumeB();
	ResumeB* Clone();
	void Show();
};

#endif