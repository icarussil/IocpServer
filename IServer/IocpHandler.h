#pragma once

#include "IocpProcessThreadDef.h"

class IocpHandler
{
public:
	IocpHandler(void);
	~IocpHandler(void);

public:
	// ICOP ���� �� �ʱ�ȭ
	BOOL Create(int nMaxNumberOfConcurrentThreads=0, int* pnOutErrCode=NULL);

	// ���ϰ� IOCP ����
	BOOL Asscoicate(SOCKET hSocket, ULONG_PTR CompletionKey, int* pnOutErrCode=NULL);

	// ���� �ڵ�� IOCP�� ����
	BOOL Asscoicate(HANDLE hDevice, ULONG_PTR CompletionKey, int* pnOutErrCod=NULL);

	// IO Completion Queue�� �� �Ϸ� ���ڵ带 ����� ���Ƿ� �߰�
	BOOL PostCompletionStatus(ULONG_PTR CompletionKey, DWORD dwBytesTransferred=0, OVERLAPPED* pOverlapped=NULL, int* pnOutErrCod=NULL );

	// IO Completion Quwue���� �Ϸ� ��Ŷ�� ���´�.
	BOOL GetCompletionStatus(ULONG_PTR* pOutCompletionkey, LPDWORD pdwOutBytesTransferred, LPOVERLAPPED* pOutOverlapped, int* pnOutErrCode=NULL, DWORD dwWaitingTime=INFINITE);

	// IOCP Worker Thread Ǯ�� ����
	BOOL CreateThreadPool(IIocpProcessThread* piProcessThread, int nNumOfPooledThread=0);

public:
	void CloseAllThreads(void);
	
private:
	// IOCP Ŀ�� ��ü�� ���� �ڵ�
	HANDLE m_hIOCP;
	
	// ������� Worker Thread ��
	int m_CreatedThreadNumber;

private:
	// IOCP ��Ŀ ������ ���� ����Ʈ�μ����� ��Ȱ?
	static DWORD __stdcall IocpWorkerThreadStartingPoint(PVOID pvParam);
};

