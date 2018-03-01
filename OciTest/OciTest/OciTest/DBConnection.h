#ifndef __CDBCONNECTION_H__
#define __CDBCONNECTION_H__
#include <iostream>

#include "oci.h"
#include "DataTable.h"
#include "DbPool.h"

#include <list>
using namespace std;

class CDBConnection 
{
public:

	CDBConnection(CDbPool& dbPool);
	~CDBConnection(void);
	bool InitConPool();//��ʼ�����ӳ�
	void DeleteConPool();//ɾ�����ӳ�
	int* BeginOciThread(void* startAdress);//����oci�߳�
	bool Logon();
	bool Logoff();

	CDataTable* Execute(const char* strCommand);//��ѯ
	bool ExecuteNonQuery(const char* strCommand);//ִ�в���
	bool ExecuteProc(const char* strCommand,int n,...);//ִ�д洢����
protected:
	bool ReOpen();//���ݿ�����
	CDbPool& m_DbPool;
	OCISvcCtx * m_Svchp;
	int m_iConState; //����״̬�� 0����������1�������ӣ�2���Ӷ�ʧ �̹߳������
};
#endif