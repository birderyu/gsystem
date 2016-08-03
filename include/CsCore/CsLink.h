#ifndef _CSCORE_LINK_H_
#define _CSCORE_LINK_H_

#include "CsObject.h"

template<typename T>
class CsLinkNode
{
public:
	CsLinkNode();
	CsLinkNode(const T &t);

private:
	CsLinkNode<T> *m_pPrior;
	CsLinkNode<T> *m_pNext;
	T m_tData;
};


template <typename T>
class CsLink :public CsObject
{
public:
	CsLink();

private:
	T m_tData;
	CsLink *m_pLast;
	CsLink *m_pNext;
};

template<typename T>
CsLinkNode<T>::CsLinkNode()
: m_tData(T()), m_pPrior(NULL), m_pNext(NULL)
{

}

template<typename T>
CsLinkNode<T>::CsLinkNode(const T &t) 
: m_tData(t), m_pPrior(NULL), m_pNext(NULL)
{

}

#endif // _CSCORE_LINK_H_