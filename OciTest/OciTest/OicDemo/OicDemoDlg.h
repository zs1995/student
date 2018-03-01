// OicDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "DBConnection.h"

// COicDemoDlg 对话框
class COicDemoDlg : public CDialog
{
// 构造
public:
	COicDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OICDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	OCI_THREAD_INFO m_HrdInsert;
	OCI_THREAD_INFO m_HrdUpdate;
	OCI_THREAD_INFO m_HrdDelete;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	static void InsertThreadProc(void* arg);
	static void UpdateThreadProc(void* arg);
	static void SelectThreadProc(void* arg);
	static void DeleteThreadProc(void* arg);
	

	CListBox m_List;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton4();
};
