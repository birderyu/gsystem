#ifndef _CORE_ARRAYS_INLINE_
#define _CORE_ARRAYS_INLINE_

#include "gallocator.h"
#include "gconstructor.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace arrays { // gsystem.detail.arrays

/// T具有内置的构造函数，无需构造，仅分配内存
template <typename T> GINLINE 
T *_GArrayCreate(gsize size, GTrueType) GEXCEPT(false)
{
	/// 创建结束不需要构造
	return GAllocate<T>(size);
}

/// T不具有内置的构造函数，分配内存之后，依次调用元素的构造函数
template <typename T> GINLINE 
T *_GArrayCreate(gsize size, GFalseType) GEXCEPT(false)
{
	T *arr = GAllocate<T>(size);
	for (gsize i = 0; i < size; i++)
	{
		GDefaultConstruct<T>(arr + i);
	}
	return arr;
}

/// T是内置类型，直接使用内存拷贝操作完成拷贝处理逻辑
template <typename T> GINLINE 
T *_GArrayCreate(const T *copy_arr, gsize copy_start, gsize copy_size, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(copy_size);
	GMemCopy(new_arr, copy_arr + copy_start, sizeof(T) * copy_size);
	return new_arr;
}

/// T不是内置类型，调用拷贝操作构造函数处理
template <typename T> GINLINE 
T *_GArrayCreate(const T *copy_arr, gsize copy_start, gsize copy_size, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(copy_size);
	for (gsize i = 0; i < copy_size; i++)
	{
		GCopyConstruct<T>(new_arr + i, copy_arr[i + copy_start]);
	}
	return new_arr;
}

/// T是内置类型，直接使用内存拷贝操作完成拷贝处理逻辑，其余元素无需构造，仅分配内存
template <typename T> GINLINE 
T *_GArrayCreate(gsize size, gsize start, const T *copy_arr, gsize copy_start, gsize copy_size, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size);
	gsize new_copy_size = size - start;
	gsize real_copy_size = copy_size < new_copy_size ? copy_size : new_copy_size;
	GMemCopy(new_arr + start, copy_arr + copy_start, sizeof(T) * real_copy_size);
	return new_arr;
}

/// T不是内置类型，调用拷贝操作构造函数处理
template <typename T> GINLINE 
T *_GArrayCreate(gsize size, gsize start, const T *copy_arr, gsize copy_start, gsize copy_size, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size);
	gsize new_copy_size = size - start;

	for (gsize i = 0; i < start; i++)
	{
		GDefaultConstruct<T>(new_arr + i);
	}

	if (copy_size < new_copy_size)
	{
		for (gsize i = start; i < start + copy_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copy_arr[i + copy_start]);
		}
		for (gsize i = start + copy_size; i < size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else
	{
		for (gsize i = start; i < size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copy_arr[i + copy_start]);
		}
	}

	return new_arr;
}

/// T具有内置的移动构造函数，且当前类型是内置类型，直接调用内存操作完成数组元素数目的调整
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_size, gsize new_size, GTrueType) GEXCEPT(false)
{
	return GReallocate<T>(old_arr, new_size);
}

/// T具有内置的移动构造函数，且当前类型是不内置类型，使用拷贝操作代替移动操作
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_size, gsize new_size, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[i]);
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[i]);
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，由于要析构元素，此时分两种情况考虑
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_size, gsize new_size, GTrueType) GEXCEPT(false)
{
	/// 根据T是否是内置类型，调用不同的处理逻辑
	return __GArrayResize(old_arr, old_size, new_size,
		GTypeTraits<T>::Arithmetic());
}

