
// IServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CIServerApp:
// �� Ŭ������ ������ ���ؼ��� IServer.cpp�� �����Ͻʽÿ�.
//

class CIServerApp : public CWinApp
{
public:
	CIServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CIServerApp theApp;