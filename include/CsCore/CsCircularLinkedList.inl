#ifndef _CORE_CIRCULAR_LINKED_LIST_INLINE_
#define _CORE_CIRCULAR_LINKED_LIST_INLINE_

template<typename DataT>
inline CsCircularLinkedList<DataT>::CsCircularLinkedList()
: m_pCursor(NULL)
{
}

template<typename DataT>
inline DataT& CsCircularLinkedList<DataT>::GetNext()
{
	CS_ASSERT(0 != m_nLength);

	if ((NULL == m_pCursor) || (NULL == m_pCursor->m_pNext))
		m_pCursor = m_pHead;
	else
		m_pCursor = m_pCursor->m_pNext;

	return m_pCursor->m_tData;
}

template<typename DataT>
inline cs_size_t CsCircularLinkedList<DataT>::GetCurrentIndex() const
{
	CS_ASSERT(0 != m_nLength);

	CsSingleLinkedListNode<DataT> *pTmpNode = m_pHead;
	for (cs_size_t i = 0; i < m_nLength; ++i)
	{
		if (pTmpNode == m_pCursor)
			return i;
		else
			pTmpNode = pTmpNode->m_pNext;
	}
	return 0;
}

template<typename DataT>
inline cs_void CsCircularLinkedList<DataT>::RemoveAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nLength);

	CsSingleLinkedListNode<DataT> *pTmpNode1 = m_pHead;
	if (0 == pos)
	{
		m_pHead = m_pHead->m_pNext;
		m_pCursor = NULL;
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

	m_pCursor = pTmpNode2;
	delete pTmpNode1;
	pTmpNode1 = NULL;
	--m_nLength;
	return;
}

#endif // _CORE_CIRCULAR_LINKED_LIST_INLINE_