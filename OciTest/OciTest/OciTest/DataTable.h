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
	void** m_pData;	//������ָ��
	int*  m_pDataType;	//�������ͱ�
	int*  m_pSize;	//���ֶγ���

	sb2* m_indp;
	ub4 m_iField;	//����
	int m_iRows;	//����
	OCIStmt *m_phStmt;       //oracle������������
	OCIError   *m_phErr;        //oracle�Ĵ����������Ի�ȡ������Ϣ  
};
#endif	//#ifndef __CDATATABLE_H__