#ifndef _CORE_CIRCULAR_LINKED_LIST_INLINE_
#define _CORE_CIRCULAR_LINKED_LIST_INLINE_

template<typename DataT, typename NodeT>
GINLINE GCircularLinkedList<DataT, NodeT>::GCircularLinkedList()
: m_pCursor(GNULL)
{

}

template<typename DataT, typename NodeT>
GINLINE typename GLinkedList<DataT, NodeT>::Node *GCircularLinkedList<DataT, NodeT>::GetNext()
{
	GASSERT(0 != m_nSize);

	if ((GNULL == m_pCursor) || (GNULL == m_pCursor->m_pNext))
		m_pCursor = m_pFirst;
	else
		m_pCursor = m_pCursor->m_pNext;

	return m_pCursor;
}

template<typename DataT, typename NodeT>
GINLINE const typename GLinkedList<DataT, NodeT>::Node *GCircularLinkedList<DataT, NodeT>::GetNext() const
{
	GASSERT(0 != m_nSize);

	if ((GNULL == m_pCursor) || (GNULL == m_pCursor->m_pNext))
		m_pCursor = m_pFirst;
	else
		m_pCursor = m_pCursor->m_pNext;

	return m_pCursor;
}

template<typename DataT, typename NodeT>
GINLINE gsize GCircularLinkedList<DataT, NodeT>::GetCurrentIndex() const
{
	GASSERT(0 != m_nSize);

	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < m_nSize; ++i)
	{
		if (pTmpNode == m_pCursor)
			return i;
		else
			pTmpNode = pTmpNode->m_pNext;
	}
	return 0;
}

template<typename DataT, typename NodeT>
GINLINE typename GLinkedList<DataT, NodeT>::Node *GCircularLinkedList<DataT, NodeT>::GetCurrentNode()
{
	return m_pCursor;
}

template<typename DataT, typename NodeT>
GINLINE const typename GLinkedList<DataT, NodeT>::Node *GCircularLinkedList<DataT, NodeT>::GetCurrentNode() const
{
	return m_pCursor;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GCircularLinkedList<DataT, NodeT>::RemoveAt(gsize pos)
{
	GASSERT(pos < m_nSize);

	NodeT *pTmpNode1 = m_pFirst;
	if (0 == pos)
	{
		m_pFirst = m_pFirst->m_pNext;
		m_pCursor = GNULL;
		delete pTmpNode1;
		pTmpNode1 = GNULL;
		--m_nSize;
		return;
	}

	NodeT *pTmpNode2 = pTmpNode1;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pTmpNode2->m_pNext = pTmpNode1->m_pNext;

	m_pCursor = pTmpNode2;
	delete pTmpNode1;
	pTmpNode1 = GNULL;
	--m_nSize;
	return;
}

#endif // _CORE_CIRCULAR_LINKED_LIST_INLINE_