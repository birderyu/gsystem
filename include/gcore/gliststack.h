/// 链表实现的栈
#ifndef _CORE_LIST_STACK_H_
#define _CORE_LIST_STACK_H_

#include "gstack.h"
#include "gdlist.h"

namespace gsystem { // gsystem

template<typename T>
class GListStack 
	: public GStack<T>
{
public:
	GListStack();
	GListStack(const GListStack<T> &stack);
	GListStack(GListStack<T> &&stack);
	GListStack<T>& operator=(const GListStack<T> &stack);
	GListStack<T>& operator=(GListStack<T> &&stack);

public:
	gsize Size() const;
	gbool IsEmpty() const;

	gvoid Clear();
	gvoid Destroy();

	gvoid Push(const T &value);
	gvoid Push(T &&value);

	gbool Pop(T *value = GNULL);

	const T &Top() const;
	T &Top();

private:
	GDList<T> m_tList;
};

} // namespace gsystem

#include "inline/gliststack.inl"

#endif // _CORE_LIST_STACK_H_
