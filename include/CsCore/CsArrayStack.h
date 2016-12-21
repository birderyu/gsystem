/// 数组实现的栈
#ifndef _CORE_ARRAY_STACK_H_
#define _CORE_ARRAY_STACK_H_

#include "CsStack.h"
#include "CsDynamicArray.h"

#define CS_STACK_DEFAULT_CAPACITY 1024

template<typename DataT>
class CsArrayStack 
	: public CsStack<DataT>
{
public:
	CsArrayStack(cs_size_t capacity = CS_STACK_DEFAULT_CAPACITY);
	CsArrayStack(const CsArrayStack<DataT>& other);
	CsArrayStack<DataT>& operator=(const CsArrayStack<DataT>& other);
	~CsArrayStack();

public:
	cs_bool IsEmpty() const;
	cs_void Clear();
	cs_size_t Size() const;
	cs_bool IsFull() const;
	cs_bool Resize(cs_size_t capacity);
	cs_bool Push(const DataT& data);
	cs_bool Pop(DataT *data = NULL);
	cs_bool Top(DataT &data) const;

	// 销毁栈
	cs_void Dispose();

private:
	CsDynamicArray<DataT> m_tArray;

	// 栈顶指针
	cs_size_t m_TopCursor;
};

#include "CsArrayStack.inl"

#undef CS_STACK_DEFAULT_CAPACITY

#endif // _CSCORE_ARRAY_STACK_H_