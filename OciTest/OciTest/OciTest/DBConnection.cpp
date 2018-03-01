#include <stdio.h>
#include "DBConnection.h"

CDBConnection::CDBConnection(CDbPool& dbPool)
:m_DbPool(dbPool)
{
	m_iConState = 2;//δ����
	m_Svchp = NULL;
}
CDBConnection::~CDBConnection(void)
{
}
//��ȡ���ݿ�����
bool CDBConnection::Logon()
{

	m_iConState = 1;
	if (m_Svchp != 0)//�Ѿ�����
	{
		m_iConState = 0;
		return true;
	}
	try
	{
		m_DbPool.CheckErr(OCILogon2(m_DbPool.envhp, m_DbPool.errhp, &m_Svchp, 
			(CONST OraText *)m_DbPool.pUserName, strlen((char*)m_DbPool.pUserName), 
			(CONST OraText *)m_DbPool.pPassWord, strlen((char*)m_DbPool.pPassWord), 
			(CONST OraText *)m_DbPool.poolName, m_DbPool.poolNameLen,
			OCI_CPOOL));
	} catch (...) {
		m_iConState = 2;//���Ӷ�ʧ
		return false;
	}
	m_iConState = 0;
	return true;
}
bool CDBConnection::Logoff()
{
	try
	{
		m_DbPool.CheckErr(OCILogoff(m_Svchp, m_DbPool.errhp));
		m_Svchp=0;
	} catch (...) {
		m_iConState = 2;//���Ӷ�ʧ
		return false;
	}
	m_iConState = 2;//���Ӷ�ʧ
	return true;
}
//���ݿ�����
bool CDBConnection::ReOpen()
{
	if (m_iConState == 1)
	{
		return false;
	} else if (m_iConState == 0)
	{
		return true;
	}
	bool bRet = Logoff();
	if (!bRet)
	{
		return false;
	}
	bRet = Logon();//����
	if (!bRet)
	{
		return false;
	}
	return true;
}

//ִ�����ݲ������
bool CDBConnection::ExecuteNonQuery(const char* strCommand)
{
	if (m_iConState != 0)
	{
		bool bRet = ReOpen();
		if (!bRet)
		{
			return false;
		}
	}
	OCIStmt *phStmt;       //oracle������������  
	try
	{

 		if (OCIHandleAlloc((dvoid *)m_DbPool.envhp, (dvoid **)&phStmt, OCI_HTYPE_STMT, (size_t)0, (dvoid **)0) != OCI_SUCCESS)
 		{
 			cout << "Create STMT error !" << endl;
 			exit(1);
		}

		OCIHandleAlloc((dvoid *)m_DbPool.envhp, (dvoid **)&m_DbPool.errhp, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0);

		m_DbPool.CheckErr(OCIStmtPrepare(phStmt, m_DbPool.errhp, (text *)strCommand, (ub4)strlen(strCommand), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT));
		//׼��Sql���
		//m_DbPool.CheckErr(OCIStmtPrepare2 (m_Svchp, &phStmt, m_DbPool.errhp, (const OraText *) strCommand, strlen((char *) strCommand), NULL, 0,	OCI_NTV_SYNTAX, OCI_DEFAULT));
		//ִ��Sql
		m_DbPool.CheckErr(OCIStmtExecute(m_Svchp, phStmt, m_DbPool.errhp, 1, 0, NULL, NULL, OCI_COMMIT_ON_SUCCESS));
		//m_DbPool.CheckErr(OCIStmtRelease(phStmt, m_DbPool.errhp, (OraText *) NULL, 0, OCI_DEFAULT));
		m_DbPool.CheckErr(OCIHandleFree((dvoid *) phStmt, OCI_HTYPE_STMT));
	}
	catch (...)
	{
		m_iConState = 2;//���Ӷ�ʧ
		return false;
	}
	return true;
}
//ִ�����ݲ�ѯ
CDataTable* CDBConnection::Execute(const char* strCommand)
{
	if (m_iConState != 0)
	{
		bool bRet = ReOpen();
		if (!bRet)
		{
			return NULL;
		}
	}
	ub4   iFileds;
	OCIStmt *phStmt;       //oracle������������  
	CDataTable* pTable = NULL;
	OCIDefine** defhp = NULL;
	try
	{
		//׼��Sql���
		//m_DbPool.CheckErr(OCIStmtPrepare2 (m_Svchp, &phStmt, m_DbPool.errhp, (const OraText *) strCommand, strlen((char *) strCommand), NULL, 0,	OCI_NTV_SYNTAX, OCI_DEFAULT));
		if (OCIHandleAlloc((dvoid *)m_DbPool.envhp, (dvoid **)&phStmt, OCI_HTYPE_STMT, (size_t)0, (dvoid **)0) != OCI_SUCCESS)
		{
			cout << "Create STMT error !" << endl;
			exit(1);
		}

		OCIHandleAlloc((dvoid *)m_DbPool.envhp, (dvoid **)&m_DbPool.errhp, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0);

		m_DbPool.CheckErr(OCIStmtPrepare(phStmt, m_DbPool.errhp, (text *)strCommand, (ub4)strlen(strCommand), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT));
		//ִ��Sql
		m_DbPool.CheckErr(OCIStmtExecute(m_Svchp, phStmt, m_DbPool.errhp, 0, 0, NULL, NULL, OCI_DEFAULT));
		//��ȡ����
		m_DbPool.CheckErr(OCIAttrGet((dvoid*)phStmt, OCI_HTYPE_STMT, (dvoid*)&iFileds, (ub4 *)0, OCI_ATTR_PARAM_COUNT, m_DbPool.errhp));
		pTable = new CDataTable(iFileds,phStmt,m_DbPool.errhp);

		OCIParam  *pRaram = NULL;
		ub2        iType;
		ub2 iColLen;
		defhp = new OCIDefine*[iFileds];
		for (int i = 0; i < (int)iFileds; i++)
		{
			pTable->m_indp[i] = 0;
//			*(indp+i) = 0;
			m_DbPool.CheckErr(OCIParamGet((dvoid*)phStmt, OCI_HTYPE_STMT, m_DbPool.errhp, (dvoid**)&pRaram, (ub4)i+1));
			m_DbPool.CheckErr(OCIAttrGet((dvoid*)pRaram, OCI_DTYPE_PARAM, (dvoid**)&iType,(ub4 *) 0, OCI_ATTR_DATA_TYPE, m_DbPool.errhp));
			m_DbPool.CheckErr(OCIAttrGet((dvoid*)pRaram, OCI_DTYPE_PARAM, (dvoid*)&iColLen, (ub4 *)0, OCI_ATTR_DATA_SIZE, m_DbPool.errhp));
			void* pField = pTable->InitField(i,iColLen,iType);
			if (iType == SQLT_NUM) iType = SQLT_CHR;//Number������Ҫ��char����ȡ
			m_DbPool.CheckErr(OCIDefineByPos(phStmt, defhp+i, m_DbPool.errhp, i+1, (dvoid*)pField, (sb4)iColLen, iType, pTable->m_indp + i, 0, 0, OCI_DEFAULT));
		}
	}
	catch(...)
	{
		if (pTable != NULL)
		{
			delete pTable;
			pTable = NULL;
		}
		m_iConState = 2;//���Ӷ�ʧ
	}
	if (defhp != NULL)
	{
		delete[] defhp;
	}
	return pTable;
}

