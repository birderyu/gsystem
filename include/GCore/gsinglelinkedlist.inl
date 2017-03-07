#ifndef _CORE_SINGLE_LINKED_LIST_INLINE_
#define _CORE_SINGLE_LINKED_LIST_INLINE_

template<typename DataT, typename NodeT>
GINLINE GSingleLinkedList<DataT, NodeT>::GSingleLinkedList()
: m_nSize(0), m_pFirst(GNULL)
{
}

template<typename DataT, typename NodeT>
GINLINE GSingleLinkedList<DataT, NodeT>::GSingleLinkedList(const DataT &data)
: m_nSize(0), m_pFirst(GNULL)
{
	AddFirst(data);
}

template<typename DataT, typename NodeT>
GINLINE GSingleLinkedList<DataT, NodeT>::GSingleLinkedList(DataT &&data)
: m_nSize(0), m_pFirst(GNULL)
{
	AddFirst(GForward<DataT>(data));
}

template<typename DataT, typename NodeT>
GINLINE GSingleLinkedList<DataT, NodeT>::GSingleLinkedList(const GSingleLinkedList<DataT, NodeT> &list)
: m_nSize(0), m_pFirst(GNULL)
{
	NodeT *node = list.m_pFirst;
	if (GNULL == node)
	{
		return;
	}

	NodeT *new_node = new NodeT(node->m_tData);
	m_pFirst = new_node;
	m_nSize = 1;
	node = node->m_pNext;
	while (node)
	{
		new_node->m_pNext = new NodeT(node->m_tData);
		new_node = new_node->m_pNext;
		node = node->m_pNext;

		m_nSize++;
	}
}

template<typename DataT, typename NodeT>
GINLINE GSingleLinkedList<DataT, NodeT>::GSingleLinkedList(GSingleLinkedList<DataT, NodeT> &&list)
: m_nSize(list.m_nSize), m_pFirst(list.m_pFirst)
{
	list.m_nSize = 0;
	list.m_pFirst = GNULL;
}

template<typename DataT, typename NodeT>
GINLINE GSingleLinkedList<DataT, NodeT>& GSingleLinkedList<DataT, NodeT>::operator=(const GSingleLinkedList<DataT, NodeT> &list)
{
	if (this == &list)
	{
		return *this;
	}

	if (m_nSize > 0)
	{
		RemoveAll();
	}

	NodeT *node = list.m_pFirst;
	if (GNULL == node)
	{
		return *this;
	}

	NodeT *new_node = new NodeT(node->m_tData);
	m_pFirst = new_node;
	m_nSize = 1;
	node = node->m_pNext;
	while (node)
	{
		new_node->m_pNext = new NodeT(node->m_tData);
		new_node = new_node->m_pNext;
		node = node->m_pNext;

		m_nSize++;
	}
	return *this;
}

template<typename DataT, typename NodeT>
GINLINE GSingleLinkedList<DataT, NodeT>& GSingleLinkedList<DataT, NodeT>::operator=(GSingleLinkedList<DataT, NodeT> &&list)
{
	if (this == &list)
	{
		return *this;
	}

	if (m_nSize > 0)
	{
		RemoveAll();
	}

	m_nSize = list.m_nSize;
	m_pFirst = list.m_pFirst;
	list.m_nSize = 0;
	list.m_pFirst = GNULL;
	return *this;
}

template<typename DataT, typename NodeT>
GINLINE GSingleLinkedList<DataT, NodeT>::~GSingleLinkedList()
{
	RemoveAll();
}

