// OicDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "DBConnection.h"

// COicDemoDlg �Ի���
class COicDemoDlg : public CDialog
{
// ����
public:
	COicDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OICDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	OCI_THREAD_INFO m_HrdInsert;
	OCI_THREAD_INFO m_HrdUpdate;
	OCI_THREAD_INFO m_HrdDelete;

	// ���ɵ���Ϣӳ�亯��
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
