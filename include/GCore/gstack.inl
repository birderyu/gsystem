#ifndef _CORE_STACK_INLINE_
#define _CORE_STACK_INLINE_

template<typename DataT>
GINLINE GStack<DataT>::~GStack()
{

}

template<typename DataT>
GINLINE gbool GStack<DataT>::Add(const DataT &data)
{
	return Push(data);
}

template<typename DataT>
GINLINE gbool GStack<DataT>::Add(DataT &&data)
{
	return Push(GForward<DataT>(data));
}

template<typename DataT>
GINLINE gbool GStack<DataT>::Remove(DataT *data)
{
	return Pop(data);
}

#endif // _CORE_STACK_INLINE_
