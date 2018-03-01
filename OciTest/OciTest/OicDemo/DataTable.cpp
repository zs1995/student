#include "stdafx.h"
#include "DataTable.h"


int GetStringLen(ub1* str,int iLen)
{
	do 
	{
	} while (str[--iLen] == ' ');
	return iLen+1;
}

CDataTable::CDataTable(int iFields,OCIStmt *phStmt,OCIError *phErr)
{
	m_pData = new void*[iFields];
	m_pDataType = new int[iFields];
	m_pSize = new int[iFields];
	for (int i = 0; i < iFields; i++)
	{
		m_pData[i] = NULL;
		m_pDataType[i] = 0;
		m_pSize[i] = 0;
	}
	m_phStmt = phStmt;
	m_phErr = phErr;
	m_iField = iFields;
	m_indp = new sb2[iFields];
}
CDataTable::~CDataTable ()
{
	for (int i = 0; i < (int)m_iField; i++)
	{
		if (m_pData[i] != NULL)
		{
			delete[] m_pData[i];
		}
	}
	delete[] m_pData;
	delete[] m_pDataType;
	delete[] m_pSize;
	delete[] m_indp;
	OCIStmtRelease(m_phStmt, m_phErr, (OraText *) NULL, 0, OCI_DEFAULT);
}

void* CDataTable::InitField(int iField,int iLen,int iType)
{
	char* pField = new char[iLen];
	memset(pField,0,iLen);
	m_pData[iField] = pField;
	m_pDataType[iField] = iType;
	m_pSize[iField] = iLen;
	return (void*)pField;
};
bool CDataTable::Next()
{
	sword status;
	status = OCIStmtFetch(m_phStmt, m_phErr, 1, OCI_FETCH_NEXT, OCI_DEFAULT);	//读取时间戳时会报异常
	if (OCI_SUCCESS != status)
	{
		return false;
	}
	return true;
}
//返回列数
int CDataTable::GetFields()
{
	return m_iField;
}
//获取int型字段值
int CDataTable::GetInt(int iField,int iDefault)
{
	int iRet;
	if (SQLT_NUM == m_pDataType[iField])
	{
		if (m_pData[iField] != NULL && (m_indp[iField] != -1))
		{
			iRet = atoi((char*)(m_pData[iField]));
		} else {
			iRet = iDefault;
		}
	} else {
		if (m_pData[iField] != NULL && (m_indp[iField] != -1))
		{
			iRet = *(int*)(m_pData[iField]);
		} else {
			iRet = iDefault;
		}
	}
	return iRet;
}
//获取float型字段值
double CDataTable::GetFloat(int iField,double dDefault)
{
	double dRet;
	if (SQLT_NUM == m_pDataType[iField])
	{
		if (m_pData[iField] != NULL && (m_indp[iField] != -1))
		{
			dRet = atof((char*)(m_pData[iField]));
		} else {
			dRet = dDefault;
		}
	} else {
		if (m_pData[iField] != NULL && (m_indp[iField] != -1))
		{
			dRet = *(double*)(m_pData[iField]);
		} else {
			dRet = dDefault;
		}
	}
	return dRet;
}

//获取char型字段值
char* CDataTable::GetString(int iField,char* pDes)
{
	memset(pDes,0,m_pSize[iField]);
	int iLen = GetStringLen((ub1*)(m_pData[iField]),m_pSize[iField]);
	if (iLen > 0)
	{
		if (m_indp[iField]!=-1)
		{
			memcpy(pDes,m_pData[iField],m_pSize[iField]);
			*((ub1*)pDes + iLen) = 0;
		}
	}
	return pDes;
}
//获取Date型字段值,返回字符串
char* CDataTable::GetDate(int iField,char* pDate)
{
	ub1* p = (ub1*)m_pData[iField];
	int iCentury = (int)p[0]-100;
	int iYear = (int)p[1]-100;
	int iMonth = (int)p[2];
	int iDate = (int)p[3];
	int iHour = (int)p[4]-1;
	int iMinute = (int)p[5]-1;
	int iSecond = (int)p[6]-1;
	if (iCentury < 0)	//公元前
	{
		iCentury = -iCentury;
		iYear = -iYear;
		sprintf_s(pDate,32,"BCE %02d%02d-%02d-%02d %02d:%02d:%02d",iCentury,iYear,iMonth,iDate,iHour,iMinute,iSecond);
	} else {
		sprintf_s(pDate,32,"%02d%02d-%02d-%02d %02d:%02d:%02d",iCentury,iYear,iMonth,iDate,iHour,iMinute,iSecond);
	}
	return pDate;
}
