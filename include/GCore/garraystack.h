/// 数组实现的栈
#ifndef _CORE_ARRAY_STACK_H_
#define _CORE_ARRAY_STACK_H_

#include "gstack.h"
#include "gdynamicarray.h"

#define G_STACK_DEFAULT_CAPACITY 1024

template<typename DataT>
class GArrayStack 
	: public GStack<DataT>
{
public:
	GArrayStack(gsize capacity = G_STACK_DEFAULT_CAPACITY);
	GArrayStack(const GArrayStack<DataT> &stack);
	GArrayStack(GArrayStack<DataT> &&stack);
	GArrayStack<DataT>& operator=(const GArrayStack<DataT> &stack);
	GArrayStack<DataT>& operator=(GArrayStack<DataT> &&stack);
	~GArrayStack();

public:
	gbool IsEmpty() const;
	gvoid Clear();
	gsize Size() const;
	gbool IsFull() const;
	gbool Resize(gsize capacity);
	gbool Push(const DataT &data);
	gbool Push(DataT &&data);
	gbool Pop(DataT *data = GNULL);
	const DataT &Top() const;
	DataT &Top();
	const DataT &Bottom() const;
	DataT &Bottom();

	// 销毁栈
	gvoid Dispose();

private:
	GDynamicArray<DataT> m_tArray;

	// 栈顶指针
	gsize m_TopCursor;
};

#include "garraystack.inl"

#undef G_STACK_DEFAULT_CAPACITY

#endif // _CORE_ARRAY_STACK_H_
