/// 链表实现的栈
#ifndef _CORE_LIST_STACK_H_
#define _CORE_LIST_STACK_H_

#include "CsStack.h"
#include "CsSingleLinkedList.h"

template<typename DataT>
class CsListStack 
	: public CsStack<DataT>
{
public:   
	CsListStack();
	CsListStack(const DataT&);
	~CsListStack();

public:
	cs_bool IsEmpty() const;
	cs_void Clear();//清空。     
	cs_size_t Size() const;
	cs_void Dispose();
	cs_bool Push(const DataT& data);
	cs_bool Pop(DataT *data = NULL);
	cs_bool Top(DataT &data) const;

private:
	CsSingleLinkedList<DataT> m_tList;
};

#include "CsListStack.inl"

#endif // _CSCORE_LIST_STACK_H_