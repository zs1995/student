#include <stdio.h>
#include "DbPool.h"

CDbPool::CDbPool()
{
	envhp = NULL;
	conMin = 2;
	conMax = 50;//最大支持50个连接
	conIncr = 1;
}
CDbPool::~CDbPool(void)
{
}

//创建连接池
bool CDbPool::CreatePool(const char* strDB,const char* strUser,const char* strPwd)
{
	try
	{
		int iLen = 60;
		strcpy((char*)pDatabase,strDB);

		strcpy((char*)pUserName,strUser);

		strcpy((char*)pPassWord,strPwd);

		OCIEnvCreate(&envhp, OCI_THREADED, (dvoid *)0,  0,0, 0, 0, 0);

		(void) OCIHandleAlloc((dvoid *) envhp, (dvoid **) &errhp, OCI_HTYPE_ERROR,
			(size_t) 0, (dvoid **) 0);


		(void) OCIHandleAlloc((dvoid *) envhp, (dvoid **) &poolhp, OCI_HTYPE_CPOOL,
			(size_t) 0, (dvoid **) 0);

		OCIThreadProcessInit ();
		CheckErr (OCIThreadInit (envhp, errhp));

		/* CREATE THE CONNECTION POOL */
		CheckErr (OCIConnectionPoolCreate(envhp, 
			errhp,poolhp, &poolName, &poolNameLen,
			pDatabase,strlen((char*)pDatabase),
			conMin, conMax, conIncr,
			pUserName,strlen((char*)pUserName),
			pPassWord,strlen((char*)pPassWord),OCI_DEFAULT));
	}catch (...)
	{
		return false;
	}
	return true;
}
//终止OCI环境，在退出程序时必须调用
void CDbPool::DeletePool()
{
	try
	{
		if (envhp)
		{
			CheckErr(OCIConnectionPoolDestroy(poolhp, errhp, OCI_DEFAULT));
			CheckErr(OCIHandleFree((dvoid *)poolhp, OCI_HTYPE_CPOOL));
			CheckErr (OCIThreadTerm (envhp, errhp));
			CheckErr(OCIHandleFree((dvoid *)errhp, OCI_HTYPE_ERROR));
			OCIHandleFree(envhp, OCI_HTYPE_ENV);
			envhp = NULL;
		}
	}
	catch (...)
	{
	}
}

//开启oci线程
bool CDbPool::BeginOciThread(void (*startAdress)(void  *),OCI_THREAD_INFO* ociInfo)
{
	try
	{
		ociInfo->svchp = (OCISvcCtx *)0;
		ociInfo->iStatus = THREAD_STATUS_RUN;
		CheckErr (OCIThreadIdInit (envhp, errhp, &ociInfo->thrid));
		CheckErr (OCIThreadHndInit (envhp, errhp, &ociInfo->thrhp));
		CheckErr (OCIThreadCreate (envhp, errhp, startAdress, (dvoid *) ociInfo, ociInfo->thrid, ociInfo->thrhp));
		return true;
	}catch(...)
	{
		return false;
	}
	return false;
}
//在退出线程时,在线程外部调用
void CDbPool::EndOciThread(OCI_THREAD_INFO* pOciInfo)
{
	try
	{
		CheckErr (OCIThreadClose (envhp, errhp, pOciInfo->thrhp));
		CheckErr (OCIThreadIdDestroy (envhp, errhp, &pOciInfo->thrid));
		CheckErr (OCIThreadHndDestroy (envhp, errhp, &pOciInfo->thrhp));
	}catch(...)
	{
	}
}
void CDbPool::CheckErr(sword status)
{
	sb4		m_s_nErrCode=0;
	char	m_s_szErr[512];
	char strLog[1024];
	switch (status)
	{
	case OCI_SUCCESS:
		break;
	case OCI_SUCCESS_WITH_INFO:
		printf("Error - OCI_SUCCESS_WITH_INFO\n");
		break;
	case OCI_NEED_DATA:
		printf("Error - OCI_NEED_DATA\n");
		throw 1;
		break;
	case OCI_NO_DATA:
		printf("Error - OCI_NODATA\n");
		break;
	case OCI_ERROR:
		OCIErrorGet(errhp,(ub4)1,(text*)NULL,&m_s_nErrCode,(OraText*)m_s_szErr,512,OCI_HTYPE_ERROR);
		sprintf(strLog,"Error - OCI_ERROR\n\tErrorCode:%d\n\tErrorInfo%s",m_s_nErrCode,m_s_szErr);
		printf(strLog);
		throw 1;
		break;
	case OCI_INVALID_HANDLE:
		printf("Error - OCI_INVALID_HANDLE\n");
		throw 1;
		break;
	case OCI_STILL_EXECUTING:
		printf("Error - OCI_STILL_EXECUTE\n");
		throw 1;
		break;
	case OCI_CONTINUE:
		printf("Error - OCI_CONTINUE\n");
		throw 1;
		break;
	default:
		break;
	}
}
