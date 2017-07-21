#ifndef _CORE_CIRCULAR_LINKED_LIST_INLINE_
#define _CORE_CIRCULAR_LINKED_LIST_INLINE_

namespace gsystem { // gsystem

template<typename T, typename NodeT>
GINLINE GCList<T, NodeT>::GCList()
: m_pCursor(GNULL)
{

}

template<typename T, typename NodeT>
GINLINE typename GLinkedList<T, NodeT>::Node *GCList<T, NodeT>::GetNextNode()
{
	GASSERT(0 != m_nSize);

	if ((GNULL == m_pCursor) || (GNULL == m_pCursor->m_pNext))
		m_pCursor = m_pFirst;
	else
		m_pCursor = m_pCursor->m_pNext;

	return m_pCursor;
}

template<typename T, typename NodeT>
GINLINE const typename GLinkedList<T, NodeT>::Node *GCList<T, NodeT>::GetNextNode() const
{
	GASSERT(0 != m_nSize);

	if ((GNULL == m_pCursor) || (GNULL == m_pCursor->m_pNext))
		m_pCursor = m_pFirst;
	else
		m_pCursor = m_pCursor->m_pNext;

	return m_pCursor;
}

template<typename T, typename NodeT>
GINLINE gsize GCList<T, NodeT>::GetCurrentIndex() const
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

template<typename T, typename NodeT>
GINLINE typename GLinkedList<T, NodeT>::Node *GCList<T, NodeT>::GetCurrentNode()
{
	return m_pCursor;
}

template<typename T, typename NodeT>
GINLINE const typename GLinkedList<T, NodeT>::Node *GCList<T, NodeT>::GetCurrentNode() const
{
	return m_pCursor;
}

template<typename T, typename NodeT>
GINLINE gvoid GCList<T, NodeT>::RemoveAt(gsize pos, T *value)
{
	GASSERT(pos < m_nSize);

	NodeT *pTmpNode1 = m_pFirst;
	if (0 == pos)
	{
		m_pFirst = m_pFirst->m_pNext;
		m_pCursor = GNULL;
		if (value)
		{
			// 将元素移走，而非拷贝
			*value = GMove(pTmpNode1->m_tData);
		}
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
	if (data)
	{
		// 将元素移走，而非拷贝
		*data = GMove(pTmpNode1->m_tData);
	}
	delete pTmpNode1;
	pTmpNode1 = GNULL;
	--m_nSize;
	return;
}

}  // namespace gsystem

#endif // _CORE_CIRCULAR_LINKED_LIST_INLINE_