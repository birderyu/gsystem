#ifndef _CORE_SINGLE_LINKED_LIST_INLINE_
#define _CORE_SINGLE_LINKED_LIST_INLINE_

template<typename DataT>
inline CsSingleLinkedList<DataT>::CsSingleLinkedList()
: m_nLength(0), m_pHead(NULL)
{
}

template<typename DataT>
inline CsSingleLinkedList<DataT>::CsSingleLinkedList(const DataT &data)
: m_nLength(0), m_pHead(NULL)
{
	AddHead(data);
}

template<typename DataT>
inline CsSingleLinkedList<DataT>::CsSingleLinkedList(const CsSingleLinkedList<DataT> &other)
: m_nLength(0), m_pHead(NULL)
{
	if (other.m_nLength > 0)
	{
		for (cs_size_t i = 0; i < other.m_nLength; i++)
		{
			AddTail(other.GetAt(i));
		}
	}
}

template<typename DataT>
inline CsSingleLinkedList<DataT>& CsSingleLinkedList<DataT>::operator=(const CsSingleLinkedList<DataT>& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (m_nLength > 0)
	{
		RemoveAll();
	}

	if (other.m_nLength > 0)
	{
		for (cs_size_t i = 0; i < other.m_nLength; i++)
		{
			AddTail(other.GetAt(i));
		}
	}
	return *this;
}

template<typename DataT>
inline CsSingleLinkedList<DataT>::~CsSingleLinkedList()
{
	RemoveAll();
}

template<typename DataT>
inline cs_void CsSingleLinkedList<DataT>::Invert()
{
	if (m_nLength <= 1) return;

	CsSingleLinkedListNode<DataT> *curNod = m_pHead, *preNod = NULL, *nextNod = m_pHead;
	for (cs_size_t i = 1; i <= m_nLength; i++)
	{
		nextNod = curNod->m_pNext;
		curNod->m_pNext = preNod;
		preNod = curNod;
		curNod = nextNod;
	}
	m_pHead = preNod;
	return;
}

template<typename DataT>
inline cs_bool CsSingleLinkedList<DataT>::IsEmpty() const
{
	return 0 == m_nLength;
}

template<typename DataT>
inline cs_bool CsSingleLinkedList<DataT>::AddHead(const DataT &data)
{
	return InsertBefore(0, data);
}

template<typename DataT>
inline cs_bool CsSingleLinkedList<DataT>::AddTail(const DataT &data)
{
	return InsertAfter(m_nLength - 1, data);
}

template<typename DataT>
inline cs_bool CsSingleLinkedList<DataT>::InsertBefore(cs_size_t pos, const DataT &data)
{
	CsSingleLinkedListNode<DataT> *pNewNode = new CsSingleLinkedListNode<DataT>(data);
	if (!pNewNode)
	{
		return false;
	}

	// 列表为空，则设置头节点为新建的节点
	if (NULL == m_pHead)
	{
		m_pHead = pNewNode;
		++m_nLength;
		return true;
	}

	CS_ASSERT(pos < m_nLength);
	if (0 == pos)
	{
		pNewNode->m_pNext = m_pHead;
		m_pHead = pNewNode;
		++m_nLength;
		return true;
	}

	CsSingleLinkedListNode<DataT> *pTmpNode1 = m_pHead;
	CsSingleLinkedListNode<DataT> *pTmpNode2 = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pNewNode->m_pNext = pTmpNode1;
	pTmpNode2->m_pNext = pNewNode;

	++m_nLength;
	return true;
}

template<typename DataT>
inline cs_bool CsSingleLinkedList<DataT>::InsertAfter(cs_size_t pos, const DataT &data)
{
	CsSingleLinkedListNode<DataT> *pNewNode = new CsSingleLinkedListNode<DataT>(data);
	if (!pNewNode)
	{
		return false;
	}

	if (NULL == m_pHead)
	{
		m_pHead = pNewNode;
		++m_nLength;
		return true;
	}

	CS_ASSERT(pos < m_nLength);
	CsSingleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pTmpNode->m_pNext = pNewNode;

	++m_nLength;
	return true;
}

template<typename DataT>
inline cs_size_t CsSingleLinkedList<DataT>::Size() const
{
	return m_nLength;
}

template<typename DataT>
inline cs_void CsSingleLinkedList<DataT>::RemoveAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nLength);

	CsSingleLinkedListNode<DataT> *pTmpNode1 = m_pHead;
	if (0 == pos)
	{
		m_pHead = m_pHead->m_pNext;

		delete pTmpNode1;
		pTmpNode1 = NULL;

		--m_nLength;
		return;
	}

	CsSingleLinkedListNode<DataT> *pTmpNode2 = pTmpNode1;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pTmpNode2->m_pNext = pTmpNode1->m_pNext;
	delete pTmpNode1;
	pTmpNode1 = NULL;
	--m_nLength;
}