/// T不具有内置的移动构造函数，调用移动构造完成数组元素的构造，多出来的元素调用默认构造函数
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_size, gsize new_size, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[i]));
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[i]));
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，且当前类型是内置类型，优先使用内存操作
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_size, gsize new_size, const T &copyable, GTrueType) GEXCEPT(false)
{
	T *new_arr = GReallocate<T>(old_arr, new_size);
	if (old_size < new_size)
	{
		for (gsize i = old_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	return new_arr;
}

/// T具有内置的移动构造函数，且当前类型是不内置类型，使用拷贝操作代替移动操作
template <typename T> GINLINE
T *__GArrayResize(T *old_arr, gsize old_size, gsize new_size, const T &copyable, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[i]);
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[i]);
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，此时分两种情况考虑
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_size, gsize new_size, const T &copyable, GTrueType) GEXCEPT(false)
{
	/// 根据T是否是内置类型，调用不同的处理逻辑
	return __GArrayResize(old_arr, old_size, new_size, copyable,
		GTypeTraits<T>::Arithmetic());
}

/// T不具有内置的移动构造函数，使用移动操作
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_size, gsize new_size, const T &copyable, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[i]));
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[i]));
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，且当前类型是内置类型，优先使用等号操作
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = new_start; i < new_real_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = new_start; i < new_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，且当前类型是不内置类型，使用拷贝操作代替移动操作
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[j++]);
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[j++]);
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，此时分两种情况考虑
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) GEXCEPT(false)
{
	/// 根据T是否是内置类型，调用不同的处理逻辑
	return __GArrayResize(old_arr, old_start, old_size, new_size, new_start,
		GTypeTraits<T>::Arithmetic());
}

/// T不具有内置的移动构造函数，使用移动操作
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;
	gsize j = old_start;

	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[j++]));
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<T>(new_arr + i);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[j++]));
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，且当前类型是内置类型，优先使用等号操作
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			new_arr[i] = copyable;
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			new_arr[i] = copyable;
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			new_arr[i] = copyable;
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，且当前类型是不内置类型，使用拷贝操作代替移动操作
template <typename T> GINLINE 
T *__GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[j++]);
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, old_arr[j++]);
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，此时分两种情况考虑
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable, GTrueType) GEXCEPT(false)
{
	/// 根据T是否是内置类型，调用不同的处理逻辑
	return __GArrayResize(old_arr, old_start, old_size, new_size, new_start, copyable,
		GTypeTraits<T>::Arithmetic());
}

/// T不具有内置的移动构造函数，使用移动操作
template <typename T> GINLINE 
T *_GArrayResize(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(new_size);
	gsize new_real_size = new_start + old_size;
	gsize j = old_start;

	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[j++]));
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<T>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GMoveConstruct<T>(new_arr + i, GMove(old_arr[j++]));
		}
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(old_arr, old_start + old_size);
	return new_arr;
}

/// T具有内置的移动构造函数，且当前类型是内置类型，使用内存拷贝
template <typename T> GINLINE 
T *__GArrayRemoveAt(T *arr, gsize size, gsize pos, GTrueType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size - 1);
	if (pos > 0)
	{
		GMemCopy(new_arr, arr, sizeof(T) * pos);
	}
	GMemCopy(new_arr + pos, arr + pos + 1, sizeof(T) * (size - pos - 1));

	// 销毁旧的数组
	GArrays::DestoryArray<T>(arr, size);
	return new_arr;
}

/// T具有内置的移动构造函数，且当前类型是内置类型，使用拷贝操作
template <typename T> GINLINE 
T *__GArrayRemoveAt(T *arr, gsize size, gsize pos, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size - 1);
	for (gsize i = 0; i < pos; i++)
	{
		GCopyConstruct<T>(new_arr + i, arr[i]);
	}
	for (gsize i = pos + 1; i < size; i++)
	{
		GCopyConstruct<T>(new_arr + i - 1, arr[i]);
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(arr, size);
	return new_arr;
}

/// T具有内置的移动构造函数，此时分两种情况考虑
template <typename T> GINLINE 
T *_GArrayRemoveAt(T *arr, gsize size, gsize pos, GTrueType) GEXCEPT(false)
{
	/// 根据T是否是内置类型，调用不同的处理逻辑
	return __GArrayRemoveAt(arr, size, pos,
		GTypeTraits<T>::Arithmetic());
}

