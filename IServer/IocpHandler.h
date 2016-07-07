#pragma once

#include "IocpProcessThreadDef.h"

class IocpHandler
{
public:
	IocpHandler(void);
	~IocpHandler(void);

public:
	// ICOP 생성 및 초기화
	BOOL Create(int nMaxNumberOfConcurrentThreads=0, int* pnOutErrCode=NULL);

	// 소켓과 IOCP 연결
	BOOL Asscoicate(SOCKET hSocket, ULONG_PTR CompletionKey, int* pnOutErrCode=NULL);

	// 파일 핸들과 IOCP와 연결
	BOOL Asscoicate(HANDLE hDevice, ULONG_PTR CompletionKey, int* pnOutErrCod=NULL);

	// IO Completion Queue에 한 완료 레코드를 사용자 정의로 추가
	BOOL PostCompletionStatus(ULONG_PTR CompletionKey, DWORD dwBytesTransferred=0, OVERLAPPED* pOverlapped=NULL, int* pnOutErrCod=NULL );

	// IO Completion Quwue에서 완료 패킷을 얻어온다.
	BOOL GetCompletionStatus(ULONG_PTR* pOutCompletionkey, LPDWORD pdwOutBytesTransferred, LPOVERLAPPED* pOutOverlapped, int* pnOutErrCode=NULL, DWORD dwWaitingTime=INFINITE);

	// IOCP Worker Thread 풀을 만듬
	BOOL CreateThreadPool(IIocpProcessThread* piProcessThread, int nNumOfPooledThread=0);

public:
	void CloseAllThreads(void);
	
private:
	// IOCP 커널 객체에 대한 핸들
	HANDLE m_hIOCP;
	
	// 만들어진 Worker Thread 수
	int m_CreatedThreadNumber;

private:
	// IOCP 워커 쓰레드 시작 포인트로서만의 역활?
	static DWORD __stdcall IocpWorkerThreadStartingPoint(PVOID pvParam);
};