template<typename DataT>
inline cs_void CsSingleLinkedList<DataT>::RemoveHead()
{
	CS_ASSERT(0 != m_nLength);
	RemoveAt(0);
}

template<typename DataT>
inline cs_void CsSingleLinkedList<DataT>::RemoveTail()
{
	CS_ASSERT(0 != m_nLength);
	RemoveAt(m_nLength - 1);
}

template<typename DataT>
inline cs_void CsSingleLinkedList<DataT>::RemoveAll()
{
	if (m_nLength <= 0)
	{
		return;
	}

	CsSingleLinkedListNode<DataT> *pTmpNode = NULL;
	for (cs_size_t i = 0; i < m_nLength; ++i)
	{
		pTmpNode = m_pHead->m_pNext;
		delete m_pHead;
		m_pHead = pTmpNode;
	}

	m_pHead = NULL;
	m_nLength = 0;
}

template<typename DataT>
inline DataT& CsSingleLinkedList<DataT>::GetTail()
{
	CS_ASSERT(0 != m_nLength);

	CsSingleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < m_nLength - 1; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	return pTmpNode->m_tData;
}

template<typename DataT>
inline DataT CsSingleLinkedList<DataT>::GetTail() const
{
	CS_ASSERT(0 != m_nLength);

	CsSingleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < m_nLength - 1; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	return pTmpNode->m_tData;
}

template<typename DataT>
inline DataT& CsSingleLinkedList<DataT>::GetHead()
{
	CS_ASSERT(0 != m_nLength);
	return m_pHead->m_tData;
}

template<typename DataT>
inline DataT CsSingleLinkedList<DataT>::GetHead() const
{
	CS_ASSERT(0 != m_nLength);
	return m_pHead->m_tData;
}

template<typename DataT>
inline DataT& CsSingleLinkedList<DataT>::GetAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nLength);
	CsSingleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode->m_tData;
}

template<typename DataT>
inline DataT CsSingleLinkedList<DataT>::GetAt(cs_size_t pos) const
{
	CS_ASSERT(pos < m_nLength);
	CsSingleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode->m_tData;
}

template<typename DataT>
inline cs_void CsSingleLinkedList<DataT>::SetAt(cs_size_t pos, const DataT &data)
{
	CS_ASSERT(pos < m_nLength);
	CsSingleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = data;
}

template<typename DataT>
inline cs_size_t CsSingleLinkedList<DataT>::IndexOf(const DataT &data) const
{
	CsSingleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < m_nLength; ++i)
	{
		if (data == pTmpNode->m_tData)
			return i;
		pTmpNode = pTmpNode->m_pNext;
	}
	return NULL_POS;
}

template<typename DataT>
inline cs_size_t CsSingleLinkedList<DataT>::FindCircle() const
{
	if (0 == m_nLength)
	{
		return NULL_POS;
	}

	CsSingleLinkedListNode<DataT>* p1 = m_pHead; // p1，步长为1
	CsSingleLinkedListNode<DataT>* p2 = m_pHead; // p2，步长为2

	/*判断链表是否有环，当p1=p2时说明链表有环，程序跳出循环。如果p2一直走到链表尽头则说明没有环。*/
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

	/*求出环的起点节点，并将其返回*/
	p2 = m_pHead;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}

	p2 = m_pHead;
	cs_size_t i = 0;
	for (i = 0; i < m_nLength; i++)
	{
		if (p1 == p2) break;
		p2 = p2->m_pNext;
	}
	return i;
}

template<typename DataT>
inline cs_size_t CsSingleLinkedList<DataT>::FindCross(const CsSingleLinkedList &list)
{
	if (0 == m_nLength || 0 == list.m_nLength)
	{
		return NULL_POS;
	}

	if (FindCircle() > 0
		|| list.FindCircle() > 0)
	{
		return NULL_POS;
	}

	/*将第二个链表接在第一个链表后面*/
	CsSingleLinkedListNode<DataT>* pTail = m_pHead;
	for (int i = 1; i < m_nLength; i++)
	{
		pTail = pTail->m_pNext;
	}

	pTail->m_pNext = list.m_pHead;
	m_nLength += list.m_nLength;
	cs_int i = FindCircle();

	pTail->m_pNext = NULL;
	m_nLength -= list.m_nLength;
	return i;
}

template<typename DataT>
DataT &CsSingleLinkedList<DataT>::operator[](cs_size_t id)
{
	return GetAt(id);
}

template<typename DataT>
DataT CsSingleLinkedList<DataT>::operator[](cs_size_t id) const
{
	return GetAt(id);
}

#endif // _CORE_SINGLE_LINKED_LIST_INLINE_