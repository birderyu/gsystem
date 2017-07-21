#ifndef _CORE_DOUBLE_LINKED_LIST_INLINE_
#define _CORE_DOUBLE_LINKED_LIST_INLINE_

#include "gutility.h"

namespace gsystem { // gsystem

template<typename T> GINLINE
GDListNode<T>::GDListNode(const T &value, GDListNode<T> *previous, GDListNode<T> *next)
	: GPreviousNextNodeT<GDListNode<T>>(previous, next)
	, GValueNodeT<T>(value)
{

}

template<typename T> GINLINE
GDListNode<T>::GDListNode(T &&value, GDListNode<T> *previous, GDListNode<T> *next)
	: GPreviousNextNodeT<GDListNode<T>>(previous, next)
	, GValueNodeT<T>(GForward<T>(value))
{

}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT>::GDList()
: m_nSize(0), m_pFirst(GNULL), m_pLast(GNULL)
{
}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT>::GDList(const T &data)
: m_nSize(0), m_pFirst(GNULL), m_pLast(GNULL)
{
	AddFirst(data);
}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT>::GDList(T &&data)
: m_nSize(0), m_pFirst(GNULL), m_pLast(GNULL)
{
	AddFirst(GForward<T>(data));
}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT>::GDList(const GDList<T, NodeT> &list)
: m_nSize(0), m_pFirst(GNULL), m_pLast(GNULL)
{
	NodeT *node = list.m_pFirst;
	if (GNULL == node)
	{
		return;
	}

	NodeT *new_node = new NodeT(node->m_tData);
	m_pFirst = m_pLast = new_node;
	m_nSize = 1;
	node = node->m_pNext;
	while (node)
	{
		new_node->m_pNext = new NodeT(node->m_tData);
		m_pLast = new_node;

		new_node = new_node->m_pNext;
		node = node->m_pNext;

		m_nSize++;
	}
}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT>::GDList(GDList<T, NodeT> &&list)
: m_nSize(list.m_nSize), m_pFirst(list.m_pFirst), m_pLast(list.m_pLast)
{
	list.m_nSize = 0;
	list.m_pFirst = GNULL;
	list.m_pLast = GNULL;
}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT>& GDList<T, NodeT>::operator=(const GDList<T, NodeT> &list)
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
	m_pFirst = m_pLast = new_node;
	m_nSize = 1;
	node = node->m_pNext;
	while (node)
	{
		new_node->m_pNext = new NodeT(node->m_tData);
		m_pLast = new_node;

		new_node = new_node->m_pNext;
		node = node->m_pNext;

		m_nSize++;
	}
	return *this;
}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT>& GDList<T, NodeT>::operator=(GDList<T, NodeT> &&list)
{
	if (this == &list)
	{
		return *this;
	}

	if (!IsEmpty())
	{
		RemoveAll();
	}

	m_nSize = list.m_nSize;
	m_pFirst = list.m_pFirst;
	m_pLast = list.m_pLast;
	list.m_nSize = 0;
	list.m_pFirst = list.m_pLast = GNULL;
	return *this;
}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT>::~GDList()
{
	RemoveAll();
}

template<typename T, typename NodeT>
GINLINE gsize GDList<T, NodeT>::Size() const
{
	return m_nSize;
}

template<typename T, typename NodeT>
GINLINE gbool GDList<T, NodeT>::IsEmpty() const
{
	return 0 == m_nSize;
}

template<typename T, typename NodeT>
GINLINE NodeT *GDList<T, NodeT>::GetFirstNode()
{
	return m_pFirst;
}

template<typename T, typename NodeT>
GINLINE const NodeT *GDList<T, NodeT>::GetFirstNode() const
{
	return m_pFirst;
}

template<typename T, typename NodeT>
GINLINE NodeT *GDList<T, NodeT>::GetLastNode()
{
	return m_pLast;
}

