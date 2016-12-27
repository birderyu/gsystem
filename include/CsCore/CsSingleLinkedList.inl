#ifndef _CORE_SINGLE_LINKED_LIST_INLINE_
#define _CORE_SINGLE_LINKED_LIST_INLINE_

template<typename DataT, typename NodeT>
inline CsSingleLinkedList<DataT, NodeT>::CsSingleLinkedList()
: m_nSize(0), m_pFirst(NULL)
{
}

template<typename DataT, typename NodeT>
inline CsSingleLinkedList<DataT, NodeT>::CsSingleLinkedList(const DataT &data)
: m_nSize(0), m_pFirst(NULL)
{
	AddFirst(data);
}

template<typename DataT, typename NodeT>
inline CsSingleLinkedList<DataT, NodeT>::CsSingleLinkedList(const CsSingleLinkedList<DataT, NodeT> &other)
: m_nSize(0), m_pFirst(NULL)
{
	if (other.m_nLength > 0)
	{
		for (cs_size_t i = 0; i < other.m_nLength; i++)
		{
			AddLast(other.GetAt(i));
		}
	}
}

template<typename DataT, typename NodeT>
inline CsSingleLinkedList<DataT, NodeT>& CsSingleLinkedList<DataT, NodeT>::operator=(const CsSingleLinkedList<DataT, NodeT>& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (m_nSize > 0)
	{
		RemoveAll();
	}

	if (other.m_nLength > 0)
	{
		for (cs_size_t i = 0; i < other.m_nLength; i++)
		{
			AddLast(other.GetAt(i));
		}
	}
	return *this;
}

template<typename DataT, typename NodeT>
inline CsSingleLinkedList<DataT, NodeT>::~CsSingleLinkedList()
{
	RemoveAll();
}

template<typename DataT, typename NodeT>
inline cs_size_t CsSingleLinkedList<DataT, NodeT>::Size() const
{
	return m_nSize;
}

template<typename DataT, typename NodeT>
inline cs_bool CsSingleLinkedList<DataT, NodeT>::IsEmpty() const
{
	return 0 == m_nSize;
}