/// T不具有内置的移动构造函数，使用移动操作
template <typename T> GINLINE 
T *_GArrayRemoveAt(T *arr, gsize size, gsize pos, GFalseType) GEXCEPT(false)
{
	T *new_arr = GAllocate<T>(size - 1);
	for (gsize i = 0; i < pos; i++)
	{
		GMoveConstruct<T>(new_arr + i, GMove(arr[i]));
	}
	for (gsize i = pos + 1; i < size; i++)
	{
		GMoveConstruct<T>(new_arr + i - 1, GMove(arr[i]));
	}

	// 销毁旧的数组
	GArrays::DestoryArray<T>(arr, size);
	return new_arr;
}

/// T不具有内置的析构函数，不析构
template <typename T> GINLINE 
gvoid _GArrayClear(T *arr, gsize size, GTrueType) GNOEXCEPT
{

}

/// T不具有内置的析构函数，依次调用析构函数
template <typename T> GINLINE 
gvoid _GArrayClear(T *arr, gsize size, GFalseType) GNOEXCEPT
{
	if (!arr)
	{
		return;
	}
	for (gsize i = 0; i < size; i++)
	{
		arr[i].~T();
	}
}

/// T是内置类型，无需析构，并直接使用内存拷贝
template <typename T> GINLINE 
gvoid _GArrayCopyFrom(T *arr, gsize size, const T *copy_arr, GTrueType)
{
	GMemCopy(arr, copy_arr, sizeof(T) * size);
}

/// T不是内置类型，先析构，在调用拷贝构造
template <typename T> GINLINE 
gvoid _GArrayCopyFrom(T *arr, gsize size, const T *copy_arr, GFalseType) GEXCEPT(false)
{
	for (gsize i = 0; i < size; i++)
	{
		// 析构原有元素
		GDestruct<T>(arr + i);

		// 拷贝构造新的元素
		GCopyConstruct<T>(arr + i, copy_arr[i]);
	}
}

/// T是内置类型，无需析构，并直接使用内存拷贝
template <typename T> GINLINE 
T *_GArrayCopyFrom(T *arr, gsize size, const T *copy_arr, gsize copy_size, GTrueType) GEXCEPT(false)
{
	if (size != copy_size)
	{
		GDeallocate<T>(arr);
		arr = GAllocate<T>(copy_size);
	}

	GMemCopy(arr, copy_arr, sizeof(T) * copy_size);
	return arr;
}

/// T不是内置类型，先析构，再调用拷贝构造
template <typename T> GINLINE 
T *_GArrayCopyFrom(T *arr, gsize size, const T *copy_arr, gsize copy_size, GFalseType) GEXCEPT(false)
{
	for (gsize i = 0; i < size; i++)
	{
		GDestruct<T>(arr + i);
	}
	if (size != copy_size)
	{
		GDeallocate<T>(arr);
		arr = GAllocate<T>(copy_size);
	}
	for (gsize i = 0; i < copy_size; i++)
	{
		GCopyConstruct<T>(arr + i, copy_arr[i]);
	}
	return arr;
}

} // namespace gsystem.detail.arrays
} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

template <typename T> GINLINE
T *GArrays::CreateArray(gsize size) GEXCEPT(false)
{
	GASSERT(size > 0);

	/// 根据T是否具有内置的默认构造函数，去调用不同的处理逻辑
	return detail::arrays::_GArrayCreate<T>(size,
		GTypeTraits<T>::TrivialDefaultConstructible());
}

template <typename T> GINLINE
T *GArrays::CreateArray(gsize size, const T &copyable) GEXCEPT(false)
{
	GASSERT(size > 0);

	T *arr = GAllocate<T>(size);
	for (gsize i = 0; i < size; i++)
	{
		// 在GConstruct的调用过程中，已经处理了针对内置类型的处理逻辑
		GCopyConstruct<T>(arr + i, copyable);
	}
	return arr;
}

