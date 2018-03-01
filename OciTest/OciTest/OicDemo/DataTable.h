#ifndef __CDATATABLE_H__
#define __CDATATABLE_H__
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include "oci.h"
#include <iostream>
#define		SQL_LEN					1024

using namespace std;

class CDataTable {
	friend class CDBConnection;
public:
	CDataTable(int iFields,OCIStmt *phStmt,OCIError *phErr);
	~CDataTable(void);
	int GetFields();
	bool Next();
	int GetInt(int iField,int iDefault=0);
	double GetFloat(int iField,double dDefault=0);
	char* GetDate(int iField,char* pDate);
	char* GetString(int iField,char* pDate);
protected:
	void* InitField(int iField,int iLen,int iType);
	void** m_pData;	//数据区指针
	int*  m_pDataType;	//数据类型表
	int*  m_pSize;	//各字段长度

	sb2* m_indp;
	ub4 m_iField;	//列数
	int m_iRows;	//行数
	OCIStmt *m_phStmt;       //oracle的语句描述句柄
	OCIError   *m_phErr;        //oracle的错误句柄，可以获取错误信息  
};
#endif	//#ifndef __CDATATABLE_H__