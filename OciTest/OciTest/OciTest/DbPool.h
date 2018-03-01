#ifndef __CDBPOOL_H__
#define __CDBPOOL_H__
#include <iostream>
#include "oci.h"
#include "DataTable.h"
#include <list>
using namespace std;
#define		THREAD_STATUS_SLEEP		0//�߳�����
#define		THREAD_STATUS_RUN		1//�����߳�
#define		THREAD_STATUS_RUNING	2//�߳���������
#define		THREAD_STATUS_QUITING	3//�����˳��߳�
#define		THREAD_STATUS_QUIT		4//�߳��Ѿ��˳�
#define		THREAD_STATUS_FAILD		5//�߳�����ʧ��

class OCI_THREAD_INFO {
public:
	OCIThreadId     *thrid;
	OCIThreadHandle *thrhp;
	OCISvcCtx *svchp;//�������ݾ��
	int iStatus;//�߳�״̬�����ڿ����̣߳�//0���ߣ�1���У�2�����˳�;3�Ѿ��˳�
};
class CDbPool 
{
	friend class CDBConnection;
public:
	static CDbPool& GetInstance()	//��ȡ��һʵ��
	{
		static CDbPool conn;
		return conn;
	}

	CDbPool();
	~CDbPool(void);
	bool CreatePool(const char* strDB,const char* strUser,const char* strPwd);//�������ӳ�
	void DeletePool();//ɾ�����ӳ�
	bool BeginOciThread(void (*startAdress)(void  *),OCI_THREAD_INFO* ociInfo);//����oci�߳�
	void EndOciThread(OCI_THREAD_INFO* pOciInfo);//�����߳�
protected:
	void CheckErr(sword status);
	bool ReOpen();//���ݿ�����
	list<OCI_THREAD_INFO*> m_OciThreadList;
	OCIError   *errhp;//oracle�Ĵ����������Ի�ȡ������Ϣ  
	OCIEnv     *envhp;//���������Ҫʹ��oracle���ݿ⣬�������Ȼ�û������  
	OCICPool   *poolhp;//���ӳؾ��

	OraText *poolName;//���ӳ�����
	sb4 poolNameLen;
	OraText pDatabase[60];
	OraText pUserName[60];
	OraText pPassWord[60];
	ub4 conMin ;//��С������
	ub4 conMax;//���������
	ub4 conIncr;
};

#endif
