#pragma once

#include "IocpHandler.h"
#include "def.h"
#include "MemPooler.h"
#include "Statistcs.h"
#define  MAX_USER 3000

#include <iostream>
#include <fstream>

#define SEND_EXTRA -1
#define SEND_START 7777
#define SEND_MIDDLE 8888
#define SEND_END 9999

#define SIZE_HEADER					136							// Ÿ��(4byte) + ����ũ��(4btye) + ���� �̸� (128byte)
#define SIZE_HEADER_DATA			MAX_BUFFER - SIZE_HEADER			// 4096

struct  stProtocol
{
	int nType;					// 4 byte	== Ÿ�� 
	int nFileSize;				// 4 byte   == ���� ũ�� 
	char szFileName[128];		// 256 byte == ���� �̸�

	stProtocol()
	{
		nType = -2;
	}
};


using namespace std;

class NetworkController : public IIocpProcessThread
{
public:
	NetworkController(void);
	~NetworkController(void);

public:
	// �ʱ�ȭ ó��
	BOOL Init(const int Port=15000);

	// RECV��û
	BOOL RecvPost(PPerSocketContext pPerSocketCtx);

	// Send ��û
	BOOL SendPost(PPerSocketContext pPerSocketCtx);

	// Accept �۾� ó��
	void AcceptProcess(void);

	// ���� �ߴ�
	void ServerClose(void);

public:
	void SetDlg(CDialog *pDlg);

private:
	// Per Io Context �޸� �Ҵ�
	PPerIoContext AllocPerIoContextForRecv(void);
	PPerIoContext AllocPerIoContextForSend(void);

	// Per Socket Context �޸� �Ҵ�
	PPerSocketContext AllocPerSocketContext(SOCKET clientSocket);

	// �Ϸ� ��Ŷ ó�� �Լ�
	void ProcessingThread(void);

	// PerIoContext �޸� ����
	void DeallocPerIoContextForSend(PPerIoContext pPerIoCtx);
	void DeallocPerIoContextForRecv(PPerIoContext pPerIoCtx);

	// PerSocketContext �޸� ����
	void DeallocPerSocketContext(PPerSocketContext pPerSocketCtx);

	// ���ú� �̺�Ʈ ó�� �ڵ鷯 �Լ�
	BOOL RecvCompleteEvent(PPerSocketContext pPerSocketCtx, DWORD dwBytesTransferred);

	// Send �Ϸ� ��Ŷ ó�� �ڵ鷯 �Լ�
	BOOL SendCompleteEvent(PPerSocketContext pPerSocketCtx, DWORD dwBytesTransferred);

	// Recv, Send �Ϸ� ���� ���� ó�� �ڵ鷯 �Լ�
	BOOL OtherCompleteEvent(PPerSocketContext pPerSocketCtx, DWORD dwBytesTransferred);

	// Ŭ���̾�Ʈ ���� ���ؽ�Ʈ �����ϰ� ���� ����
	void CloseClient(PPerSocketContext pPerSocketCtx,bool bGraceful);

	int GetProtocolType(PPerSocketContext pPerSocketCtx, stProtocol& type);
	CString GetFileName(CString strFile);
		
private:
	// ���� ����
	SOCKET m_listenSocket;
	// IOCP �ڵ鷯 
	IocpHandler m_IocpHandler;

#ifdef STATISTICS
	// ��� ǥ�ø� ���� Ŭ���� �ν��Ͻ�
	Statistics m_state;
#endif
	
	// ����ȭ�� ���� ����( �̷��� �ϴ°� ���� �ٸ� ����� �� ���� �� ����)
	CRITICAL_SECTION m_cs;

	MemPooler<PerSocketContext> * m_pPerSocketCtxMemPool;
	MemPooler<PerIoContext> * m_pRecvMemPool;
	MemPooler<PerIoContext> * m_pSendMemPool;
	
	CDialog *m_pDlg;
		
	CFile m_fileWrite;
	
	int m_RecvCount;
	int m_nReceiveDataSize;
	int m_nFileSize;
};

