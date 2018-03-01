#include "Resume.h"
#include "ResumeA.h"
#include "ResumeB.h"

int main(int argc,char argv)
{
	Resume *r1 = new ResumeA("A");
	Resume *r2 = new ResumeB("B");
	Resume *r3 = r1->Clone();
	Resume *r4 = r2->Clone();

	r1->Show();
	r2->Show();

	delete r1;
	delete r2;

	r1 = NULL;
	r2 = NULL;

	r3->Show();
	r4->Show();

	delete r3;
	delete r4;

	r3 = NULL;
	r4 = NULL;

	getchar();
	return 0;
}