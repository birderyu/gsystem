/// 数组实现的栈
#ifndef _CORE_ARRAY_STACK_H_
#define _CORE_ARRAY_STACK_H_

#include "gstack.h"
#include "gdynamicarray.h"

namespace gsystem { // gsystem

template<typename DataT>
class GArrayStack 
	: public GStack<DataT>
{
public:
	GArrayStack(gsize capacity = 0);
	GArrayStack(const GArrayStack<DataT> &stack);
	GArrayStack(GArrayStack<DataT> &&stack);
	GArrayStack<DataT>& operator=(const GArrayStack<DataT> &stack);
	GArrayStack<DataT>& operator=(GArrayStack<DataT> &&stack);

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
	gsize Capacity() const;
	gvoid Reserve(gsize capacity);
	gbool Fill() const;

private:
	GDynamicArray<DataT> m_tArray;

	// 栈顶指针
	gsize m_TopCursor;
};

} // namespace gsystem

#include "garraystack.inl"

#endif // _CORE_ARRAY_STACK_H_
