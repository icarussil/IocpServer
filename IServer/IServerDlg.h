
// IServerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "NetworkController.h"

#define WM_USER_LOG WM_USER+1000 

// CIServerDlg 대화 상자
class CIServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CIServerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ISERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL DestroyWindow();
	afx_msg LRESULT OnMessage(WPARAM wp, LPARAM lp);

public:
	afx_msg void OnBnClickedButtonStartServer();
	afx_msg void OnBnClickedButtonStopServer();
	CListBox m_listLog;

	NetworkController m_nc;

	BOOL m_bStart;
};
