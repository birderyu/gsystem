/////////////////////////////////////////////////////////////////////////////////
/// @brief 双向链表（double linked list）
/// 
///  双向链表的定义及实现
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CSCORE_DOUBLE_LINKED_LIST_H_
#define _CSCORE_DOUBLE_LINKED_LIST_H_

/*dlist.h*/

#include <assert.h> 
#include <crtdbg.h> 

template<typename T>
class CsDList;

template<typename T>
struct CsDListNode
{
	T data;
	CsDListNode<T> *prior;
	CsDListNode<T> *next;
	CsDListNode() : data(T()), prior(NULL), next(NULL) {}
	CsDListNode(const T &initdata) : data(initdata), prior(NULL), next(NULL) {}
};

template<typename T>
class CsDList
{
	typedef CsDListNode<T> Node;

protected:
	int m_nCount;
	Node *m_pNodeHead;
	Node *m_pNodeTail;

public:
	CsDList();
	CsDList(const T &initdata);
	CsDList(const CsDList<T>& other);
	CsDList<T>& operator=(const CsDList<T>& other);
	~CsDList();

public:
	////插入或删除需要注意处理：插入节点本身的next 和prior,前一个节点的next,后一个节点的prior. 
	//注意在第一个节点或最后一个节点插入或删除时的特殊情况：前一个或后一个节点为NULL,而且注意移动m_pNodeHead或m_pNodeTail 
	cs_void    Invert();
	int     IsEmpty() const;
	int     GetCount() const;
	int     InsertBefore(const int pos, const T data);
	int     InsertAfter(const int pos, const T data);
	int     AddHead(const T data);
	int     AddTail(const T data);
	void    RemoveAt(const int pos);
	void    RemoveHead();
	void    RemoveTail();
	void    RemoveAll();
	T&      GetTail();
	T       GetTail() const;
	T&      GetHead();
	T       GetHead() const;
	T&      GetAt(const int pos);
	T       GetAt(const int pos) const;
	void    SetAt(const int pos, T data);
	int     Find(const T data) const;
	int     FindCircle() const;
	int     FindCross(CsDList& testlist);
	T&      GetPrev(int &pos);
	T&      GetNext(int &pos);
};

template<typename T>
inline CsDList<T>::CsDList() : m_nCount(0), m_pNodeHead(NULL), m_pNodeTail(NULL)
{
}

template<typename T>
inline CsDList<T>::CsDList(const T &initdata)
: m_nCount(0), m_pNodeHead(NULL), m_pNodeTail(NULL)
{
	AddHead(initdata);
}

template<typename T>
inline CsDList<T>::CsDList(const CsDList<T>& other)
: m_nCount(0), m_pNodeHead(NULL), m_pNodeTail(NULL)
{
	if (other.m_nCount > 0)
	{
		for (int i = 1; i <= other.m_nCount; i++)
		{
			AddTail(other.GetAt(i));
		}
	}
}


template<typename T>
inline CsDList<T>& CsDList<T>::operator=(const CsDList<T>& other)
{
	if (this == &other)
	{
		return *this;
	}
	if (m_nCount > 0)
	{
		RemoveAll();
	}

	if (other.m_nCount > 0)
	{
		for (int i = 1; i <= other.m_nCount; i++)
		{
			AddTail(other.GetAt(i));
		}
	}

	return *this;
}

template<typename T>
inline CsDList<T>::~CsDList()
{
	RemoveAll();
}

template<typename T>
inline void CsDList<T>::Invert()
{
	if (m_nCount <= 1) return;
	CsDListNode<T> *tmpNod, *curNod, *nextNod;
	curNod = m_pNodeHead;
	for (int i = 1; i <= m_nCount; i++)
	{
		nextNod = curNod->next;
		tmpNod = curNod->prior;
		curNod->prior = curNod->next;
		curNod->next = tmpNod;
		curNod = nextNod;
	}

	tmpNod = m_pNodeHead;
	m_pNodeHead = m_pNodeTail;
	m_pNodeTail = tmpNod;
	return;
}

