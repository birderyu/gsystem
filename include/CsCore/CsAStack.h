/// 数组实现的栈

#ifndef _CSCORE_ARRAY_STACK_H_
#define _CSCORE_ARRAY_STACK_H_

#include <assert.h> 

const int EmptyTOS = -1;
const int MinStackSize = 5;
const int MaxStackSize = 500;

template<typename T>
class CsAStack
{
public:
	CsAStack(int maxsize = MaxStackSize);
	CsAStack(const CsAStack<T>& other);
	CsAStack<T>& operator=(const CsAStack<T>& other);
	~CsAStack();
public:
	int IsEmpty() const;
	cs_void MakeEmpty();
	int GetCount() const;
	int IsFull();
	int Resize(int newmaxsize);//change the capacity. 
	int Push(const T& data);
	int Pop(T *data = NULL);
	int Top(T *data) const;
private:
	cs_void DisposeStack();//释放数组所占的内存，即栈被销毁. 
private:
	int capacity;
	int tos;//Top of stack for now. 
	T* array;
};

template<typename T>
inline CsAStack<T>::CsAStack(int maxsize) :capacity(maxsize), tos(EmptyTOS), array(NULL)
{
	ASSERT(capacity >= MinStackSize);

	try
	{
		array = new T[capacity];
	}
	catch (std::bad_alloc&)
	{
	}
}

template<typename T>
inline CsAStack<T>::CsAStack(const CsAStack<T>& other) :capacity(other.capacity), tos(other.tos), array(NULL)
{
	try
	{
		array = new T[capacity];
	}
	catch (std::bad_alloc&)
	{
	}
	if (tos >= 0 && tos < capacity)
	{
		for (i = 0; i <= tos; i++)
		{
			array[i] = other.array[i];
		}
	}
}

template<typename T>
inline CsAStack<T>& CsAStack<T>::operator=(const CsAStack<T>& other)
{
	if (this == &other)
	{
		return *this;
	}
	if (array != NULL)
	{
		delete[] array;
	}

	capacity = other.capacity;
	tos = other.tos;
	if (tos >= 0 && tos < capacity)
	{
		for (i = 0; i <= tos; i++)
		{
			array[i] = other.array[i];
		}
	}

	return *this;
}


template<typename T>
inline CsAStack<T>::~CsAStack()
{

	DisposeStack();
}

template<typename T>
inline cs_void CsAStack<T>::DisposeStack()
{
	capacity = 0;
	tos = EmptyTOS;
	if (array)
	{
		delete[] array;
	}
}

template<typename T>
inline int CsAStack<T>::IsEmpty() const
{
	return EmptyTOS == tos;
}


template<typename T>
inline cs_void CsAStack<T>::MakeEmpty()
{
	tos = EmptyTOS;
}

template<typename T>
inline int CsAStack<T>::GetCount() const
{
	return tos + 1;
}

template<typename T>
inline int CsAStack<T>::IsFull()
{
	return tos >= capacity - 1;
}

template<typename T>
inline int CsAStack<T>::Resize(int newmaxsize)
{
	DisposeStack();
	capacity = newmaxsize;
	tos = EmptyTOS;
	try
	{
		array = new T[newmaxsize];
	}
	catch (std::bad_alloc&)
	{
		return 0;
	}
	return 1;
}

template<typename T>
inline int CsAStack<T>::Push(const T& data)
{
	if (IsFull())
	{
		return 0;
	}
	else
	{
		array[++tos] = data;
		return 1;
	}
}

template<typename T>
inline int CsAStack<T>::Pop(T* data = NULL)
{
	if (IsEmpty())
	{
		return 0;
	}
	else
	{
		if (data)
		{
			*data = array[tos];
		}
		--tos;
		return 1;
	}
}


template<typename T>
inline int CsAStack<T>::Top(T* data) const
{
	if (IsEmpty())
	{
		return 0;
	}
	else
	{
		*data = array[tos];
		return 1;
	}
}


#endif // _CSCORE_ARRAY_STACK_H_