template<typename T, typename NodeT>
GINLINE const NodeT *GDList<T, NodeT>::GetLastNode() const
{
	return m_pLast;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::GetNodeBefore(const NodeT *node)
{
	if (node == GNULL)
	{
		return GNULL;
	}
	return node->m_pPrevious;
}

template<typename T, typename NodeT> GINLINE
const NodeT *GDList<T, NodeT>::GetNodeBefore(const NodeT *node) const
{
	if (node == GNULL)
	{
		return GNULL;
	}
	return node->m_pPrevious;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::GetNodeAfter(const NodeT *node)
{
	if (node == GNULL)
	{
		return GNULL;
	}
	return node->m_pNext;
}

template<typename T, typename NodeT> GINLINE
const NodeT *GDList<T, NodeT>::GetNodeAfter(const NodeT *node) const
{
	if (node == GNULL)
	{
		return GNULL;
	}
	return node->m_pNext;
}

template<typename T, typename NodeT>
GINLINE NodeT *GDList<T, NodeT>::GetNodeAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename T, typename NodeT>
GINLINE const NodeT *GDList<T, NodeT>::GetNodeAt(gsize pos) const
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
GINLINE T &GDList<T, NodeT>::GetFirstValue()
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename T, typename NodeT>
GINLINE const T &GDList<T, NodeT>::GetFirstValue() const
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename T, typename NodeT>
GINLINE T &GDList<T, NodeT>::GetLastValue()
{
	GASSERT(m_pLast);
	return m_pLast->m_tData;
}

template<typename T, typename NodeT>
GINLINE const T &GDList<T, NodeT>::GetLastValue() const
{
	GASSERT(m_pLast);
	return m_pLast->m_tData;
}

template<typename T, typename NodeT>
GINLINE T& GDList<T, NodeT>::GetValueAt(gsize pos)
{
	NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename T, typename NodeT>
GINLINE const T &GDList<T, NodeT>::GetValueAt(gsize pos) const
{
	const NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename T, typename NodeT>
GINLINE gvoid GDList<T, NodeT>::SetValueAt(gsize pos, const T &data)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = data;
}

template<typename T, typename NodeT>
GINLINE gvoid GDList<T, NodeT>::SetValueAt(gsize pos, T &&data)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = GForward<T>(data);
}

template<typename T, typename NodeT>
GINLINE gsize GDList<T, NodeT>::FirstIndexOf(const T &data) const
{
	NodeT *node = m_pFirst;
	for (gsize i = 0; i < m_nSize; i++)
	{
		if (data == node->m_tData)
			return i;
		node = node->m_pNext;
	}
	return NULL_POS;
}

template<typename T, typename NodeT>
GINLINE gsize GDList<T, NodeT>::LastIndexOf(const T &data) const
{
	NodeT *node = m_pLast;
	for (gsize i = 0; i < m_nSize; i++)
	{
		if (data == node->m_tData)
			return i;
		node = node->m_pPrevious;
	}
	return NULL_POS;
}

template<typename T, typename NodeT>
GINLINE NodeT *GDList<T, NodeT>::Find(const T &data)
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

template<typename T, typename NodeT>
GINLINE const NodeT *GDList<T, NodeT>::Find(const T &data) const
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

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::AddFirst(const T &data)
{
	NodeT *pNewNode = new NodeT(data);
	pNewNode->m_pPrevious = GNULL;
	pNewNode->m_pNext = m_pFirst;
	if (GNULL != m_pFirst)
	{
		m_pFirst->m_pPrevious = pNewNode;
	}
	m_pFirst = pNewNode;
	if (GNULL == m_pLast)
	{
		m_pLast = pNewNode;
	}
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::AddFirst(T &&data)
{
	NodeT *pNewNode = new NodeT(GForward<T>(data));
	pNewNode->m_pPrevious = GNULL;
	pNewNode->m_pNext = m_pFirst;
	if (GNULL != m_pFirst)
	{
		m_pFirst->m_pPrevious = pNewNode;
	}
	m_pFirst = pNewNode;
	if (GNULL == m_pLast)
	{
		m_pLast = pNewNode;
	}
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::AddLast(const T &data)
{
	NodeT *pNewNode = new NodeT(data);
	pNewNode->m_pNext = GNULL;
	pNewNode->m_pPrevious = m_pLast;
	if (GNULL != m_pLast)
	{
		m_pLast->m_pNext = pNewNode;
	}
	m_pLast = pNewNode;
	if (GNULL == m_pFirst)
	{
		m_pFirst = pNewNode;
	}
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::AddLast(T &&data)
{
	NodeT *pNewNode = new NodeT(GForward<T>(data));
	pNewNode->m_pNext = GNULL;
	pNewNode->m_pPrevious = m_pLast;
	if (GNULL != m_pLast)
	{
		m_pLast->m_pNext = pNewNode;
	}
	m_pLast = pNewNode;
	if (GNULL == m_pFirst)
	{
		m_pFirst = pNewNode;
	}
	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::InsertBefore(gsize pos, const T &data)
{
	if (GNULL == m_pFirst || 0 == pos)
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
	pNewNode->m_pNext = pTmpNode;
	pNewNode->m_pPrevious = pTmpNode->m_pPrevious;

	pTmpNode->m_pPrevious->m_pNext = pNewNode;
	pTmpNode->m_pPrevious = pNewNode;

	if (GNULL == pNewNode->m_pNext)
	{
		m_pLast = pNewNode;
	}

	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::InsertBefore(gsize pos, T &&data)
{
	if (GNULL == m_pFirst || 0 == pos)
	{
		return AddFirst(GForward<T>(data));
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	NodeT *pNewNode = new NodeT(GForward<T>(data));
	pNewNode->m_pNext = pTmpNode;
	pNewNode->m_pPrevious = pTmpNode->m_pPrevious;

	pTmpNode->m_pPrevious->m_pNext = pNewNode;
	pTmpNode->m_pPrevious = pNewNode;

	if (GNULL == pNewNode->m_pNext)
	{
		m_pLast = pNewNode;
	}

	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::InsertBefore(NodeT *node, const T &data)
{
	GASSERT(node && m_pFirst && m_pLast);
	NodeT *pNewNode = new NodeT(data);
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
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::InsertBefore(NodeT *node, T &&data)
{
	GASSERT(node && m_pFirst && m_pLast);
	NodeT *pNewNode = new NodeT(GForward<T>(data));
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
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::InsertAfter(gsize pos, const T &data)
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
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pNewNode->m_pPrevious = pTmpNode;
	pTmpNode->m_pNext = pNewNode;

	if (GNULL == pNewNode->m_pNext)
	{
		m_pLast = pNewNode;
	}
	else
	{
		pNewNode->m_pNext->m_pPrevious = pNewNode;
	}

	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::InsertAfter(gsize pos, T &&data)
{
	if (GNULL == m_pFirst)
	{
		return AddFirst(GForward<T>(data));
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	NodeT *pNewNode = new NodeT(GForward<T>(data));
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pNewNode->m_pPrevious = pTmpNode;
	pTmpNode->m_pNext = pNewNode;

	if (GNULL == pNewNode->m_pNext)
	{
		m_pLast = pNewNode;
	}
	else
	{
		pNewNode->m_pNext->m_pPrevious = pNewNode;
	}

	++m_nSize;
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::InsertAfter(NodeT *node, const T &data)
{
	GASSERT(node && m_pFirst && m_pLast);
	NodeT *pNewNode = new NodeT(data);
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
	return pNewNode;
}

template<typename T, typename NodeT> GINLINE
NodeT *GDList<T, NodeT>::InsertAfter(NodeT *node, T &&data)
{
	GASSERT(node && m_pFirst && m_pLast);
	NodeT *pNewNode = new NodeT(GForward<T>(data));
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
	return pNewNode;
}

template<typename T, typename NodeT>
GINLINE gvoid GDList<T, NodeT>::Remove(const NodeT *node)
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
		m_pFirst = GNULL;
	}

	if (node->m_pNext)
	{
		node->m_pNext->m_pPrevious = node->m_pPrevious;
	}
	else
	{
		m_pLast = GNULL;
	}

	delete node;
	--m_nSize;
}

template<typename T, typename NodeT>
GINLINE gvoid GDList<T, NodeT>::RemoveAt(gsize pos, T *data)
{
	GASSERT(pos < m_nSize);

	if (0 == pos)
	{
		// 头指针
		return RemoveFirst(data);
	}
	else if (pos == m_nSize - 1)
	{
		// 尾指针
		return RemoveLast(data);
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

	if (data)
	{
		// 将元素移走，而非拷贝
		*data = GMove(pTmpNode->m_tData);
	}
	delete pTmpNode;
	pTmpNode = GNULL;

	--m_nSize;
}

template<typename T, typename NodeT>
GINLINE gvoid GDList<T, NodeT>::RemoveFirst(T *data)
{
	if (!m_pFirst)
	{
		return;
	}

	NodeT *pTmpNode = m_pFirst;

	m_pFirst = m_pFirst->m_pNext;
	if (m_pFirst)
	{
		m_pFirst->m_pPrevious = GNULL;
	}
	else
	{
		m_pLast = GNULL;
	}
	if (data)
	{
		// 将元素移走，而非拷贝
		*data = GMove(pTmpNode->m_tData);
	}
	delete pTmpNode;
	pTmpNode = GNULL;
	--m_nSize;
}

template<typename T, typename NodeT>
GINLINE gvoid GDList<T, NodeT>::RemoveLast(T *data)
{
	if (!m_pLast)
	{
		return;
	}

	NodeT *pTmpNode = m_pLast;
	m_pLast = m_pLast->m_pPrevious;
	if (m_pLast)
	{
		m_pLast->m_pNext = GNULL;
	}
	else
	{
		m_pFirst = GNULL;
	}
	if (data)
	{
		// 将元素移走，而非拷贝
		*data = GMove(pTmpNode->m_tData);
	}
	delete pTmpNode;
	pTmpNode = GNULL;
	--m_nSize;
}

template<typename T, typename NodeT>
GINLINE gvoid GDList<T, NodeT>::RemoveAll()
{
	NodeT *node = m_pFirst;
	NodeT *next_node = GNULL;
	while (node)
	{
		next_node = node->m_pNext;
		delete node;
		node = next_node;
	}

	m_pFirst = GNULL;
	m_pLast = GNULL;
	m_nSize = 0;
}

template<typename T, typename NodeT>
GINLINE gvoid GDList<T, NodeT>::Invert()
{
	if (m_nSize <= 1) return;

	NodeT *tmpNod = GNULL, *curNod = m_pFirst, *nextNod = GNULL;
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

template<typename T, typename NodeT>
GINLINE gsize GDList<T, NodeT>::IndexOfCircle() const
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

template<typename T, typename NodeT>
NodeT *GDList<T, NodeT>::FindCircle()
{
	if (0 == m_nSize)
	{
		return GNULL;
	}

	NodeT* p1 = m_pFirst;
	NodeT* p2 = m_pFirst;

	// 判断链表是否有环，当p1=p2时说明链表有环，程序跳出循环。如果p2一直走到链表尽头则说明没有环。
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

	// 求出环的起点节点，并将其返回
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}
	return p1;
}

template<typename T, typename NodeT>
const NodeT *GDList<T, NodeT>::FindCircle() const
{
	if (0 == m_nSize)
	{
		return GNULL;
	}

	const NodeT* p1 = m_pFirst;
	const NodeT* p2 = m_pFirst;

	// 判断链表是否有环，当p1=p2时说明链表有环，程序跳出循环。如果p2一直走到链表尽头则说明没有环。
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

	// 求出环的起点节点，并将其返回
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}
	return p1;
}

template<typename T, typename NodeT>
GINLINE gsize GDList<T, NodeT>::IndexOfCross(const GLinkedList<T, NodeT> &list)
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

	m_pLast->m_pNext = GNULL;
	m_nSize -= list.Size();
	return i;
}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT> &GDList<T, NodeT>::operator+=(const GDList<T, NodeT> &list)
{
	if (list.IsEmpty())
	{
		return *this;
	}

	if (IsEmpty())
	{
		// 直接调用拷贝运算符
		return this->operator=(list);
	}

	NodeT *new_node = GNULL;
	const NodeT *node = list.m_pLast;
	while (node)
	{
		new_node = new NodeT(node->m_tData);
		m_pLast->m_pNext = new_node;
		m_pLast = new_node;

		node = node->m_pNext;
		m_nSize++;
	}
	return *this;
}

template<typename T, typename NodeT>
GINLINE GDList<T, NodeT> &GDList<T, NodeT>::operator+=(GDList<T, NodeT> &&list)
{
	if (list.IsEmpty())
	{
		return *this;
	}

	if (IsEmpty())
	{
		// 直接调用移动运算符
		return this->operator=(GForward<GDList<T, NodeT>>(list));
	}

	// 将list衔接到当且链表的后面
	m_nSize += list.m_nSize;
	m_pLast->m_pNext = list.m_pFirst;
	m_pLast = list.m_pLast;

	list.m_nSize = 0;
	list.m_pFirst = GNULL;
	list.m_pLast = GNULL;
	return *this;
}

} // namespace gsystem

#endif // _CORE_DOUBLE_LINKED_LIST_INLINE_