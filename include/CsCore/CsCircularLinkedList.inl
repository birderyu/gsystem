#ifndef _CORE_CIRCULAR_LINKED_LIST_INLINE_
#define _CORE_CIRCULAR_LINKED_LIST_INLINE_

template<typename DataT, typename NodeT>
inline CsCircularLinkedList<DataT, NodeT>::CsCircularLinkedList()
: m_pCursor(NULL)
{

}

template<typename DataT, typename NodeT>
inline typename CsLinkedList<DataT, NodeT>::Node *CsCircularLinkedList<DataT, NodeT>::GetNext()
{
	CS_ASSERT(0 != m_nSize);

	if ((NULL == m_pCursor) || (NULL == m_pCursor->m_pNext))
		m_pCursor = m_pFirst;
	else
		m_pCursor = m_pCursor->m_pNext;

	return m_pCursor;
}

template<typename DataT, typename NodeT>
inline const typename CsLinkedList<DataT, NodeT>::Node *CsCircularLinkedList<DataT, NodeT>::GetNext() const
{
	CS_ASSERT(0 != m_nSize);

	if ((NULL == m_pCursor) || (NULL == m_pCursor->m_pNext))
		m_pCursor = m_pFirst;
	else
		m_pCursor = m_pCursor->m_pNext;

	return m_pCursor;
}

template<typename DataT, typename NodeT>
inline cs_size_t CsCircularLinkedList<DataT, NodeT>::GetCurrentIndex() const
{
	CS_ASSERT(0 != m_nSize);

	NodeT *pTmpNode = m_pFirst;
	for (cs_size_t i = 0; i < m_nSize; ++i)
	{
		if (pTmpNode == m_pCursor)
			return i;
		else
			pTmpNode = pTmpNode->m_pNext;
	}
	return 0;
}

template<typename DataT, typename NodeT>
inline typename CsLinkedList<DataT, NodeT>::Node *CsCircularLinkedList<DataT, NodeT>::GetCurrentNode()
{
	return m_pCursor;
}

template<typename DataT, typename NodeT>
inline const typename CsLinkedList<DataT, NodeT>::Node *CsCircularLinkedList<DataT, NodeT>::GetCurrentNode() const
{
	return m_pCursor;
}

template<typename DataT, typename NodeT>
inline cs_void CsCircularLinkedList<DataT, NodeT>::RemoveAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nSize);

	NodeT *pTmpNode1 = m_pFirst;
	if (0 == pos)
	{
		m_pFirst = m_pFirst->m_pNext;
		m_pCursor = NULL;
		delete pTmpNode1;
		pTmpNode1 = NULL;
		--m_nSize;
		return;
	}

	NodeT *pTmpNode2 = pTmpNode1;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pTmpNode2->m_pNext = pTmpNode1->m_pNext;

	m_pCursor = pTmpNode2;
	delete pTmpNode1;
	pTmpNode1 = NULL;
	--m_nSize;
	return;
}

#endif // _CORE_CIRCULAR_LINKED_LIST_INLINE_