#ifndef _CORE_DOUBLE_LINKED_LIST_INLINE_
#define _CORE_DOUBLE_LINKED_LIST_INLINE_

template<typename DataT>
inline CsDoubleLinkedList<DataT>::CsDoubleLinkedList()
: m_nSize(0), m_pHead(NULL), m_pTail(NULL)
{
}

template<typename DataT>
inline CsDoubleLinkedList<DataT>::CsDoubleLinkedList(const DataT &data)
: m_nSize(0), m_pHead(NULL), m_pTail(NULL)
{
	AddHead(data);
}

template<typename DataT>
inline CsDoubleLinkedList<DataT>::CsDoubleLinkedList(const CsDoubleLinkedList<DataT> &other)
: m_nSize(0), m_pHead(NULL), m_pTail(NULL)
{
	if (other.m_nSize > 0)
	{
		for (cs_size_t i = 0; i < other.m_nSize; i++)
		{
			AddTail(other.GetAt(i));
		}
	}
}

template<typename DataT>
inline CsDoubleLinkedList<DataT>& CsDoubleLinkedList<DataT>::operator=(const CsDoubleLinkedList<DataT> &other)
{
	if (this == &other)
	{
		return *this;
	}

	if (m_nSize > 0)
	{
		RemoveAll();
	}

	if (other.m_nSize > 0)
	{
		for (cs_size_t i = 0; i < other.m_nSize; i++)
		{
			AddTail(other.GetAt(i));
		}
	}
	return *this;
}

template<typename DataT>
inline CsDoubleLinkedList<DataT>::~CsDoubleLinkedList()
{
	RemoveAll();
}

template<typename DataT>
inline cs_void CsDoubleLinkedList<DataT>::Invert()
{
	if (m_nSize <= 1) return;

	CsDoubleLinkedListNode<DataT> *tmpNod = NULL, *curNod = m_pHead, *nextNod = NULL;
	for (cs_size_t i = 1; i <= m_nSize; i++)
	{
		nextNod = curNod->m_pNext;
		tmpNod = curNod->m_pPrevious;
		curNod->m_pPrevious = curNod->m_pNext;
		curNod->m_pNext = tmpNod;
		curNod = nextNod;
	}

	tmpNod = m_pHead;
	m_pHead = m_pTail;
	m_pTail = tmpNod;
	return;
}

template<typename DataT>
inline cs_bool CsDoubleLinkedList<DataT>::InsertBefore(cs_size_t pos, const DataT &data)
{
	CsDoubleLinkedListNode<DataT> *pNewNode = new CsDoubleLinkedListNode<DataT>(data);
	if (!pNewNode)
	{
		return false;
	}

	if (NULL == m_pHead)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
		++m_nSize;
		return true;
	}

	CS_ASSERT(pos < m_nSize);
	if (0 == pos)
	{
		pNewNode->m_pPrevious = NULL;
		pNewNode->m_pNext = m_pHead;
		m_pHead->m_pPrevious = pNewNode;
		m_pHead = pNewNode;
		++m_nSize;
		return true;
	}

	CsDoubleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pNewNode->m_pNext = pTmpNode;
	pNewNode->m_pPrevious = pTmpNode->m_pPrevious;

	pTmpNode->m_pPrevious->m_pNext = pNewNode;
	pTmpNode->m_pPrevious = pNewNode;

	if (NULL == pNewNode->m_pNext)
	{
		m_pTail = pNewNode;
	}

	++m_nSize;
	return true;
}

template<typename DataT>
inline cs_bool CsDoubleLinkedList<DataT>::InsertAfter(cs_size_t pos, const DataT &data)
{
	CsDoubleLinkedListNode<DataT> *pNewNode = new CsDoubleLinkedListNode<DataT>(data);
	if (!pNewNode)
	{
		return false;
	}

	if (NULL == m_pHead)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
		++m_nSize;
		return true;
	}

	CS_ASSERT(pos < m_nSize);

	CsDoubleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	pNewNode->m_pNext = pTmpNode->m_pNext;
	pNewNode->m_pPrevious = pTmpNode;

	pTmpNode->m_pNext = pNewNode;

	if (NULL == pNewNode->m_pNext)
	{
		m_pTail = pNewNode;
	}
	else
	{
		pNewNode->m_pNext->m_pPrevious = pNewNode;
	}

	++m_nSize;
	return true;
}

template<typename DataT>
inline DataT& CsDoubleLinkedList<DataT>::GetAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nSize);
	CsDoubleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode->m_tData;
}

template<typename DataT>
inline DataT CsDoubleLinkedList<DataT>::GetAt(cs_size_t pos) const
{
	CS_ASSERT(pos < m_nSize);
	CsDoubleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode->m_tData;
}

template<typename DataT>
inline cs_bool CsDoubleLinkedList<DataT>::AddHead(const DataT &data)
{
	return InsertBefore(0, data);
}

template<typename DataT>
inline cs_bool CsDoubleLinkedList<DataT>::AddTail(const DataT &data)
{
	return InsertAfter(m_nSize - 1, data);
}

template<typename DataT>
inline cs_bool CsDoubleLinkedList<DataT>::IsEmpty() const
{
	return 0 == m_nSize;
}

template<typename DataT>
inline cs_size_t CsDoubleLinkedList<DataT>::Size() const
{
	return m_nSize;
}

template<typename DataT>
inline DataT& CsDoubleLinkedList<DataT>::GetTail()
{
	CS_ASSERT(0 != m_nSize);
	return m_pTail->m_tData;
}