template <typename T> GINLINE 
T *GArrays::CreateArray(const T *copy_arr, gsize copy_start, gsize copy_size) GEXCEPT(false)
{
	// 若copy_arr不存在，或者copy_start超过了范围，则会报错
	GASSERT(copy_arr && copy_start < copy_size);

	// 根据T是否是内置类型，去调用不同的处理逻辑
	return detail::arrays::_GArrayCreate<T>(copy_arr, copy_start, copy_size,
		GTypeTraits<T>::Arithmetic());
}

template <typename T> GINLINE
T *GArrays::CreateArray(gsize size, gsize start, const T *copy_arr, gsize copy_start, gsize copy_size) GEXCEPT(false)
{
	GASSERT(start < size && copy_arr && copy_start < copy_size);

	// 根据T是否是内置类型，去调用不同的处理逻辑
	return detail::arrays::_GArrayCreate(size, start, copy_arr, copy_start, copy_size,
		GTypeTraits<T>::Arithmetic());
}

template <typename T> GINLINE
T *GArrays::ResizeArray(T *old_arr, gsize old_size, gsize new_size) GEXCEPT(false)
{
	// 判断T是否具有移动构造函数，以判断是否需要调用不同的函数
	return detail::arrays::_GArrayResize<T>(old_arr, old_size, new_size,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
T *GArrays::ResizeArray(T *old_arr, gsize old_size, gsize new_size, const T &copyable) GEXCEPT(false)
{
	// 判断T是否具有移动构造函数，以判断是否需要调用不同的函数
	return detail::arrays::_GArrayResize<T>(old_arr, old_size, new_size, copyable,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
T *GArrays::ResizeArray(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start) GEXCEPT(false)
{
	GASSERT(old_start < old_size);

	// 判断T是否具有移动构造函数，以判断是否需要调用不同的函数
	return detail::arrays::_GArrayResize<T>(old_arr, old_start, old_size, new_size, new_start,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
T *GArrays::ResizeArray(T *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const T &copyable) GEXCEPT(false)
{
	// 判断T是否具有移动构造函数，以判断是否需要调用不同的函数
	return detail::arrays::_GArrayResize<T>(old_arr, old_start, old_size, new_size, new_start, copyable,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
T *GArrays::RemoveArrayElementAt(T *arr, gsize size, gsize pos) GEXCEPT(false)
{
	GASSERT(size > 0 && pos < size);

	// 判断T是否具有移动构造函数，以判断是否需要调用不同的函数
	return detail::arrays::_GArrayRemoveAt(arr, size, pos,
		GTypeTraits<T>::TrivialMoveConstructible());
}

template <typename T> GINLINE
gvoid GArrays::ClearArray(T *arr, gsize size) GNOEXCEPT
{
	detail::arrays::_GArrayClear(arr, size,
		GTypeTraits<T>::TrivialDestructible());
}

template <typename T> GINLINE
gvoid GArrays::DestoryArray(T *arr, gsize size) GNOEXCEPT
{
	// 判断T是否具有析构函数，以判断是否需要调用不同的函数
	detail::arrays::_GArrayClear(arr, size,
		GTypeTraits<T>::TrivialDestructible());

	// 释放内存
	GDeallocate<T>(arr);
}

template <typename T> GINLINE
gvoid GArrays::CopyArrayFrom(T *arr, gsize size, const T *copy_arr) GEXCEPT(false)
{
	GASSERT(arr && copy_arr);

	// 判断T是否是基本类型，以判断是否需要调用不同的函数
	detail::arrays::_GArrayCopyFrom<T>(arr, size, copy_arr,
		GTypeTraits<T>::Arithmetic());
}

template <typename T> GINLINE 
T *GArrays::CopyArrayFrom(T *arr, gsize size, const T *copy_arr, gsize copy_size) GEXCEPT(false)
{
	GASSERT(arr && copy_arr);

	// 判断T是否是基本类型，以判断是否需要调用不同的函数
	return detail::arrays::_GArrayCopyFrom<T>(arr, size, copy_arr, copy_size,
		GTypeTraits<T>::Arithmetic());
}

}  // namespace gsystem

#endif // _CORE_ARRAYS_INLINE_
