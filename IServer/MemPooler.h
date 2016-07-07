#pragma once
#include <assert.h>

template<typename T>
class MemPooler
{
public:
	// 생성자
	MemPooler(int nNumberOfBlock) : 
		m_nNumberOfBlock(nNumberOfBlock),
		m_pFreList(NULL),
		m_pMemBlock(NULL),
		m_nAllocCount(0)
	{
		assert (nNumberOfBlock>0);
		m_nListBlockSize = sizeof(BlockNode) * sizeof(T);

		Create();
	}

	// 소멸자
	~MemPooler()
	{
		Destory();
	}

	// 메모리 할당
	T* Alloc()
	{
		BlockNode* pNode = NULL;
		T* pRet = NULL;

		EnterCriticalSection(&m_cs);

		pNode = m_pFreList;
		if ( NULL != pNode )
		{
			m_pFreList=m_pFreList->pNext;
			m_nAllocCount++;
			pRet = reinterpret_cast<T*>(pNode+1);
		}
		LeaveCriticalSection(&m_cs);

		return pRet;
	}

	BOOL Free(T* freeBlock)
	{
		BlockNode* pNode = NULL;
		BOOL bRet = FALSE;

		EnterCriticalSection(&m_cs);
		
		pNode = (reinterpret_cast<BlockNode*>(freeBlock))-1;
		if ( m_nAllocCount > 0 )
		{
			pNode->pNext = m_pFreList;
			m_pFreList = pNode;
			m_nAllocCount--;
			bRet = TRUE;
		}

		LeaveCriticalSection(&m_cs);

		return bRet;
	}

	int GetCount()
	{
		return m_nAllocCount;
	}

protected:
	void Create()
	{
		const int AllocationSize = (m_nListBlockSize) * m_nNumberOfBlock;
		m_pMemBlock = VirtualAlloc(NULL, AllocationSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		assert(m_pMemBlock);

		BlockNode* pNode = reinterpret_cast<BlockNode*>(m_pMemBlock);

		pNode = reinterpret_cast<BlockNode*>((reinterpret_cast<DWORD>(pNode))+(m_nNumberOfBlock-1) * (m_nListBlockSize) );
		for ( int i = m_nNumberOfBlock-1; i>=0; i-- )
		{
			pNode->pNext = m_pFreList;
			m_pFreList = pNode;
			pNode = reinterpret_cast<BlockNode*>((reinterpret_cast<DWORD>(pNode))-m_nListBlockSize);
		}

		InitializeCriticalSectionAndSpinCount(&m_cs, 4000);
	}

	void Destory()
	{
		if(m_pMemBlock)
		{
			VirtualFree(m_pMemBlock, 0, MEM_RELEASE);
		}

		DeleteCriticalSection(&m_cs);
	}
	
	///////////////////////////////////////////
	// 링크드 리스트 처럼 관리를 위한 노드 타입
	struct BlockNode
	{
		BlockNode* pNext;
		BlockNode()
		{
			pNext=NULL;
		}
	};
	//////////////////////////////////////////


protected:
	BlockNode* m_pFreList;
	void * m_pMemBlock;

	int m_nNumberOfBlock;
	int m_nListBlockSize;
	int m_nAllocCount;

	CRITICAL_SECTION m_cs;
};
