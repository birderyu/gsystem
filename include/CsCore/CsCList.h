#ifndef _CSCORE_CIRCULAR_LINK_H_
#define _CSCORE_CIRCULAR_LINK_H_

#include "CsSList.h" 

/*一般而言，将循环链表继承自单向链表，会有一些问题的：
1.作为基类的单向链表的析构函数应该为虚函数，因为作为有多态性质的基类的析构函数必须是virtual的；
2.循环列表中重定义了函数RemoveAt，一般情况下绝对不应该重定义基类中的非虚函数的，因为会导致精神分裂症：通过指向或应用循环列表
的基类指针或引用来调用该函数时，会调用基类中RemoveAt，而通过循环列表本身或指向或引用它的派生类指针或引用调用该函数时，会调用
派生类中的RemoveAt。
但是，如果不适用多态性质，也就是不通过基类的指针或引用来操纵派生类对象的情况下，上述两个问题是不会爆发出来的！*/


template<typename T>
class CList : public CsSList<T>
{
protected:
	Node *m_pNodeCurr;

public:
	CList();

public:
	T&      GetNext();
	void    RemoveAt(const int pos);
	int     GetCurrentIndex() const;
};


template<typename T>
inline CList<T>::CList() : m_pNodeCurr(NULL)
{
}

/*这个函数很重要。循环链表是概念上的，实际上链表的最后一个节点并未指向其头节点。循环链表的概念是靠该函数来实施的。
如果当前节点为NULL或者当前节点为最后一个节点，则将其调整为指向头节点，否则将其向后移动一个节点；
然后返回当前节点的数据。*/
template<typename T>
inline T& CList<T>::GetNext()
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
inline int CList<T>::GetCurrentIndex() const
{
	ASSERT(0 != m_nCount);

	int i;
	CsSListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i <= m_nCount; ++i)
	{
		if (pTmpNode == m_pNodeCurr)
			return i;
		else
			pTmpNode = pTmpNode->next;
	}

	return 0;
}

//删除一个节点，就让当前节点指向其前一个节点；如果删除的是头节点，则应将当前节点置为NULL。 
//这个函数似乎专为解决约瑟夫问题而设计的。 
template<typename T>
inline void CList<T>::RemoveAt(const int pos)
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
		pTmpNode1 = pTmpNode1->next;
	}
	pTmpNode2->next = pTmpNode1->next;

	// added for loop list 
	m_pNodeCurr = pTmpNode2;

	delete pTmpNode1;
	--m_nCount;
	return;
}

#endif // _CSCORE_CIRCULAR_LINK_H_