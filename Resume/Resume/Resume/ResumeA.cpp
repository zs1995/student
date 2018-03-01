#include "ResumeA.h"

ResumeA::ResumeA(const char* str)
{
	if(str == NULL)
	{
		name = new char[1];
		name[0] = '\0';
	}
	else
	{
		name = new char[strlen(str)+1];
		strcpy(name,str);
	}
}

ResumeA::ResumeA(const ResumeA &r)
{
	name = new char[strlen(r.name)+1];
	strcpy(name,r.name);
}

ResumeA::~ResumeA()
{
	delete[] name;
}

ResumeA* ResumeA::Clone()
{
	return new ResumeA(*this);
}

void ResumeA::Show()
{
	cout << "ResumeA name:" << name << endl;
}
