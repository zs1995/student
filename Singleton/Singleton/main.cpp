#include "Singleton.h"
void DoIt()
{
	CEmperor *pEmperor1 = CEmperor::GetInstance();
	pEmperor1->SetEmperorTag("95");
	pEmperor1->EmperorInfo();

	CEmperor *pEmperor2 = CEmperor::GetInstance();
	pEmperor2->EmperorInfo();

	CEmperor *pEmperor3 = CEmperor::GetInstance();
	pEmperor3->EmperorInfo();

	CEmperor *pEmperor4 = pEmperor3;
	pEmperor4->EmperorInfo();

	CEmperor *pEmperor5 = NULL;
	pEmperor5 = pEmperor4;
	pEmperor5->EmperorInfo();

	CEmperor::ReleaseInstance();
}

int main(int argc, char* argv[])
{
	DoIt();

	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtDumpMemoryLeaks();

	getchar();
	return 0;
}