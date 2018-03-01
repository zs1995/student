#ifndef __CDBPOOL_H__
#define __CDBPOOL_H__
#include <iostream>
#include "oci.h"
#include "DataTable.h"
#include <list>
using namespace std;
#define		THREAD_STATUS_SLEEP		0//线程休眠
#define		THREAD_STATUS_RUN		1//启动线程
#define		THREAD_STATUS_RUNING	2//线程正在运行
#define		THREAD_STATUS_QUITING	3//正在退出线程
#define		THREAD_STATUS_QUIT		4//线程已经退出
#define		THREAD_STATUS_FAILD		5//线程启动失败

class OCI_THREAD_INFO {
public:
	OCIThreadId     *thrid;
	OCIThreadHandle *thrhp;
	OCISvcCtx *svchp;//服务内容句柄
	int iStatus;//线程状态，用于控制线程，//0休眠；1运行；2正在退出;3已经退出
};
class CDbPool 
{
	friend class CDBConnection;
public:
	static CDbPool& GetInstance()	//获取单一实例
	{
		static CDbPool conn;
		return conn;
	}

	CDbPool();
	~CDbPool(void);
	bool CreatePool(const char* strDB,const char* strUser,const char* strPwd);//创建连接池
	void DeletePool();//删除连接池
	bool BeginOciThread(void (*startAdress)(void  *),OCI_THREAD_INFO* ociInfo);//开启oci线程
	void EndOciThread(OCI_THREAD_INFO* pOciInfo);//结束线程
protected:
	void CheckErr(sword status);
	bool ReOpen();//数据库重连
	list<OCI_THREAD_INFO*> m_OciThreadList;
	OCIError   *errhp;//oracle的错误句柄，可以获取错误信息  
	OCIEnv     *envhp;//环境句柄，要使用oracle数据库，必须首先获得环境句柄  
	OCICPool   *poolhp;//连接池句柄

	OraText *poolName;//连接池名字
	sb4 poolNameLen;
	OraText pDatabase[60];
	OraText pUserName[60];
	OraText pPassWord[60];
	ub4 conMin ;//最小连接数
	ub4 conMax;//最大连接数
	ub4 conIncr;
};

#endif
