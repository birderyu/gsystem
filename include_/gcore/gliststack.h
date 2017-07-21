/// 链表实现的栈
#ifndef _CORE_LIST_STACK_H_
#define _CORE_LIST_STACK_H_

#include "gstack.h"
#include "gdlist.h"

namespace gsystem { // gsystem

template<typename DataT>
class GListStack 
	: public GStack<DataT>
{
public:
	GListStack();
	GListStack(const GListStack<DataT> &stack);
	GListStack(GListStack<DataT> &&stack);
	GListStack<DataT>& operator=(const GListStack<DataT> &stack);
	GListStack<DataT>& operator=(GListStack<DataT> &&stack);

public:
	gsize Size() const;
	gbool IsEmpty() const;

	gvoid Clear();
	gvoid Destroy();

	gvoid Push(const DataT &data);
	gvoid Push(DataT &&data);

	gvoid Pop(DataT *data = GNULL);

	const DataT &Top() const;
	DataT &Top();

private:
	GDList<DataT> m_tList;
};

} // namespace gsystem

#include "inline/gliststack.inl"

#endif // _CORE_LIST_STACK_H_
