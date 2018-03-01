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
	bool InitConPool();//初始化连接池
	void DeleteConPool();//删除连接池
	int* BeginOciThread(void* startAdress);//开启oci线程
	bool Logon();
	bool Logoff();

	CDataTable* Execute(const char* strCommand);//查询
	bool ExecuteNonQuery(const char* strCommand);//执行操作
	bool ExecuteProc(const char* strCommand,int n,...);//执行存储过程
protected:
	bool ReOpen();//数据库重连
	CDbPool& m_DbPool;
	OCISvcCtx * m_Svchp;
	int m_iConState; //连接状态： 0连接正常；1正在连接；2连接丢失 线程共享变量
};
#endif