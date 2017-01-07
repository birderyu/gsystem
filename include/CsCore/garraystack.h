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
	GArrayStack(const GArrayStack<DataT>& other);
	GArrayStack<DataT>& operator=(const GArrayStack<DataT>& other);
	~GArrayStack();

public:
	gbool IsEmpty() const;
	gvoid Clear();
	gsize Size() const;
	gbool IsFull() const;
	gbool Resize(gsize capacity);
	gbool Push(const DataT& data);
	gbool Pop(DataT *data = NULL);
	gbool Top(DataT &data) const;

	// 销毁栈
	gvoid Dispose();

private:
	GDynamicArray<DataT> m_tArray;

	// 栈顶指针
	gsize m_TopCursor;
};

#include "garraystack.inl"

#undef G_STACK_DEFAULT_CAPACITY

#endif // _CSCORE_ARRAY_STACK_H_