#ifndef _CORE_DOUBLE_LINKED_LIST_INLINE_
#define _CORE_DOUBLE_LINKED_LIST_INLINE_

template<typename DataT, typename NodeT>
inline GDoubleLinkedList<DataT, NodeT>::GDoubleLinkedList()
: m_nSize(0), m_pFirst(NULL), m_pLast(NULL)
{
}

template<typename DataT, typename NodeT>
inline GDoubleLinkedList<DataT, NodeT>::GDoubleLinkedList(const DataT &data)
: m_nSize(0), m_pFirst(NULL), m_pLast(NULL)
{
	AddFirst(data);
}

template<typename DataT, typename NodeT>
inline GDoubleLinkedList<DataT, NodeT>::GDoubleLinkedList(const GDoubleLinkedList<DataT, NodeT> &other)
: m_nSize(0), m_pFirst(NULL), m_pLast(NULL)
{
	if (other.m_nSize > 0)
	{
		for (gsize i = 0; i < other.m_nSize; i++)
		{
			AddLast(other.GetAt(i));
		}
	}
}

template<typename DataT, typename NodeT>
inline GDoubleLinkedList<DataT, NodeT>& GDoubleLinkedList<DataT, NodeT>::operator=(const GDoubleLinkedList<DataT, NodeT> &other)
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
		for (gsize i = 0; i < other.m_nSize; i++)
		{
			AddLast(other.GetDataAt(i));
		}
	}
	return *this;
}

template<typename DataT, typename NodeT>
inline GDoubleLinkedList<DataT, NodeT>::~GDoubleLinkedList()
{
	RemoveAll();
}

template<typename DataT, typename NodeT>
inline gsize GDoubleLinkedList<DataT, NodeT>::Size() const
{
	return m_nSize;
}

template<typename DataT, typename NodeT>
inline gbool GDoubleLinkedList<DataT, NodeT>::IsEmpty() const
{
	return 0 == m_nSize;
}

template<typename DataT, typename NodeT>
inline gvoid GDoubleLinkedList<DataT, NodeT>::Invert()
{
	if (m_nSize <= 1) return;

	NodeT *tmpNod = NULL, *curNod = m_pFirst, *nextNod = NULL;
	for (gsize i = 1; i <= m_nSize; i++)
	{
		nextNod = curNod->m_pNext;
		tmpNod = curNod->m_pPrevious;
		curNod->m_pPrevious = curNod->m_pNext;
		curNod->m_pNext = tmpNod;
		curNod = nextNod;
	}

	tmpNod = m_pFirst;
	m_pFirst = m_pLast;
	m_pLast = tmpNod;
	return;
}

