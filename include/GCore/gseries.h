
/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gseries.h
** @brief	序列数组结构
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2016-12-03
** @version	1.0.0
**
** 为了使得串结构（String）更加高效，构建了数据结构GSeries
** GSeries作为所有串结构的内核（GString、GWString、GBytes），拥有以下特点：
** 1）为了支持串操作在大部分使用场景中，其长度都不大（如字符串中，短字符串频繁出现）；
** 2）为了支持串在大部分时间其实用于只读操作的情景，支持COW（copy-on-write，写时拷贝）。
**
****************************************************************************/
#ifndef _CORE_SERIES_H_
#define _CORE_SERIES_H_

#include "garray.h"
#include "garrays.h"

namespace gsystem { // gsystem

/// 当使用一个数组来存储数据时，针对这个数组有以下处理：
/// 为了增加数组的初始化数据，当数据量小于MIN_SIZE时，数据存储在本地空间上，反之在全局空间中开辟内存
/// 当数据量大于MIN_SIZE时，允许预开辟一些额外的内存，实际内存的大小存储在m_pArray的前几位空间中
/// m_nType用以表示当前对象
template<typename T, 
	gsize LOCAL_SIZE,
	gbool HAS_END_FLAG, 
	T END_FLAG>
class GSeries
{
public:
	static const gsize MIN_CAPACITY = HAS_END_FLAG ? (LOCAL_SIZE - 1) : LOCAL_SIZE;
	static_assert(MIN_CAPACITY > 0, "MIN_CAPACITY must greater than zero.");

public:
	static GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> CopyOf(const T *copy_arr, gsize copy_size);
	static GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> ReferenceOf(const T *ref_arr, gsize ref_size);

public:
	GSeries(gsize capacity = 0);
	GSeries(const T *copy_arr, gsize copy_size);
	GSeries(const GArray<T> &copy_arr);
	GSeries(GArray<T> &&move_arr);
	GSeries(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &arr);
	GSeries(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&arr);
	~GSeries();

	gsize Size() const;
	gsize Capacity() const;

	gbool IsEmpty() const;

	gvoid Resize(gsize size);
	gvoid Reserve(gsize capacity);

	const T &ConstGetAt(gsize pos) const;
	const T &GetAt(gsize pos) const;
	T &GetAt(gsize pos);

	const T *ConstCursorAt(gsize pos) const;
	const T *CursorAt(gsize pos) const;
	T *CursorAt(gsize pos);

	const T *ConstStart() const;
	const T *Start() const;
	T *Start();

	gvoid SetAt(gsize pos, const T &data);
	gvoid SetAt(gsize pos, T &&data);

	// 清空数组，不释放内存
	gvoid Clear();

	// 销毁数组并将数组置空
	gvoid Destroy();

	// 将一个数组添加到末尾
	gvoid Append(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &series);
	gvoid Append(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&series);

	GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &operator=(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &arr);
	GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &operator=(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&arr);
	const T &operator[](gsize pos) const;
	T &operator[](gsize pos);

private:
	// 注意，这三个函数的调用需要慎重，这是因为这三个函数仅做了初始化，未对原来的数据做内存回收
	gvoid CopyConstruct(const T *copy_arr, gsize copy_size);
	gvoid MoveConstruct(T *&move_arr, gsize move_size);
	gvoid ReferenceConstruct(const T *ref_arr, gsize ref_size);

	gvoid Free(); // 销毁数据

	gbool IsReference() const;

	// 将引用类型转换成值类型
	gvoid ToValue(gsize capacity);

private:
	T *m_pStart;
	gsize m_nSize;
	gsize m_nCapacity;
	union
	{
		T  m_tArray[LOCAL_SIZE];
		T *m_pArray;
	};
	gbyte m_nType;
};

GAPI typedef GSeries<gbyte, 4, false, 0>		GBytesData;
GAPI typedef GSeries<gchar8, 8, true, 0>		GString8Data;
GAPI typedef GSeries<gchar16, 4, true, 0>		GString16Data;
GAPI typedef GSeries<gchar32, 2, true, 0>		GString32Data;
GAPI typedef GSeries<gwchar, 4, true, 0>		GWStringData;

} // namespace gsystem

#include "gseries.inl"

#endif // _CORE_SERIES_H_