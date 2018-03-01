#include "Cplus.h"

int main()
{
	 CPlus c;
	c.getCplus();
	CPlus b = c.getCplus();
	std::cout << c.GetRet() << "----" << c.GetFlag()<<std::endl;
	getchar();
}