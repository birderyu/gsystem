/// 链表实现的栈
#ifndef _CORE_LIST_STACK_H_
#define _CORE_LIST_STACK_H_

#include "gstack.h"
#include "gsinglelinkedlist.h"

template<typename DataT>
class GListStack 
	: public GStack<DataT>
{
public:   
	GListStack();
	GListStack(const DataT&);
	~GListStack();

public:
	gbool IsEmpty() const;
	gvoid Clear();//清空。     
	gsize Size() const;
	gvoid Dispose();
	gbool Push(const DataT& data);
	gbool Pop(DataT *data = NULL);
	gbool Top(DataT &data) const;

private:
	GSingleLinkedList<DataT> m_tList;
};

#include "gliststack.inl"

#endif // _CSCORE_LIST_STACK_H_