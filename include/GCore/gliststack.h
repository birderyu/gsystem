/// 链表实现的栈
#ifndef _CORE_LIST_STACK_H_
#define _CORE_LIST_STACK_H_

#include "gstack.h"
#include "gdoublelinkedlist.h"

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

	gbool Push(const DataT &data);
	gbool Push(DataT &&data);

	gbool Pop(DataT *data = GNULL);

	const DataT &Top() const;
	DataT &Top();
	const DataT &Bottom() const;
	DataT &Bottom();

private:
	GDoubleLinkedList<DataT> m_tList;
};

#include "gliststack.inl"

#endif // _CORE_LIST_STACK_H_
