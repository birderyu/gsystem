/// 数组实现的栈
#ifndef _CORE_ARRAY_STACK_H_
#define _CORE_ARRAY_STACK_H_

#include "CsStack.h"
#include "CsDynamicArray.h"

const cs_int EmptyTOS = -1;
const cs_size_t MinStackSize = 5;
const cs_size_t MaxStackSize = 500;

template<typename DataT>
class CsArrayStack 
	: public CsStack<DataT>
{
public:
	CsArrayStack(cs_size_t capacity = MaxStackSize);
	CsArrayStack(const CsArrayStack<DataT>& other);
	CsArrayStack<DataT>& operator=(const CsArrayStack<DataT>& other);
	~CsArrayStack();

public:
	cs_int IsEmpty() const;
	cs_void Clear();
	cs_size_t Size() const;
	cs_bool IsFull();
	cs_bool Resize(cs_size_t capacity);//change the capacity. 
	cs_bool Push(const DataT& data);
	cs_bool Pop(DataT *data = NULL);
	cs_bool Top(DataT &data) const;

	// 销毁栈
	cs_void Dispose();

private:
	CsDynamicArray<DataT> m_tArray;

	// 栈顶指针
	cs_int m_TopCursor;
};

#include "CsArrayStack.inl"

#endif // _CSCORE_ARRAY_STACK_H_