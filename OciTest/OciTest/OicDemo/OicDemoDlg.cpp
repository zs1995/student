// OicDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OicDemo.h"
#include "OicDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COicDemoDlg �Ի���




COicDemoDlg::COicDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COicDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_HrdInsert.thrid = NULL;
	m_HrdUpdate.thrid = NULL;
	m_HrdDelete.thrid = NULL;
}

void COicDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}

BEGIN_MESSAGE_MAP(COicDemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &COicDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &COicDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &COicDemoDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &COicDemoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON4, &COicDemoDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// COicDemoDlg ��Ϣ�������

BOOL COicDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COicDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COicDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COicDemoDlg::OnBnClickedButton1()
{
	static bool bFlag = true;
	CDbPool& dbPool = CDbPool::GetInstance();
	CWnd* pwnd = GetDlgItem(IDC_BUTTON1);
	if (bFlag)
	{
		pwnd->SetWindowText("ֹͣ��Insert��");
		dbPool.BeginOciThread(InsertThreadProc,&m_HrdInsert);
	} else {
		pwnd->SetWindowText("��ʼ��Insert��");
		m_HrdInsert.iStatus = THREAD_STATUS_QUITING;//*--*/֪ͨ�˳�
		while (m_HrdInsert.iStatus == THREAD_STATUS_QUIT)
		{
			dbPool.EndOciThread(&m_HrdInsert);
		}
		m_HrdInsert.thrid = NULL;
	}
	bFlag = !bFlag;
}

void COicDemoDlg::OnBnClickedButton3()
{
	static bool bFlag = true;
	CDbPool& dbPool = CDbPool::GetInstance();
	CWnd* pwnd = GetDlgItem(IDC_BUTTON3);
	if (bFlag)
	{
		pwnd->SetWindowText("ֹͣ��Update��");
		dbPool.BeginOciThread(UpdateThreadProc,&m_HrdUpdate);
	} else {
		pwnd->SetWindowText("��ʼ��Update��");
		m_HrdUpdate.iStatus = THREAD_STATUS_QUITING;//*--*/֪ͨ�˳�
		while (m_HrdUpdate.iStatus == THREAD_STATUS_QUIT)
		{
			dbPool.EndOciThread(&m_HrdUpdate);
		}
		m_HrdUpdate.thrid = NULL;
	}
	bFlag = !bFlag;
}

void COicDemoDlg::OnBnClickedButton4()
{
	static bool bFlag = true;
	CDbPool& dbPool = CDbPool::GetInstance();
	CWnd* pwnd = GetDlgItem(IDC_BUTTON4);
	if (bFlag)
	{
		pwnd->SetWindowText("ֹͣ��Delete��");
		dbPool.BeginOciThread(DeleteThreadProc,&m_HrdDelete);
	} else {
		pwnd->SetWindowText("��ʼ��Delete��");
		m_HrdDelete.iStatus = THREAD_STATUS_QUITING;//*--*/֪ͨ�˳�
		while (m_HrdDelete.iStatus == THREAD_STATUS_QUIT)
		{
			dbPool.EndOciThread(&m_HrdDelete);
		}
		m_HrdDelete.thrid = NULL;
	}
	bFlag = !bFlag;
}

void COicDemoDlg::OnBnClickedButton2()
{

	static bool bFlag = true;
	CDbPool& dbPool = CDbPool::GetInstance();
	CWnd* pwnd = GetDlgItem(IDC_BUTTON2);
	if (bFlag)
	{
		pwnd->SetWindowText("ֹͣ��Select��");
		SetTimer(100,1000,NULL);
	} else {
		pwnd->SetWindowText("��ʼ��Select��");
		KillTimer(100);
	}
	bFlag = !bFlag;
}
//�������ݵ��߳�
void COicDemoDlg::InsertThreadProc(void* arg)
{
	OCI_THREAD_INFO* pThrdInfo = (OCI_THREAD_INFO*)arg;
	char strSql[SQL_LEN];
	CDbPool& dbPool = CDbPool::GetInstance();
	CDBConnection* m_pDb = new CDBConnection(dbPool);
	m_pDb->Logon();
	while (pThrdInfo->iStatus == THREAD_STATUS_RUN)
	{
		sprintf_s(strSql,SQL_LEN,"insert into odn_pda(pda_id,pda_name,bureau_id,user_name,telephone,state,create_time,assets_gs) values(odn_pda_id_sequ.nextval,'kjkj',1,'bbbb','1325646',1,sysdate,2)");
		m_pDb->ExecuteNonQuery(strSql);
		Sleep(1000);
	}
	m_pDb->Logoff();
	delete m_pDb;
	pThrdInfo->iStatus = THREAD_STATUS_QUIT;
}

//�������ݵ��߳�
void COicDemoDlg::UpdateThreadProc(void* arg)
{
	OCI_THREAD_INFO* pThrdInfo = (OCI_THREAD_INFO*)arg;
	char strSql[SQL_LEN];
	CDbPool& dbPool = CDbPool::GetInstance();
	CDBConnection* m_pDb = new CDBConnection(dbPool);
	m_pDb->Logon();
	while (pThrdInfo->iStatus == THREAD_STATUS_RUN)
	{
		sprintf_s(strSql,SQL_LEN,"update odn_pda set pda_name='������' where pda_id = (select max(pda_id) from odn_pda)");
		m_pDb->ExecuteNonQuery(strSql);
		Sleep(1000);
	}
	m_pDb->Logoff();
	delete m_pDb;
	pThrdInfo->iStatus = THREAD_STATUS_QUIT;
}
//ɾ�������߳�

void COicDemoDlg::DeleteThreadProc(void* arg)
{
	OCI_THREAD_INFO* pThrdInfo = (OCI_THREAD_INFO*)arg;
	char strSql[SQL_LEN];
	CDbPool& dbPool = CDbPool::GetInstance();
	CDBConnection* m_pDb = new CDBConnection(dbPool);
	m_pDb->Logon();
	while (pThrdInfo->iStatus == THREAD_STATUS_RUN)
	{
		sprintf_s(strSql,SQL_LEN,"delete odn_pda where pda_id = (select max(pda_id) from odn_pda)");
		m_pDb->ExecuteNonQuery(strSql);
		Sleep(1000);
	}
	m_pDb->Logoff();
	delete m_pDb;
	pThrdInfo->iStatus = THREAD_STATUS_QUIT;
}
void COicDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int oldId = 0;
	if (nIDEvent == 100)
	{
		CDbPool& dbPool = CDbPool::GetInstance();
		CDBConnection* m_pDb = new CDBConnection(dbPool);
		m_pDb->Logon();
		CDataTable* table = NULL;
		CString str;
		int iId;
		char name[120];
		char strSql[SQL_LEN];
		sprintf_s(strSql,SQL_LEN,"select pda_id,pda_name from odn_pda where pda_id = (select max(pda_id) from odn_pda)");
		table = m_pDb->Execute(strSql);
		if (table != NULL)
		{
			if (table->Next())
			{
				iId = table->GetInt(0);
				if (oldId != iId)
				{
					oldId = iId;
					table->GetString(1,name);
					str.Format("    id=%d   name=%s",iId,name);
					m_List.InsertString(0,str);
				}
			}
			delete table;
		}
		m_pDb->Logoff();
		delete m_pDb;
	}
	CDialog::OnTimer(nIDEvent);
}

void COicDemoDlg::OnBnClickedCancel()
{
	CDbPool& dbPool = CDbPool::GetInstance();
	if (m_HrdInsert.thrid != NULL)
	{
		m_HrdInsert.iStatus = THREAD_STATUS_QUITING;
		while (m_HrdInsert.iStatus != THREAD_STATUS_QUIT)
		{
			Sleep(10);
		}
		dbPool.EndOciThread(&m_HrdInsert);
	}
	if (m_HrdUpdate.thrid != NULL)
	{
		m_HrdUpdate.iStatus = THREAD_STATUS_QUITING;
		while (m_HrdUpdate.iStatus != THREAD_STATUS_QUIT)
		{
			Sleep(10);
		}
		dbPool.EndOciThread(&m_HrdUpdate);
	}
	if (m_HrdDelete.thrid != NULL)
	{
		m_HrdDelete.iStatus = THREAD_STATUS_QUITING;
		while (m_HrdDelete.iStatus != THREAD_STATUS_QUIT)
		{
			Sleep(10);
		}
		dbPool.EndOciThread(&m_HrdDelete);
	}
	KillTimer(100);
	OnCancel();
}