// ִ�д洢����
bool CDBConnection::ExecuteProc(const char* strCommand,int n,...)
{
	if (m_iConState != 0)
	{
		bool bRet = ReOpen();
		if (!bRet)
		{
			return NULL;
		}
	}
	va_list ap;
	va_start(ap,n);//
	OCIStmt *phStmt;       //oracle������������  
	try
	{
		//׼��Sql���
		//m_DbPool.CheckErr(OCIStmtPrepare2 (m_Svchp, &phStmt, m_DbPool.errhp, (const OraText *) strCommand, strlen((char *) strCommand), NULL, 0,	OCI_NTV_SYNTAX, OCI_DEFAULT));
		if (OCIHandleAlloc((dvoid *)m_DbPool.envhp, (dvoid **)&phStmt, OCI_HTYPE_STMT, (size_t)0, (dvoid **)0) != OCI_SUCCESS)
		{
			cout << "Create STMT error !" << endl;
			exit(1);
		}

		OCIHandleAlloc((dvoid *)m_DbPool.envhp, (dvoid **)&m_DbPool.errhp, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0);

		m_DbPool.CheckErr(OCIStmtPrepare(phStmt, m_DbPool.errhp, (text *)strCommand, (ub4)strlen(strCommand), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT));

		for (int i = 0; i < n/2; i++)
		{
			OCIBind  *bndp;
			//ub2 dty = va_arg(ap,ub2);
			ub2 dty = va_arg(ap,int);
			void* pVar = NULL;
			int iSize = 0;
			switch (dty)
			{
			case SQLT_INT:
				pVar = va_arg(ap,void*);
				iSize = sizeof(int);
				break;
			case SQLT_LNG:
			case  SQLT_CHR:
				pVar = va_arg(ap,void*);
				iSize = va_arg(ap,int);
				break;
			case SQLT_DAT:
				pVar = va_arg(ap,void*);
				iSize = 7;
				break;
			case  SQLT_BLOB:
				pVar = va_arg(ap,void*);
				iSize = va_arg(ap,int);
				break;
			}
			m_DbPool.CheckErr(OCIBindByPos(phStmt, &bndp, m_DbPool.errhp, (ub4) 1+i,
				(dvoid *) pVar, (sb4) iSize, dty,
				(dvoid *) 0, (ub2 *) 0,
				(ub2 *) 0, (ub4) 0, (ub4 *) 0, (ub4) OCI_DEFAULT));
		}
		//ִ��Sql
		m_DbPool.CheckErr(OCIStmtExecute(m_Svchp, phStmt, m_DbPool.errhp, 1, 0, NULL, NULL, OCI_COMMIT_ON_SUCCESS));
		//m_DbPool.CheckErr(OCIStmtRelease(phStmt, m_DbPool.errhp, (OraText *) NULL, 0, OCI_DEFAULT));
		//m_DbPool.CheckErr(OCIHandleFree(phStmt, OCI_DEFAULT));
		m_DbPool.CheckErr(OCIHandleFree((dvoid *) phStmt, OCI_HTYPE_STMT));
	}
	catch (...)
	{
		va_end(ap);
		m_iConState = 2;//���Ӷ�ʧ
		return false;
	}
	va_end(ap);
	return true;
}
