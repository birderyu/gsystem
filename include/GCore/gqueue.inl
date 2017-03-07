#ifndef _CORE_QUEUE_INLINE_
#define _CORE_QUEUE_INLINE_

template<typename DataT>
GINLINE GQueue<DataT>::~GQueue()
{

}

template<typename DataT>
GINLINE gbool GQueue<DataT>::Add(const DataT &data)
{
	return EnQueue(data);
}

template<typename DataT>
GINLINE gbool GQueue<DataT>::Add(DataT &&data)
{
	return EnQueue(GForward<DataT>(data));
}

template<typename DataT>
GINLINE gbool GQueue<DataT>::Remove(DataT *data)
{
	return DeQueue(data);
}

#endif // _CORE_QUEUE_INLINE_