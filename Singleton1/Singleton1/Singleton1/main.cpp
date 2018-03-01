#include "Singleton.h"

int main()
{
	Singleton *st = Singleton::GetInstance("SingletonB");
	Singleton *st2 = Singleton::GetInstance("SingletonA");
	st->Show();
	st2->Show();
	getchar();
	return 0;
}