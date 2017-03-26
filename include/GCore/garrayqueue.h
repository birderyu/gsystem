// 使用数组实现的队列
#ifndef _CORE_ARRAY_QUEUE_H_
#define _CORE_ARRAY_QUEUE_H_

#include "gqueue.h"
#include "gdynamicarray.h"

namespace gsystem { // gsystem

template <typename DataT>
class GArrayQueue
	: public GQueue<DataT>
{
public:
	//构造函数
	GArrayQueue(gsize capacity)
		: m_nFront(0)
		, m_nRear(0)
		, m_tArray(capacity)
	{
		
	}
	//析构函数
	~GArrayQueue()
	{
		
	}

	gbool IsEmpty() const;
	int Size();         //队列的大小

	gvoid Clear();
	gvoid Dispose();

	DataT front();          //队首元素
	bool pop();         //出对
	bool push(T t);     //入队
	

private:
	gsize m_nFront; // 队首
	gsize m_nRear;	// 队尾
	GDynamicArray<DataT> m_tArray;
};

} // namespace gsystem

#include "garrayqueue.inl"

#endif // _CORE_ARRAY_QUEUE_H_