template<typename DataT, typename NodeT>
GINLINE gsize GSingleLinkedList<DataT, NodeT>::Size() const
{
	return m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::IsEmpty() const
{
	return 0 == m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSingleLinkedList<DataT, NodeT>::Invert()
{
	if (m_nSize <= 1) return;

	NodeT *cur_node = m_pFirst, *pre_node = GNULL, *next_node = m_pFirst;
	for (gsize i = 1; i <= m_nSize; i++)
	{
		next_node = cur_node->m_pNext;
		cur_node->m_pNext = pre_node;
		pre_node = cur_node;
		cur_node = next_node;
	}
	m_pFirst = pre_node;
	return;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::InsertBefore(gsize pos, const DataT &data)
{
	if (pos == NULL_POS)
	{
		return false;
	}

	if (GNULL == m_pFirst || 0 == pos)
	{
		return AddFirst(data);
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}

	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = pTmpNode1;
	pTmpNode2->m_pNext = pNewNode;

	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::InsertBefore(gsize pos, DataT &&data)
{
	if (pos == NULL_POS)
	{
		return false;
	}

	if (GNULL == m_pFirst || 0 == pos)
	{
		return AddFirst(GForward<DataT>(data));
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}

	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = pTmpNode1;
	pTmpNode2->m_pNext = pNewNode;

	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::InsertBefore(NodeT *node, const DataT &data)
{	
	if (!node)
	{
		return false;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	if (pTmpNode1 == GNULL)
	{
		// 查找不到，不做任何操作
		return false;
	}
	
	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = node;
	if (pTmpNode2)
	{
		pTmpNode2->m_pNext = pNewNode;
	}
	if (m_pFirst == node)
	{
		m_pFirst = pNewNode;
	}
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::InsertBefore(NodeT *node, DataT &&data)
{
	if (!node)
	{
		return false;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	if (pTmpNode1 == GNULL)
	{
		// 查找不到，不做任何操作
		return false;
	}

	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = node;
	if (pTmpNode2)
	{
		pTmpNode2->m_pNext = pNewNode;
	}
	if (m_pFirst == node)
	{
		m_pFirst = pNewNode;
	}
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::InsertAfter(gsize pos, const DataT &data)
{
	if (GNULL == m_pFirst)
	{
		return AddFirst(data);
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pTmpNode->m_pNext = pNewNode;

	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::InsertAfter(gsize pos, DataT &&data)
{
	if (GNULL == m_pFirst)
	{
		return AddFirst(GForward<DataT>(data));
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pTmpNode->m_pNext = pNewNode;

	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::InsertAfter(NodeT *node, const DataT &data)
{
	if (GNULL == node)
	{
		return false;
	}

	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = node->m_pNext;
	node->m_pNext = pNewNode;
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::InsertAfter(NodeT *node, DataT &&data)
{
	if (GNULL == node)
	{
		return false;
	}

	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = node->m_pNext;
	node->m_pNext = pNewNode;
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::AddFirst(const DataT &data)
{
	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = m_pFirst;
	m_pFirst = pNewNode;
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::AddFirst(DataT &&data)
{
	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = m_pFirst;
	m_pFirst = pNewNode;
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::AddLast(const DataT &data)
{
	return InsertAfter(m_nSize - 1, data);
}

template<typename DataT, typename NodeT>
GINLINE gbool GSingleLinkedList<DataT, NodeT>::AddLast(DataT &&data)
{
	return InsertAfter(m_nSize - 1, GForward<DataT>(data));
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSingleLinkedList<DataT, NodeT>::Remove(const NodeT *node)
{
	if (!node || m_nSize <= 0)
	{
		return;
	}

	if (node == m_pFirst)
	{
		RemoveFirst();
		return;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}

	if (GNULL == pTmpNode1)
	{
		return;
	}

	pTmpNode2->m_pNext = pTmpNode1->m_pNext;
	delete pTmpNode1;
	pTmpNode1 = GNULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSingleLinkedList<DataT, NodeT>::RemoveAt(gsize pos)
{
	GASSERT(pos < m_nSize);

	if (0 == pos)
	{
		RemoveFirst();
		return;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pTmpNode2->m_pNext = pTmpNode1->m_pNext;
	delete pTmpNode1;
	pTmpNode1 = GNULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSingleLinkedList<DataT, NodeT>::RemoveFirst()
{
	if (!m_pFirst)
	{
		return;
	}

	NodeT *pTmpNode = m_pFirst;
	m_pFirst = m_pFirst->m_pNext;

	delete pTmpNode;
	--m_nSize;
	return;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSingleLinkedList<DataT, NodeT>::RemoveLast()
{
	GASSERT(0 != m_nSize);
	RemoveAt(m_nSize - 1);
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSingleLinkedList<DataT, NodeT>::RemoveAll()
{
	if (m_nSize <= 0)
	{
		return;
	}

	NodeT *pTmpNode = GNULL;
	for (gsize i = 0; i < m_nSize; ++i)
	{
		pTmpNode = m_pFirst->m_pNext;
		delete m_pFirst;
		m_pFirst = pTmpNode;
	}

	m_pFirst = GNULL;
	m_nSize = 0;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSingleLinkedList<DataT, NodeT>::GetFirstNode()
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSingleLinkedList<DataT, NodeT>::GetFirstNode() const
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSingleLinkedList<DataT, NodeT>::GetLastNode()
{
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	return pTmpNode2;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSingleLinkedList<DataT, NodeT>::GetLastNode() const
{
	const NodeT *pTmpNode1 = m_pFirst;
	const NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	return pTmpNode2;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSingleLinkedList<DataT, NodeT>::GetNodeAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSingleLinkedList<DataT, NodeT>::GetNodeAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	const NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
GINLINE DataT &GSingleLinkedList<DataT, NodeT>::GetFirstData()
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE const DataT &GSingleLinkedList<DataT, NodeT>::GetFirstData() const
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE DataT &GSingleLinkedList<DataT, NodeT>::GetLastData()
{
	NodeT *pTail = GetLastNode();
	GASSERT(pTail);
	return pTail->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE const DataT &GSingleLinkedList<DataT, NodeT>::GetLastData() const
{
	const NodeT *pTail = GetLastNode();
	GASSERT(pTail);
	return pTail->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE DataT &GSingleLinkedList<DataT, NodeT>::GetDataAt(gsize pos)
{
	NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE const DataT &GSingleLinkedList<DataT, NodeT>::GetDataAt(gsize pos) const
{
	const NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSingleLinkedList<DataT, NodeT>::SetDataAt(gsize pos, const DataT &data)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = data;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSingleLinkedList<DataT, NodeT>::SetDataAt(gsize pos, DataT &&data)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = GForward<DataT>(data);
}

template<typename DataT, typename NodeT>
GINLINE gsize GSingleLinkedList<DataT, NodeT>::IndexOf(const DataT &data) const
{
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < m_nSize; ++i)
	{
		if (data == pTmpNode->m_tData)
			return i;
		pTmpNode = pTmpNode->m_pNext;
	}
	return NULL_POS;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSingleLinkedList<DataT, NodeT>::Find(const DataT &data)
{
	NodeT *pTmpNode = m_pFirst;
	while (pTmpNode)
	{
		if (data == pTmpNode->m_tData)
			return pTmpNode;
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSingleLinkedList<DataT, NodeT>::Find(const DataT &data) const
{
	const NodeT *pTmpNode = m_pFirst;
	while (pTmpNode)
	{
		if (data == pTmpNode->m_tData)
			return pTmpNode;
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
GINLINE gsize GSingleLinkedList<DataT, NodeT>::IndexOfCircle() const
{
	if (0 == m_nSize)
	{
		return NULL_POS;
	}

	NodeT* p1 = m_pFirst; // p1，步长为1
	NodeT* p2 = m_pFirst; // p2，步长为2

	/*判断链表是否有环，当p1=p2时说明链表有环，程序跳出循环。如果p2一直走到链表尽头则说明没有环。*/
	do
	{
		if (p1 != GNULL && p2 != GNULL && p2->m_pNext != GNULL)
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
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}

	p2 = m_pFirst;
	gsize i = 0;
	for (i = 0; i < m_nSize; i++)
	{
		if (p1 == p2) break;
		p2 = p2->m_pNext;
	}
	return i;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSingleLinkedList<DataT, NodeT>::FindCircle()
{
	if (0 == m_nSize)
	{
		return GNULL;
	}

	NodeT* p1 = m_pFirst; // p1，步长为1
	NodeT* p2 = m_pFirst; // p2，步长为2

	/*判断链表是否有环，当p1=p2时说明链表有环，程序跳出循环。如果p2一直走到链表尽头则说明没有环。*/
	do
	{
		if (p1 != GNULL && p2 != GNULL && p2->m_pNext != GNULL)
		{
			p1 = p1->m_pNext;
			p2 = p2->m_pNext->m_pNext;
		}
		else
		{
			return GNULL;
		}
	} while (p1 != p2);

	/*求出环的起点节点，并将其返回*/
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}
	return p1;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSingleLinkedList<DataT, NodeT>::FindCircle() const
{
	if (0 == m_nSize)
	{
		return GNULL;
	}

	const NodeT* p1 = m_pFirst; // p1，步长为1
	const NodeT* p2 = m_pFirst; // p2，步长为2

	/*判断链表是否有环，当p1=p2时说明链表有环，程序跳出循环。如果p2一直走到链表尽头则说明没有环。*/
	do
	{
		if (p1 != GNULL && p2 != GNULL && p2->m_pNext != GNULL)
		{
			p1 = p1->m_pNext;
			p2 = p2->m_pNext->m_pNext;
		}
		else
		{
			return GNULL;
		}
	} while (p1 != p2);

	/*求出环的起点节点，并将其返回*/
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}
	return p1;
}

template<typename DataT, typename NodeT>
GINLINE gsize GSingleLinkedList<DataT, NodeT>::IndexOfCross(const GLinkedList<DataT, NodeT> &list)
{
	if (0 == m_nSize || 0 == list.Size())
	{
		return NULL_POS;
	}

	if (IndexOfCircle() != NULL_POS
		|| list.IndexOfCircle() != NULL_POS)
	{
		return NULL_POS;
	}

	/*将第二个链表接在第一个链表后面*/
	NodeT* pTail = m_pFirst;
	for (gsize i = 1; i < m_nSize; i++)
	{
		pTail = pTail->m_pNext;
	}

	pTail->m_pNext = const_cast<NodeT *>(list.GetFirstNode());
	m_nSize += list.Size();
	gsize i = IndexOfCircle();

	pTail->m_pNext = GNULL;
	m_nSize -= list.Size();
	return i;
}

template<typename DataT, typename NodeT>
DataT &GSingleLinkedList<DataT, NodeT>::operator[](gsize pos)
{
	return GetDataAt(pos);
}

template<typename DataT, typename NodeT>
const DataT &GSingleLinkedList<DataT, NodeT>::operator[](gsize pos) const
{
	return GetDataAt(pos);
}

#endif // _CORE_SINGLE_LINKED_LIST_INLINE_