#include "Singleton.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;
CEmperor* CEmperor::m_pEmperor = NULL;
HANDLE CEmperor::m_pMutex = CreateMutex(NULL, FALSE, NULL);
CEmperor::CGarbo CEmperor::m_Garbo;

CEmperor::CEmperor(void)
{
	cout << "Create CEmperor Instance" << endl;
}

CEmperor::~CEmperor(void)
{
	cout << "Destroy CEmperor Instance and release its resource" << endl;
}

void CEmperor::EmperorInfo(void)
{
	char msgBuffer[50] = { 0 };
	sprintf_s(msgBuffer, 50, "銘那著?議3議3議3... ...(%s).", m_EmperorTag.c_str());
	string msg(msgBuffer);
	cout << msg.c_str() << endl;
}

CEmperor* CEmperor::GetInstance()
{
	if (NULL == m_pEmperor)
	{
		WaitForSingleObject(m_pMutex, INFINITE);
		if (NULL == m_pEmperor)
			m_pEmperor = new CEmperor();
		ReleaseMutex(m_pMutex);
	}
	return m_pEmperor;
}

void CEmperor::ReleaseInstance()
{
	if (NULL != m_pEmperor)
	{
		WaitForSingleObject(m_pMutex, INFINITE);
		if (NULL != m_pEmperor)
		{
			delete m_pEmperor;
			m_pEmperor = NULL;
		}
		ReleaseMutex(m_pMutex);
	}
}
void CEmperor::SetEmperorTag( string tag )
{
	m_EmperorTag = tag;
}