template<typename DataT, typename NodeT>
inline cs_void CsSingleLinkedList<DataT, NodeT>::Invert()
{
	if (m_nSize <= 1) return;

	NodeT *cur_node = m_pFirst, *pre_node = NULL, *next_node = m_pFirst;
	for (cs_size_t i = 1; i <= m_nSize; i++)
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
inline cs_bool CsSingleLinkedList<DataT, NodeT>::AddFirst(const DataT &data)
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
inline cs_bool CsSingleLinkedList<DataT, NodeT>::AddLast(const DataT &data)
{
	return InsertAfter(m_nSize - 1, data);
}

template<typename DataT, typename NodeT>
inline cs_bool CsSingleLinkedList<DataT, NodeT>::InsertBefore(cs_size_t pos, const DataT &data)
{
	if (pos == NULL_POS)
	{
		return false;
	}

	if (NULL == m_pFirst || 0 == pos)
	{
		return AddFirst(data);
	}

	CS_ASSERT(pos < m_nSize);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = NULL;
	for (cs_size_t i = 0; i < pos; ++i)
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
inline cs_bool CsSingleLinkedList<DataT, NodeT>::InsertBefore(NodeT *node, const DataT &data)
{	
	if (!node)
	{
		return false;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = NULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	if (pTmpNode1 == NULL)
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
inline cs_bool CsSingleLinkedList<DataT, NodeT>::InsertAfter(cs_size_t pos, const DataT &data)
{
	if (NULL == m_pFirst)
	{
		return AddFirst(data);
	}

	CS_ASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (cs_size_t i = 0; i < pos; ++i)
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
inline cs_bool CsSingleLinkedList<DataT, NodeT>::InsertAfter(NodeT *node, const DataT &data)
{
	if (NULL == node)
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
inline cs_void CsSingleLinkedList<DataT, NodeT>::Remove(NodeT *node)
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
	NodeT *pTmpNode2 = NULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}

	if (NULL == pTmpNode1)
	{
		return;
	}

	pTmpNode2->m_pNext = pTmpNode1->m_pNext;
	delete pTmpNode1;
	pTmpNode1 = NULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
inline cs_void CsSingleLinkedList<DataT, NodeT>::RemoveAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nSize);

	if (0 == pos)
	{
		RemoveFirst();
		return;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = NULL;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pTmpNode2->m_pNext = pTmpNode1->m_pNext;
	delete pTmpNode1;
	pTmpNode1 = NULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
inline cs_void CsSingleLinkedList<DataT, NodeT>::RemoveFirst()
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
inline cs_void CsSingleLinkedList<DataT, NodeT>::RemoveLast()
{
	CS_ASSERT(0 != m_nSize);
	RemoveAt(m_nSize - 1);
}

template<typename DataT, typename NodeT>
inline cs_void CsSingleLinkedList<DataT, NodeT>::RemoveAll()
{
	if (m_nSize <= 0)
	{
		return;
	}

	NodeT *pTmpNode = NULL;
	for (cs_size_t i = 0; i < m_nSize; ++i)
	{
		pTmpNode = m_pFirst->m_pNext;
		delete m_pFirst;
		m_pFirst = pTmpNode;
	}

	m_pFirst = NULL;
	m_nSize = 0;
}

template<typename DataT, typename NodeT>
inline NodeT *CsSingleLinkedList<DataT, NodeT>::GetFirstNode()
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
inline const NodeT *CsSingleLinkedList<DataT, NodeT>::GetFirstNode() const
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
inline NodeT *CsSingleLinkedList<DataT, NodeT>::GetLastNode()
{
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = NULL;
	while (pTmpNode1)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	return pTmpNode2;
}

template<typename DataT, typename NodeT>
inline const NodeT *CsSingleLinkedList<DataT, NodeT>::GetLastNode() const
{
	const NodeT *pTmpNode1 = m_pFirst;
	const NodeT *pTmpNode2 = NULL;
	while (pTmpNode1)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	return pTmpNode2;
}

template<typename DataT, typename NodeT>
inline NodeT *CsSingleLinkedList<DataT, NodeT>::GetNodeAt(cs_size_t pos)
{
	CS_ASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
inline const NodeT *CsSingleLinkedList<DataT, NodeT>::GetNodeAt(cs_size_t pos) const
{
	CS_ASSERT(pos < m_nSize);
	const NodeT *pTmpNode = m_pFirst;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
inline DataT &CsSingleLinkedList<DataT, NodeT>::GetFirstData()
{
	CS_ASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
inline const DataT &CsSingleLinkedList<DataT, NodeT>::GetFirstData() const
{
	CS_ASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
inline DataT &CsSingleLinkedList<DataT, NodeT>::GetLastData()
{
	NodeT *pTail = GetLastNode();
	CS_ASSERT(pTail);
	return pTail->m_tData;
}

template<typename DataT, typename NodeT>
inline const DataT &CsSingleLinkedList<DataT, NodeT>::GetLastData() const
{
	const NodeT *pTail = GetLastNode();
	CS_ASSERT(pTail);
	return pTail->m_tData;
}

template<typename DataT, typename NodeT>
inline DataT &CsSingleLinkedList<DataT, NodeT>::GetDataAt(cs_size_t pos)
{
	NodeT *node = GetNodeAt(pos);
	CS_ASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
inline const DataT &CsSingleLinkedList<DataT, NodeT>::GetDataAt(cs_size_t pos) const
{
	const NodeT *node = GetNodeAt(pos);
	CS_ASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
inline cs_void CsSingleLinkedList<DataT, NodeT>::SetDataAt(cs_size_t pos, const DataT &data)
{
	CS_ASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (cs_size_t i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = data;
}

template<typename DataT, typename NodeT>
inline cs_size_t CsSingleLinkedList<DataT, NodeT>::IndexOf(const DataT &data) const
{
	NodeT *pTmpNode = m_pFirst;
	for (cs_size_t i = 0; i < m_nSize; ++i)
	{
		if (data == pTmpNode->m_tData)
			return i;
		pTmpNode = pTmpNode->m_pNext;
	}
	return NULL_POS;
}

template<typename DataT, typename NodeT>
inline NodeT *CsSingleLinkedList<DataT, NodeT>::Find(const DataT &data)
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
inline const NodeT *CsSingleLinkedList<DataT, NodeT>::Find(const DataT &data) const
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
inline cs_size_t CsSingleLinkedList<DataT, NodeT>::IndexOfCircle() const
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
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}

	p2 = m_pFirst;
	cs_size_t i = 0;
	for (i = 0; i < m_nSize; i++)
	{
		if (p1 == p2) break;
		p2 = p2->m_pNext;
	}
	return i;
}

template<typename DataT, typename NodeT>
inline NodeT *CsSingleLinkedList<DataT, NodeT>::FindCircle()
{
	if (0 == m_nSize)
	{
		return NULL;
	}

	NodeT* p1 = m_pFirst; // p1，步长为1
	NodeT* p2 = m_pFirst; // p2，步长为2

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
			return NULL;
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
inline const NodeT *CsSingleLinkedList<DataT, NodeT>::FindCircle() const
{
	if (0 == m_nSize)
	{
		return NULL;
	}

	const NodeT* p1 = m_pFirst; // p1，步长为1
	const NodeT* p2 = m_pFirst; // p2，步长为2

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
			return NULL;
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
inline cs_size_t CsSingleLinkedList<DataT, NodeT>::IndexOfCross(const CsLinkedList<DataT, NodeT> &list)
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
	for (cs_size_t i = 1; i < m_nSize; i++)
	{
		pTail = pTail->m_pNext;
	}

	pTail->m_pNext = const_cast<NodeT *>(list.GetFirstNode());
	m_nSize += list.Size();
	cs_size_t i = IndexOfCircle();

	pTail->m_pNext = NULL;
	m_nSize -= list.Size();
	return i;
}

template<typename DataT, typename NodeT>
DataT &CsSingleLinkedList<DataT, NodeT>::operator[](cs_size_t pos)
{
	return GetDataAt(pos);
}

template<typename DataT, typename NodeT>
const DataT &CsSingleLinkedList<DataT, NodeT>::operator[](cs_size_t pos) const
{
	return GetDataAt(pos);
}

#endif // _CORE_SINGLE_LINKED_LIST_INLINE_