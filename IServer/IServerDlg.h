
// IServerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "NetworkController.h"

// CIServerDlg ��ȭ ����
class CIServerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CIServerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ISERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStartServer();
	afx_msg void OnBnClickedButtonStopServer();
	CListBox m_listLog;

	NetworkController m_nc;
};
