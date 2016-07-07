#pragma once

#define MAX_BUFFER 4096

typedef struct tagPerloContext
{
	WSAOVERLAPPED overlapped;
	WSABUF wsaBuf;
	char Buffer[MAX_BUFFER];
} PerIoContext, *PPerIoContext;

typedef struct tagPerSocketContext
{
	SOCKET socket;
	PPerIoContext recvContext;
	PPerIoContext sendContext;
} PerSocketContext, *PPerSocketContext;
