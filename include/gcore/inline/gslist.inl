#ifndef _CORE_SINGLE_LINKED_LIST_INLINE_
#define _CORE_SINGLE_LINKED_LIST_INLINE_

namespace gsystem { // gsystem

template<typename T> GINLINE
GSListNode<T>::GSListNode(const T &value, GSListNode<T> *next)
	: GNextNodeT<GSListNode<T>>(next)
	, GValueNodeT<T>(value)
{

}

template<typename T> GINLINE
GSListNode<T>::GSListNode(T &&value, GSListNode<T> *next)
	: GNextNodeT<GSListNode<T>>(next)
	, GValueNodeT<T>(GForward<T>(value))
{

}

template<typename T, typename NodeT>
GINLINE GSList<T, NodeT>::GSList()
: m_nSize(0), m_pFirst(GNULL)
{
}

template<typename T, typename NodeT>
GINLINE GSList<T, NodeT>::GSList(const T &value)
: m_nSize(0), m_pFirst(GNULL)
{
	AddFirst(value);
}

template<typename T, typename NodeT>
GINLINE GSList<T, NodeT>::GSList(T &&value)
: m_nSize(0), m_pFirst(GNULL)
{
	AddFirst(GForward<T>(value));
}

template<typename T, typename NodeT>
GINLINE GSList<T, NodeT>::GSList(const GSList<T, NodeT> &list)
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

template<typename T, typename NodeT>
GINLINE GSList<T, NodeT>::GSList(GSList<T, NodeT> &&list)
: m_nSize(list.m_nSize), m_pFirst(list.m_pFirst)
{
	list.m_nSize = 0;
	list.m_pFirst = GNULL;
}

template<typename T, typename NodeT>
GINLINE GSList<T, NodeT>& GSList<T, NodeT>::operator=(const GSList<T, NodeT> &list)
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

template<typename T, typename NodeT>
GINLINE GSList<T, NodeT>& GSList<T, NodeT>::operator=(GSList<T, NodeT> &&list)
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

template<typename T, typename NodeT>
GINLINE GSList<T, NodeT>::~GSList()
{
	RemoveAll();
}

template<typename T, typename NodeT>
GINLINE gsize GSList<T, NodeT>::Size() const
{
	return m_nSize;
}

template<typename T, typename NodeT>
GINLINE gbool GSList<T, NodeT>::IsEmpty() const
{
	return 0 == m_nSize;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::GetFirstNode()
{
	return m_pFirst;
}

template<typename T, typename NodeT> GINLINE
const NodeT *GSList<T, NodeT>::GetFirstNode() const
{
	return m_pFirst;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::GetLastNode()
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

template<typename T, typename NodeT> GINLINE
const NodeT *GSList<T, NodeT>::GetLastNode() const
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

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::GetNodeBefore(const NodeT *node)
{
	NodeT *pnode = m_pFirst;
	while (pnode)
	{
		if (pnode->m_pNext == node)
		{
			return pnode;
		}
	}
	return GNULL;
}

template<typename T, typename NodeT> GINLINE
const NodeT *GSList<T, NodeT>::GetNodeBefore(const NodeT *node) const
{
	const NodeT *pnode = m_pFirst;
	while (pnode)
	{
		if (pnode->m_pNext == node)
		{
			return pnode;
		}
	}
	return GNULL;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::GetNodeAfter(const NodeT *node)
{
	if (node == GNULL)
	{
		return GNULL;
	}
	return node->m_pNext;
}

template<typename T, typename NodeT> GINLINE
const NodeT *GSList<T, NodeT>::GetNodeAfter(const NodeT *node) const
{
	if (node == GNULL)
	{
		return GNULL;
	}
	return node->m_pNext;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::GetNodeAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename T, typename NodeT> GINLINE
const NodeT *GSList<T, NodeT>::GetNodeAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	const NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename T, typename NodeT>
GINLINE T &GSList<T, NodeT>::GetFirstValue()
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename T, typename NodeT>
GINLINE const T &GSList<T, NodeT>::GetFirstValue() const
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename T, typename NodeT>
GINLINE T &GSList<T, NodeT>::GetLastValue()
{
	NodeT *pTail = GetLastNode();
	GASSERT(pTail);
	return pTail->m_tData;
}

template<typename T, typename NodeT>
GINLINE const T &GSList<T, NodeT>::GetLastValue() const
{
	const NodeT *pTail = GetLastNode();
	GASSERT(pTail);
	return pTail->m_tData;
}

template<typename T, typename NodeT>
GINLINE T &GSList<T, NodeT>::GetValueAt(gsize pos)
{
	NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename T, typename NodeT>
GINLINE const T &GSList<T, NodeT>::GetValueAt(gsize pos) const
{
	const NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename T, typename NodeT>
GINLINE gvoid GSList<T, NodeT>::SetValueAt(gsize pos, const T &value)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = value;
}

template<typename T, typename NodeT>
GINLINE gvoid GSList<T, NodeT>::SetValueAt(gsize pos, T &&value)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = GForward<T>(value);
}

template<typename T, typename NodeT>
GINLINE gsize GSList<T, NodeT>::FirstIndexOf(const T &value) const
{
	NodeT *node = m_pFirst;
	for (gsize i = 0; i < m_nSize; ++i)
	{
		if (node == GNULL)
		{
			break;
		}
		if (value == node->m_tData)
			return i;
		node = node->m_pNext;
	}
	return NULL_POS;
}

template<typename T, typename NodeT>
GINLINE gsize GSList<T, NodeT>::LastIndexOf(const T &value) const
{
	NodeT *node = m_pFirst;
	gsize lastIndex = NULL_POS;
	for (gsize i = 0; i < m_nSize; ++i)
	{
		if (node == GNULL)
		{
			break;
		}
		if (value == node->m_tData)
			lastIndex = i;
		node = node->m_pNext;
	}
	return NULL_POS;
}

template<typename T, typename NodeT>
GINLINE NodeT *GSList<T, NodeT>::Find(const T &value)
{
	NodeT *node = m_pFirst;
	while (node)
	{
		if (value == node->m_tData)
			return node;
		node = node->m_pNext;
	}
	return node;
}

template<typename T, typename NodeT>
GINLINE const NodeT *GSList<T, NodeT>::Find(const T &value) const
{
	const NodeT *node = m_pFirst;
	while (node)
	{
		if (value == node->m_tData)
			return node;
		node = node->m_pNext;
	}
	return node;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::AddFirst(const T &value)
{
	NodeT *node = new NodeT(value);
	node->m_pNext = m_pFirst;
	m_pFirst = node;
	++m_nSize;
	return node;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::AddFirst(T &&value)
{
	NodeT *node = new NodeT(GForward<T>(value));
	node->m_pNext = m_pFirst;
	m_pFirst = node;
	++m_nSize;
	return node;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::AddLast(const T &value)
{
	return InsertAfter(m_nSize - 1, value);
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::AddLast(T &&value)
{
	return InsertAfter(m_nSize - 1, GForward<T>(value));
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::InsertBefore(gsize pos, const T &value)
{
	GASSERT(pos != NULL_POS);
	if (GNULL == m_pFirst || 0 == pos)
	{
		return AddFirst(value);
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	NodeT *pNewNode = new NodeT(value);
	pNewNode->m_pNext = pTmpNode1;
	pTmpNode2->m_pNext = pNewNode;
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::InsertBefore(gsize pos, T &&value)
{
	GASSERT(pos != NULL_POS);
	if (GNULL == m_pFirst || 0 == pos)
	{
		return AddFirst(GForward<T>(value));
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}

	NodeT *pNewNode = new NodeT(GForward<T>(value));
	pNewNode->m_pNext = pTmpNode1;
	pTmpNode2->m_pNext = pNewNode;
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::InsertBefore(NodeT *node, const T &value)
{	
	GASSERT(node);
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
		return GNULL;
	}
	
	NodeT *pNewNode = new NodeT(value);
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
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::InsertBefore(NodeT *node, T &&value)
{
	GASSERT(node);
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
		return GNULL;
	}

	NodeT *pNewNode = new NodeT(GForward<T>(value));
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
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::InsertAfter(gsize pos, const T &value)
{
	if (GNULL == m_pFirst)
	{
		return AddFirst(value);
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	NodeT *pNewNode = new NodeT(value);
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pTmpNode->m_pNext = pNewNode;
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::InsertAfter(gsize pos, T &&value)
{
	if (GNULL == m_pFirst)
	{
		return AddFirst(GForward<T>(value));
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	NodeT *pNewNode = new NodeT(GForward<T>(value));
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pTmpNode->m_pNext = pNewNode;
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::InsertAfter(NodeT *node, const T &value)
{
	GASSERT(node);
	NodeT *pNewNode = new NodeT(value);
	pNewNode->m_pNext = node->m_pNext;
	node->m_pNext = pNewNode;
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GSList<T, NodeT>::InsertAfter(NodeT *node, T &&value)
{
	GASSERT(node);
	NodeT *pNewNode = new NodeT(GForward<T>(value));
	pNewNode->m_pNext = node->m_pNext;
	node->m_pNext = pNewNode;
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT>
GINLINE gvoid GSList<T, NodeT>::Remove(const NodeT *node)
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

template<typename T, typename NodeT>
GINLINE gvoid GSList<T, NodeT>::RemoveAt(gsize pos, T *value)
{
	GASSERT(pos < m_nSize);

	if (0 == pos)
	{
		RemoveFirst(value);
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
	if (value)
	{
		// 将元素移走，而非拷贝
		*value = GMove(pTmpNode1->m_tData);
	}
	delete pTmpNode1;
	pTmpNode1 = GNULL;
	--m_nSize;
}

template<typename T, typename NodeT>
GINLINE gvoid GSList<T, NodeT>::RemoveFirst(T *value)
{
	if (!m_pFirst)
	{
		return;
	}

	NodeT *pTmpNode = m_pFirst;
	m_pFirst = m_pFirst->m_pNext;
	if (value)
	{
		// 将元素移走，而非拷贝
		*value = GMove(pTmpNode->m_tData);
	}
	delete pTmpNode;
	--m_nSize;
	return;
}

template<typename T, typename NodeT>
GINLINE gvoid GSList<T, NodeT>::RemoveLast(T *value)
{
	GASSERT(0 != m_nSize);
	RemoveAt(m_nSize - 1, value);
}

template<typename T, typename NodeT>
GINLINE gvoid GSList<T, NodeT>::RemoveAll()
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

template<typename T, typename NodeT>
GINLINE gvoid GSList<T, NodeT>::Invert()
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

template<typename T, typename NodeT>
GINLINE gsize GSList<T, NodeT>::IndexOfCircle() const
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

template<typename T, typename NodeT>
GINLINE NodeT *GSList<T, NodeT>::FindCircle()
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

template<typename T, typename NodeT>
GINLINE const NodeT *GSList<T, NodeT>::FindCircle() const
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

template<typename T, typename NodeT>
GINLINE gsize GSList<T, NodeT>::IndexOfCross(const GLinkedList<T, NodeT> &list)
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

} // namespace gsystem

#endif // _CORE_SINGLE_LINKED_LIST_INLINE_