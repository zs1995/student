//#include <windows.h>
#include "DBConnection.h"


//插入数据的线程
void InsertThreadProc(void* arg)
{
	OCI_THREAD_INFO* pThrdInfo = (OCI_THREAD_INFO*)arg;
	char strSql[SQL_LEN];
	CDbPool& dbPool = CDbPool::GetInstance();
	CDBConnection* m_pDb = new CDBConnection(dbPool);
	m_pDb->Logon();
	while (pThrdInfo->iStatus == THREAD_STATUS_RUN)
	{
		printf("insert begin\n");
		sprintf(strSql,"insert into table1 values(1,2020,'make')");
		bool bRet = false;
		bRet = m_pDb->ExecuteNonQuery(strSql);
		cout << bRet << "---" << endl;
		sleep(1);
		printf("insert end\n");

// 		printf("insert begin\n");
// 		sprintf(strSql,"begin pro_table1(1,2057,'Jackk');end;");
// 		bool bRet = false;
// 		bRet = m_pDb->ExecuteProc(strSql,6,1,2057,"Jackk");
// 		cout << bRet << "---" << endl;
// 		sleep(1);
// 		printf("insert end\n");
	}
	m_pDb->Logoff();
	delete m_pDb;
	pThrdInfo->iStatus = THREAD_STATUS_QUIT;
}

//更新数据的线程
void UpdateThreadProc(void* arg)
{
	OCI_THREAD_INFO* pThrdInfo = (OCI_THREAD_INFO*)arg;
	char strSql[SQL_LEN];
	CDbPool& dbPool = CDbPool::GetInstance();
	CDBConnection* m_pDb = new CDBConnection(dbPool);
	m_pDb->Logon();
	while (pThrdInfo->iStatus == THREAD_STATUS_RUN)
	{
		sprintf(strSql,"update table1 set id=2 where year = '2020'");
		m_pDb->ExecuteNonQuery(strSql);
		sleep(1);
	}
	m_pDb->Logoff();
	delete m_pDb;
	pThrdInfo->iStatus = THREAD_STATUS_QUIT;
}
//删除数据线程

void DeleteThreadProc(void* arg)
{
	OCI_THREAD_INFO* pThrdInfo = (OCI_THREAD_INFO*)arg;
	char strSql[SQL_LEN];
	CDbPool& dbPool = CDbPool::GetInstance();
	CDBConnection* m_pDb = new CDBConnection(dbPool);
	m_pDb->Logon();
	while (pThrdInfo->iStatus == THREAD_STATUS_RUN)
	{
		sprintf(strSql,"delete table1 where id = 1");
		m_pDb->ExecuteNonQuery(strSql);
		sleep(1);
	}
	m_pDb->Logoff();
	delete m_pDb;
	pThrdInfo->iStatus = THREAD_STATUS_QUIT;
}

//查询数据线程
void SelectThreadProc(void* arg)
{
	static int oldId = 0;
	OCI_THREAD_INFO* pThrdInfo = (OCI_THREAD_INFO*)arg;
	CDbPool& dbPool = CDbPool::GetInstance();
	CDBConnection* m_pDb = new CDBConnection(dbPool);
	m_pDb->Logon();
	CDataTable* table = NULL;
	char strData[1024];
	std::string str;
	int iId;
	char name[120];
	char strSql[SQL_LEN];
	sprintf(strSql,"select id,name from table1");
	table = m_pDb->Execute(strSql);
	while(1)
	{
		if (table != NULL)
		{
			if (table->Next())
			{
				iId = table->GetInt(0);
// 				if (oldId != iId)
// 				{
// 					oldId = iId;
					table->GetString(1,name);
					sprintf(strData,"    id=%d   name=%s",iId,name);
					printf(strData);
					printf("\n");
//				}
			}
		}
		sleep(1);
	}
	delete table;
	m_pDb->Logoff();
	delete m_pDb;
}


int main(int argc,char ** argv)
{

 OCI_THREAD_INFO m_HrdInsert;
 OCI_THREAD_INFO m_HrdUpdate;
 OCI_THREAD_INFO m_HrdDelete;

 m_HrdInsert.thrid = NULL;
 m_HrdUpdate.thrid = NULL;
 m_HrdDelete.thrid = NULL;

 const char *dbname = "192.168.22.70:1521/orcl10g";
 const char *dbusername = "gdmdc";
 const char *dbpassword = "gdmdc";

 bool nRet = false;

 CDbPool& dbPool = CDbPool::GetInstance();

 dbPool.CreatePool(dbname,dbusername,dbpassword);
 nRet = dbPool.BeginOciThread(InsertThreadProc,&m_HrdInsert);
 cout << nRet << endl;
//  nRet = dbPool.BeginOciThread(InsertThreadProc,&m_HrdInsert);
//  cout << nRet << endl;

//  nRet = dbPool.BeginOciThread(SelectThreadProc,&m_HrdInsert);
//  cout << nRet << endl;

 //dbPool.BeginOciThread(DeleteThreadProc,&m_HrdDelete);

 do
 {
	 sleep(1);

 }while (m_HrdInsert.iStatus == THREAD_STATUS_QUIT);

 getchar();

 dbPool.EndOciThread(&m_HrdInsert);
 dbPool.EndOciThread(&m_HrdUpdate);

 return  0;
}