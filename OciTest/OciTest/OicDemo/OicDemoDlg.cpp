// OicDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OicDemo.h"
#include "OicDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COicDemoDlg 对话框




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


// COicDemoDlg 消息处理程序

BOOL COicDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COicDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
		pwnd->SetWindowText("停止（Insert）");
		dbPool.BeginOciThread(InsertThreadProc,&m_HrdInsert);
	} else {
		pwnd->SetWindowText("开始（Insert）");
		m_HrdInsert.iStatus = THREAD_STATUS_QUITING;//*--*/通知退出
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
		pwnd->SetWindowText("停止（Update）");
		dbPool.BeginOciThread(UpdateThreadProc,&m_HrdUpdate);
	} else {
		pwnd->SetWindowText("开始（Update）");
		m_HrdUpdate.iStatus = THREAD_STATUS_QUITING;//*--*/通知退出
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
		pwnd->SetWindowText("停止（Delete）");
		dbPool.BeginOciThread(DeleteThreadProc,&m_HrdDelete);
	} else {
		pwnd->SetWindowText("开始（Delete）");
		m_HrdDelete.iStatus = THREAD_STATUS_QUITING;//*--*/通知退出
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
		pwnd->SetWindowText("停止（Select）");
		SetTimer(100,1000,NULL);
	} else {
		pwnd->SetWindowText("开始（Select）");
		KillTimer(100);
	}
	bFlag = !bFlag;
}
//插入数据的线程
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

//更新数据的线程
void COicDemoDlg::UpdateThreadProc(void* arg)
{
	OCI_THREAD_INFO* pThrdInfo = (OCI_THREAD_INFO*)arg;
	char strSql[SQL_LEN];
	CDbPool& dbPool = CDbPool::GetInstance();
	CDBConnection* m_pDb = new CDBConnection(dbPool);
	m_pDb->Logon();
	while (pThrdInfo->iStatus == THREAD_STATUS_RUN)
	{
		sprintf_s(strSql,SQL_LEN,"update odn_pda set pda_name='更新了' where pda_id = (select max(pda_id) from odn_pda)");
		m_pDb->ExecuteNonQuery(strSql);
		Sleep(1000);
	}
	m_pDb->Logoff();
	delete m_pDb;
	pThrdInfo->iStatus = THREAD_STATUS_QUIT;
}
//删除数据线程

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
