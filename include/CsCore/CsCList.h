/////////////////////////////////////////////////////////////////////////////////
/// @brief 循环链表（circular linked list）
/// 
///  循环链表的定义及实现
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_CIRCULAR_LINKED_LIST_H_
#define _CORE_CIRCULAR_LINKED_LIST_H_

#include "CsSList.h" 

template<typename T>
class CsCList : public CsSList<T>
{
protected:
	Node *m_pNodeCurr;

public:
	CsCList();

public:
	T& GetNext();
	void RemoveAt(const cs_int pos);
	int GetCurrentIndex() const;
};


template<typename T>
inline CsCList<T>::CsCList() : m_pNodeCurr(NULL)
{
}

/*这个函数很重要。循环链表是概念上的，实际上链表的最后一个节点并未指向其头节点。循环链表的概念是靠该函数来实施的。
如果当前节点为NULL或者当前节点为最后一个节点，则将其调整为指向头节点，否则将其向后移动一个节点；
然后返回当前节点的数据。*/
template<typename T>
inline T& CsCList<T>::GetNext()
{
	ASSERT(0 != m_nCount);

	if ((NULL == m_pNodeCurr) || (NULL == m_pNodeCurr->next))
		m_pNodeCurr = m_pNodeHead;
	else
		m_pNodeCurr = m_pNodeCurr->next;

	return m_pNodeCurr->data;
}


//返回当前节点的位置。 
template<typename T>
inline int CsCList<T>::GetCurrentIndex() const
{
	ASSERT(0 != m_nCount);

	int i;
	CsSListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i <= m_nCount; ++i)
	{
		if (pTmpNode == m_pNodeCurr)
			return i;
		else
			pTmpNode = pTmpNode->m_pNext;
	}

	return 0;
}

//删除一个节点，就让当前节点指向其前一个节点；如果删除的是头节点，则应将当前节点置为NULL。 
//这个函数似乎专为解决约瑟夫问题而设计的。 
template<typename T>
inline void CsCList<T>::RemoveAt(const int pos)
{
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsSListNode<T> *pTmpNode1;
	CsSListNode<T> *pTmpNode2;

	pTmpNode1 = m_pNodeHead;

	// head node? 
	if (1 == pos)
	{
		m_pNodeHead = m_pNodeHead->next;

		// added for loop list 
		// m_pNodeCurr will be set to m_pNodeHead in function GetNext() 
		m_pNodeCurr = NULL;

		delete pTmpNode1;
		--m_nCount;
		return;
	}

	for (i = 1; i < pos; ++i)
	{
		// we will get the previous node of the target node after 
		// the for loop finished, and it would be stored into pTmpNode2 
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pTmpNode2->m_pNext = pTmpNode1->m_pNext;

	// added for loop list 
	m_pNodeCurr = pTmpNode2;

	delete pTmpNode1;
	--m_nCount;
	return;
}

#endif // _CORE_CIRCULAR_LINKED_LIST_H_