template<typename DataT>
inline DataT CsDoubleLinkedList<DataT>::GetTail() const
{
	CS_ASSERT(0 != m_nSize);
	return m_pTail->m_tData;
}

template<typename DataT>
inline DataT& CsDoubleLinkedList<DataT>::GetHead()
{
	CS_ASSERT(0 != m_nSize);
	return m_pHead->m_tData;
}

template<typename DataT>
inline DataT CsDoubleLinkedList<DataT>::GetHead() const
{
	CS_ASSERT(0 != m_nSize);
	return m_pHead->m_tData;
}

template<typename DataT>
inline cs_void CsDoubleLinkedList<DataT>::RemoveAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nSize);

	CsDoubleLinkedListNode<DataT> *pTmpNode = m_pHead;
	if (0 == pos)
	{
		// 头指针
		pTmpNode = m_pHead;
		m_pHead = m_pHead->m_pNext;
		if (m_pHead)
		{
			m_pHead->m_pPrevious = NULL;
		}
	}
	else if (pos == m_nSize - 1)
	{
		// 尾指针
		pTmpNode = m_pTail;
		m_pTail = m_pTail->m_pPrevious;
		if (m_pTail)
		{
			m_pTail->m_pNext = NULL;
		}
	}
	else
	{
		pTmpNode = m_pHead;
		for (cs_size_t i = 0; i < pos; ++i)
		{
			pTmpNode = pTmpNode->m_pNext;
		}
		pTmpNode->m_pPrevious->m_pNext = pTmpNode->m_pNext;

		if (pTmpNode->m_pNext)
		{
			pTmpNode->m_pNext->m_pPrevious = pTmpNode->m_pPrevious;
		}
		else
		{
			m_pTail = pTmpNode->m_pPrevious;
		}
	}

	delete pTmpNode;
	pTmpNode = NULL;

	--m_nSize;
	if (0 == m_nSize)
	{
		m_pTail = NULL;
	}

	return;
}

template<typename DataT>
inline cs_void CsDoubleLinkedList<DataT>::RemoveHead()
{
	CS_ASSERT(0 != m_nSize);
	RemoveAt(0);
}

template<typename DataT>
inline cs_void CsDoubleLinkedList<DataT>::RemoveTail()
{
	CS_ASSERT(0 != m_nSize);
	RemoveAt(m_nSize - 1);
}

template<typename DataT>
inline cs_void CsDoubleLinkedList<DataT>::RemoveAll()
{
	if (m_nSize <= 0)
	{
		return;
	}

	CsDoubleLinkedListNode<DataT> *pTmpNode = NULL;
	for (cs_size_t i = 0; i < m_nSize; ++i)
	{
		pTmpNode = m_pHead->m_pNext;
		delete m_pHead;
		m_pHead = pTmpNode;
	}

	m_pHead = NULL;
	m_pTail = NULL;
	m_nSize = 0;
}

template<typename DataT>
inline cs_void CsDoubleLinkedList<DataT>::SetAt(cs_size_t pos, const DataT &data)
{
	CS_ASSERT(pos < m_nSize);
	CsDoubleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = data;
}

template<typename DataT>
inline cs_size_t CsDoubleLinkedList<DataT>::IndexOf(const DataT &data) const
{
	CsDoubleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < m_nSize; ++i)
	{
		if (data == pTmpNode->m_tData)
			return i;
		pTmpNode = pTmpNode->m_pNext;
	}
	return NULL_POS;
}

template<typename DataT>
inline cs_size_t CsDoubleLinkedList<DataT>::FindCircle() const
{
	if (0 == m_nSize)
	{
		return NULL_POS;
	}

	CsDoubleLinkedListNode<DataT>* p1 = m_pHead;
	CsDoubleLinkedListNode<DataT>* p2 = m_pHead;

	// 判断链表是否有环，当p1=p2时说明链表有环，程序跳出循环。如果p2一直走到链表尽头则说明没有环。
	do
	{
		if (p1 != NULL && p2 != NULL && p2->m_pNext != NULL)
		{
			p1 = p1->m_pNext;
			p2 = p2->m_pNext->m_pNext;
		}
		else
		{
			return NULL_POS;
		}
	} while (p1 != p2);

	// 求出环的起点节点，并将其返回
	p2 = m_pHead;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}

	p2 = m_pHead;
	cs_size_t i = 0;
	for (i = 0; i < m_nSize; i++)
	{
		if (p1 == p2) break;
		p2 = p2->m_pNext;
	}
	return i;
}

template<typename DataT>
inline cs_size_t CsDoubleLinkedList<DataT>::FindCross(const CsDoubleLinkedList &list)
{
	if (0 == m_nSize || 0 == list.m_nSize)
	{
		return NULL_POS;
	}

	if (FindCircle() > 0
		|| list.FindCircle() > 0)
	{
		return NULL_POS;
	}

	// 将第二个链表接在第一个链表后面
	CsDoubleLinkedListNode<DataT>* pTail = m_pHead;
	for (int i = 1; i < m_nSize; i++)
	{
		pTail = pTail->m_pNext;
	}

	pTail->m_pNext = list.m_pHead;
	m_nSize += list.m_nSize;

	cs_int i = FindCircle();

	pTail->m_pNext = NULL;
	m_nSize -= list.m_nSize;
	return i;

}

template<typename DataT>
inline DataT &CsDoubleLinkedList<DataT>::operator[](cs_size_t id)
{
	return GetAt(id);
}

template<typename DataT>
inline DataT CsDoubleLinkedList<DataT>::operator[](cs_size_t id) const
{
	return GetAt(id);
}

#endif // _CORE_DOUBLE_LINKED_LIST_INLINE_