//insert data before pos. 
template<typename T>
inline int CsDList<T>::InsertBefore(const int pos, const T data)
{
	int i;
	int nRetPos;
	CsDListNode<T> *pTmpNode;
	CsDListNode<T> *pNewNode;

	try
	{
		pNewNode = new CsDListNode<T>;
	}
	catch (std::bad_alloc&)
	{
		nRetPos = 0;
		return nRetPos;
	}

	pNewNode->data = data;

	// if the list is empty, replace the head node with the new node. 
	if (NULL == m_pNodeHead)
	{
		pNewNode->prior = NULL;
		pNewNode->next = NULL;
		m_pNodeHead = pNewNode;
		m_pNodeTail = pNewNode;
		nRetPos = 1;
		++m_nCount;
		return nRetPos;
	}

	// is pos range valid? 
	ASSERT(1 <= pos && pos <= m_nCount);

	// insert before head node? 
	if (1 == pos)
	{
		pNewNode->prior = NULL;
		pNewNode->next = m_pNodeHead;
		m_pNodeHead->prior = pNewNode;
		m_pNodeHead = pNewNode;
		nRetPos = 1;
		++m_nCount;
		return nRetPos;
	}

	// if the list is not empty and is not inserted before head node, 
	// seek to the pos of the list and insert the new node before it. 
	pTmpNode = m_pNodeHead;
	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}
	pNewNode->next = pTmpNode;
	pNewNode->prior = pTmpNode->prior;

	pTmpNode->prior->next = pNewNode;
	pTmpNode->prior = pNewNode;

	// if tail node, must update m_pNodeTail 
	if (NULL == pNewNode->next)
	{
		m_pNodeTail = pNewNode;
	}

	nRetPos = pos;

	++m_nCount;
	return nRetPos;
}
//insert data after pos 
template<typename T>
inline int CsDList<T>::InsertAfter(const int pos, const T data)
{
	int i;
	int nRetPos;
	CsDListNode<T> *pNewNode;
	CsDListNode<T> *pTmpNode;

	try
	{
		pNewNode = new CsDListNode<T>;
	}
	catch (std::bad_alloc&)
	{
		nRetPos = 0;
		return nRetPos;
	}

	pNewNode->data = data;

	// if the list is empty, replace the head node with the new node. 
	if (NULL == m_pNodeHead)
	{
		pNewNode->prior = NULL;
		pNewNode->next = NULL;
		m_pNodeHead = pNewNode;
		m_pNodeTail = pNewNode;
		nRetPos = 1;
		++m_nCount;
		return nRetPos;
	}

	// is pos range valid? 
	ASSERT(1 <= pos && pos <= m_nCount);

	// if the list is not empty, 
	// seek to the pos of the list and insert the new node after it. 
	pTmpNode = m_pNodeHead;
	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}

	pNewNode->next = pTmpNode->next;
	pNewNode->prior = pTmpNode;

	pTmpNode->next = pNewNode;
	//modified by myself   
	// if tail node, must update m_pNodeTail 
	if (NULL == pNewNode->next)
	{
		m_pNodeTail = pNewNode;
	}
	else
	{
		pNewNode->next->prior = pNewNode;
	}

	nRetPos = pos + 1;

	++m_nCount;
	return nRetPos;
}

template<typename T>
inline T& CsDList<T>::GetAt(const int pos)
{
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsDListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}

	return pTmpNode->data;
}

template<typename T>
inline T CsDList<T>::GetAt(const int pos) const
{
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsDListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}

	return pTmpNode->data;
}

template<typename T>
inline int CsDList<T>::AddHead(const T data)
{
	return InsertBefore(1, data);
}

template<typename T>
inline int CsDList<T>::AddTail(const T data)
{
	return InsertAfter(GetCount(), data);
}

template<typename T>
inline int CsDList<T>::IsEmpty() const
{
	return 0 == m_nCount;
}

template<typename T>
inline int CsDList<T>::GetCount() const
{
	return m_nCount;
}

template<typename T>
inline T& CsDList<T>::GetTail()
{
	ASSERT(0 != m_nCount);
	return m_pNodeTail->data;
}

template<typename T>
inline T CsDList<T>::GetTail() const
{
	ASSERT(0 != m_nCount);
	return m_pNodeTail->data;
}

template<typename T>
inline T& CsDList<T>::GetHead()
{
	ASSERT(0 != m_nCount);
	return m_pNodeHead->data;
}

