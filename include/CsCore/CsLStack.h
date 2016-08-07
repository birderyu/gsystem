/// 链表实现的栈

#ifndef _CSCORE_LIST_STACK_H_
#define _CSCORE_LIST_STACK_H_

#include "CsSList.h"

template<typename T>
class CsLStack
{
public: //不需要自行定义copying函数，编译器自动的合成的版本工作正常：调用基类和各个数据成员的相应的copying函数。   
	CsLStack();
	CsLStack(const T& initdata);
	~CsLStack();
public:
	int IsEmpty() const;
	void MakeEmpty();//清空。     
	int GetCount() const;
	//void DisposeStack();//清空。对于用链表实现的Stack，这两个清空的含义相同，对于用数组实现的，两者含义不一样。     
	int Push(T data);
	int Pop(T *data = NULL);
	int Top(T *data) const;

private:
	CsSList<T> slist;
};

template<typename T>
inline CsLStack<T>::CsLStack() :slist()
{
}

template<typename T>
inline CsLStack<T>::CsLStack(const T& initdata) : slist(initdata)
{
}

template<typename T>
inline CsLStack<T>::~CsLStack()
{
}

template<typename T>
inline int CsLStack<T>::IsEmpty() const
{
	return slist.IsEmpty();
}

template<typename T>
inline void CsLStack<T>::MakeEmpty()
{
	slist.RemoveAll();
}

template<typename T>
inline int CsLStack<T>::GetCount() const
{
	return slist.GetCount();
}
/*template<typename T>
inline void Stack<T>::DisposeStack()
{
slist.RemoveAll();
}*/

template<typename T>
inline int CsLStack<T>::Push(T data)
{
	return slist.AddHead(data);
}

template<typename T>
inline int CsLStack<T>::Pop(T *data)
{
	if (IsEmpty())
		return 0;

	if (data)
		Top(data);

	slist.RemoveHead();
	return 1;
}

template<typename T>
inline int CsLStack<T>::Top(T *data) const
{
	ASSERT(data);

	if (IsEmpty())
		return 0;

	*data = slist.GetHead();
	return 1;
}

#endif // _CSCORE_LIST_STACK_H_