template<typename DataT, typename NodeT>
inline gbool GDoubleLinkedList<DataT, NodeT>::InsertBefore(gsize pos, const DataT &data)
{
	if (NULL == m_pFirst || 0 == pos)
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
	pNewNode->m_pNext = pTmpNode;
	pNewNode->m_pPrevious = pTmpNode->m_pPrevious;

	pTmpNode->m_pPrevious->m_pNext = pNewNode;
	pTmpNode->m_pPrevious = pNewNode;

	if (NULL == pNewNode->m_pNext)
	{
		m_pLast = pNewNode;
	}

	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline gbool GDoubleLinkedList<DataT, NodeT>::InsertBefore(NodeT *node, const DataT &data)
{
	if (!node || !m_pFirst || !m_pLast)
	{
		return false;
	}

	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}

	pNewNode->m_pPrevious = node->m_pPrevious;
	if (node->m_pPrevious)
	{
		node->m_pPrevious->m_pNext = pNewNode;
	}
	pNewNode->m_pNext = node;
	node->m_pPrevious = pNewNode;
	if (m_pFirst == node)
	{
		m_pFirst = pNewNode;
	}
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline gbool GDoubleLinkedList<DataT, NodeT>::InsertAfter(gsize pos, const DataT &data)
{
	if (NULL == m_pFirst)
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
	pNewNode->m_pPrevious = pTmpNode;
	pTmpNode->m_pNext = pNewNode;

	if (NULL == pNewNode->m_pNext)
	{
		m_pLast = pNewNode;
	}
	else
	{
		pNewNode->m_pNext->m_pPrevious = pNewNode;
	}

	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline gbool GDoubleLinkedList<DataT, NodeT>::InsertAfter(NodeT *node, const DataT &data)
{
	if (!node || !m_pFirst || !m_pLast)
	{
		return false;
	}

	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}

	pNewNode->m_pNext = node->m_pNext;
	if (node->m_pNext)
	{
		node->m_pNext->m_pPrevious = pNewNode;
	}
	pNewNode->m_pPrevious = node;
	node->m_pNext = pNewNode;
	if (m_pLast == node)
	{
		m_pLast = pNewNode;
	}
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline DataT& GDoubleLinkedList<DataT, NodeT>::GetDataAt(gsize pos)
{
	NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
inline const DataT &GDoubleLinkedList<DataT, NodeT>::GetDataAt(gsize pos) const
{
	const NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
inline gbool GDoubleLinkedList<DataT, NodeT>::AddFirst(const DataT &data)
{
	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}

	pNewNode->m_pPrevious = NULL;
	pNewNode->m_pNext = m_pFirst;
	if (NULL != m_pFirst)
	{
		m_pFirst->m_pPrevious = pNewNode;
	}
	m_pFirst = pNewNode;
	if (NULL == m_pLast)
	{
		m_pLast = pNewNode;
	}
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline gbool GDoubleLinkedList<DataT, NodeT>::AddLast(const DataT &data)
{
	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}

	pNewNode->m_pNext = NULL;
	pNewNode->m_pPrevious = m_pLast;
	if (NULL != m_pLast)
	{
		m_pLast->m_pNext = pNewNode;
	}
	m_pLast = pNewNode;
	if (NULL == m_pFirst)
	{
		m_pFirst = pNewNode;
	}
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline NodeT *GDoubleLinkedList<DataT, NodeT>::GetFirstNode()
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
inline const NodeT *GDoubleLinkedList<DataT, NodeT>::GetFirstNode() const
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
inline NodeT *GDoubleLinkedList<DataT, NodeT>::GetLastNode()
{
	return m_pLast;
}

template<typename DataT, typename NodeT>
inline const NodeT *GDoubleLinkedList<DataT, NodeT>::GetLastNode() const
{
	return m_pLast;
}

template<typename DataT, typename NodeT>
inline NodeT *GDoubleLinkedList<DataT, NodeT>::GetNodeAt(gsize pos)
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
inline const NodeT *GDoubleLinkedList<DataT, NodeT>::GetNodeAt(gsize pos) const
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
inline DataT &GDoubleLinkedList<DataT, NodeT>::GetFirstData()
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
inline const DataT &GDoubleLinkedList<DataT, NodeT>::GetFirstData() const
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
inline DataT &GDoubleLinkedList<DataT, NodeT>::GetLastData()
{
	GASSERT(m_pLast);
	return m_pLast->m_tData;
}

template<typename DataT, typename NodeT>
inline const DataT &GDoubleLinkedList<DataT, NodeT>::GetLastData() const
{
	GASSERT(m_pLast);
	return m_pLast->m_tData;
}

template<typename DataT, typename NodeT>
inline gvoid GDoubleLinkedList<DataT, NodeT>::Remove(NodeT *node)
{
	if (!node)
	{
		return;
	}

	if (node->m_pPrevious)
	{
		node->m_pPrevious->m_pNext = node->m_pNext;
	}
	else
	{
		m_pFirst = NULL;
	}

	if (node->m_pNext)
	{
		node->m_pNext->m_pPrevious = node->m_pPrevious;
	}
	else
	{
		m_pLast = NULL;
	}

	delete node;
	--m_nSize;
}

template<typename DataT, typename NodeT>
inline gvoid GDoubleLinkedList<DataT, NodeT>::RemoveAt(gsize pos)
{
	GASSERT(pos < m_nSize);

	if (0 == pos)
	{
		// 头指针
		RemoveFirst();
		return;
	}
	else if (pos == m_nSize - 1)
	{
		// 尾指针
		RemoveLast();
		return;
	}
	
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
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
		m_pLast = pTmpNode->m_pPrevious;
	}

	delete pTmpNode;
	pTmpNode = NULL;

	--m_nSize;
	return;
}

template<typename DataT, typename NodeT>
inline gvoid GDoubleLinkedList<DataT, NodeT>::RemoveFirst()
{
	if (!m_pFirst)
	{
		return;
	}

	NodeT *pTmpNode = m_pFirst;

	m_pFirst = m_pFirst->m_pNext;
	if (m_pFirst)
	{
		m_pFirst->m_pPrevious = NULL;
	}
	else
	{
		m_pLast = NULL;
	}

	delete pTmpNode;
	pTmpNode = NULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
inline gvoid GDoubleLinkedList<DataT, NodeT>::RemoveLast()
{
	if (!m_pLast)
	{
		return;
	}

	NodeT *pTmpNode = m_pLast;
	m_pLast = m_pLast->m_pPrevious;
	if (m_pLast)
	{
		m_pLast->m_pNext = NULL;
	}
	else
	{
		m_pFirst = NULL;
	}

	delete pTmpNode;
	pTmpNode = NULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
inline gvoid GDoubleLinkedList<DataT, NodeT>::RemoveAll()
{
	if (m_nSize <= 0)
	{
		return;
	}

	NodeT *pTmpNode = NULL;
	for (gsize i = 0; i < m_nSize; ++i)
	{
		pTmpNode = m_pFirst->m_pNext;
		delete m_pFirst;
		m_pFirst = pTmpNode;
	}

	m_pFirst = NULL;
	m_pLast = NULL;
	m_nSize = 0;
}

template<typename DataT, typename NodeT>
inline gvoid GDoubleLinkedList<DataT, NodeT>::SetDataAt(gsize pos, const DataT &data)
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
inline gsize GDoubleLinkedList<DataT, NodeT>::IndexOf(const DataT &data) const
{
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < m_nSize; i++)
	{
		if (data == pTmpNode->m_tData)
			return i;
		pTmpNode = pTmpNode->m_pNext;
	}
	return NULL_POS;
}

template<typename DataT, typename NodeT>
inline NodeT *GDoubleLinkedList<DataT, NodeT>::Find(const DataT &data)
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
inline const NodeT *GDoubleLinkedList<DataT, NodeT>::Find(const DataT &data) const
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
inline gsize GDoubleLinkedList<DataT, NodeT>::IndexOfCircle() const
{
	if (0 == m_nSize)
	{
		return NULL_POS;
	}

	NodeT* p1 = m_pFirst;
	NodeT* p2 = m_pFirst;

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
NodeT *GDoubleLinkedList<DataT, NodeT>::FindCircle()
{
	if (0 == m_nSize)
	{
		return NULL;
	}

	NodeT* p1 = m_pFirst;
	NodeT* p2 = m_pFirst;

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
			return NULL;
		}
	} while (p1 != p2);

	// 求出环的起点节点，并将其返回
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}
	return p1;
}

template<typename DataT, typename NodeT>
const NodeT *GDoubleLinkedList<DataT, NodeT>::FindCircle() const
{
	if (0 == m_nSize)
	{
		return NULL;
	}

	const NodeT* p1 = m_pFirst;
	const NodeT* p2 = m_pFirst;

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
			return NULL;
		}
	} while (p1 != p2);

	// 求出环的起点节点，并将其返回
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}
	return p1;
}

template<typename DataT, typename NodeT>
inline gsize GDoubleLinkedList<DataT, NodeT>::IndexOfCross(const GLinkedList<DataT, NodeT> &list)
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

	// 将第二个链表接在第一个链表后面
	m_pLast->m_pNext = const_cast<NodeT *>(list.GetFirstNode());
	m_nSize += list.Size();

	gsize i = IndexOfCircle();

	m_pLast->m_pNext = NULL;
	m_nSize -= list.Size();
	return i;
}

template<typename DataT, typename NodeT>
inline DataT &GDoubleLinkedList<DataT, NodeT>::operator[](gsize pos)
{
	return GetDataAt(pos);
}

template<typename DataT, typename NodeT>
inline const DataT &GDoubleLinkedList<DataT, NodeT>::operator[](gsize pos) const
{
	return GetDataAt(pos);
}

#endif // _CORE_DOUBLE_LINKED_LIST_INLINE_