template<typename T>
inline T CsDList<T>::GetHead() const
{
	ASSERT(0 != m_nCount);
	return m_pNodeHead->data;
}
//as its name, delete the data at pos 
template<typename T>
inline void CsDList<T>::RemoveAt(const int pos)
{
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsDListNode<T> *pTmpNode = m_pNodeHead;

	// head node? 
	if (1 == pos)
	{
		m_pNodeHead = m_pNodeHead->next;
		if (m_pNodeHead)
		{
			m_pNodeHead->prior = NULL;
		}

		delete pTmpNode;
		--m_nCount;
		if (0 == m_nCount)
		{
			m_pNodeTail = NULL;
		}

		return;
	}

	//otherwise... 
	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}
	pTmpNode->prior->next = pTmpNode->next;
	//last node? 
	if (pTmpNode->next)
	{
		pTmpNode->next->prior = pTmpNode->prior;
	}
	else
	{
		m_pNodeTail = pTmpNode->prior;
	}


	delete pTmpNode;
	--m_nCount;
	if (0 == m_nCount)
	{
		m_pNodeTail = NULL;
	}

	return;
}

template<typename T>
inline void CsDList<T>::RemoveHead()
{
	ASSERT(0 != m_nCount);
	RemoveAt(1);
}

template<typename T>
inline void CsDList<T>::RemoveTail()
{
	ASSERT(0 != m_nCount);
	RemoveAt(m_nCount);
}

template<typename T>
inline void CsDList<T>::RemoveAll()
{
	int i;
	int nCount;
	CsDListNode<T> *pTmpNode;

	nCount = m_nCount;
	for (i = 0; i < nCount; ++i)
	{
		pTmpNode = m_pNodeHead->next;
		delete m_pNodeHead;
		m_pNodeHead = pTmpNode;
	}
	m_pNodeHead = NULL;
	m_pNodeTail = NULL;
	m_nCount = 0;
}

template<typename T>
inline void CsDList<T>::SetAt(const int pos, T data)
{
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsDListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}
	pTmpNode->data = data;
}

template<typename T>
inline int CsDList<T>::Find(const T data) const
{
	int i;
	int nCount;
	CsDListNode<T> *pTmpNode = m_pNodeHead;

	nCount = m_nCount;
	for (i = 0; i < nCount; ++i)
	{
		if (data == pTmpNode->data)
			return i + 1;
		pTmpNode = pTmpNode->next;
	}

	return 0;
}

/*判断链表是否有环，如果有环则返回环的首结点位置，否则返回0*/
template<typename T>
inline int CsDList<T>::FindCircle() const
{
	if (0 == m_nCount)
	{
		return 0;
	}

	CsDListNode<T>* p1 = m_pNodeHead;
	CsDListNode<T>* p2 = m_pNodeHead;

	/*判断链表是否有环，当p1=p2时说明链表有环，程序跳出循环。如果p2一直走到链表尽头则说明没有环。*/
	do{
		if (p1 != NULL&&p2 != NULL&&p2->next != NULL)
		{
			p1 = p1->next;
			p2 = p2->next->next;
		}
		else
			return 0;
	} while (p1 != p2);

	/*求出环的起点节点，并将其返回*/
	p2 = m_pNodeHead;
	while (p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}

	int i;
	p2 = m_pNodeHead;
	for (i = 1; i <= m_nCount; i++)
	{
		if (p1 == p2) break;
		p2 = p2->next;
	}
	return i;

}

/*判断两个链表是否交叉，如果交叉返回首个交叉节点位置（在本链表中的位置，而不是testlist中的位置），否则返回0。
假定：这两个链表本身均无环*/
template<typename T>
inline int CsDList<T>::FindCross(CsDList& testlist)
{
	if (0 == m_nCount || 0 == testlist.m_nCount)
	{
		return 0;
	}

	if (FindCircle() || testlist.FindCircle())
	{
		return 0;
	}

	/*将第二个链表接在第一个链表后面*/
	CsDListNode<T>* pTail = m_pNodeHead;
	for (int i = 1; i < m_nCount; i++)
	{
		pTail = pTail->next;
	}

	pTail = testlist.m_pNodeHead;
	m_nCount += testlist.m_nCount;

	int i = FindCircle();

	pTail = NULL;
	m_nCount -= testlist.m_nCount;
	return i;

}
//get the data at pos and let pos=pos+1   
template<typename T>
inline T& CsDList<T>::GetNext(int &pos)
{
	ASSERT(0 != m_nCount);
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsDListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}

	++pos;

	return pTmpNode->data;
}

//get the data at pos and let pos=pos-1 
template<typename T>
inline T& CsDList<T>::GetPrev(int &pos)
{
	ASSERT(0 != m_nCount);
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsDListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}

	--pos;

	return pTmpNode->data;
}

#endif // _CSCORE_DOUBLE_LINKED_LIST_H_