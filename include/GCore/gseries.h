
/********************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file gseries.h
** @brief 序列数组结构
** @author birderyu
** @contact https://github.com/birderyu
** @date 2016-12-03
** @version 1.0.0
**
** 为了使得串结构（String）更加高效，构建了高效利用栈空间的数据结构GSeries，它拥有以下特点：
** 1）为了支持串操作在大部分使用场景中，其长度都不大（如字符串中，短字符串频繁出现），将元素数
** 量较小的数组数据存储在本地空间（栈空间）中；
** 2）为了支持串在大部分时间其实用于只读操作的情景，支持COW（copy-on-write，写时拷贝）。
**
********************************************************************************/
#ifndef _CORE_SERIES_H_
#define _CORE_SERIES_H_

#include "garray.h"
#include "garrays.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 序列数组
** @template T {type} 数组元素的类型
** @template LOCAL_SIZE {gsize} 本地空间的大小
** @template HAS_END_FLAG {gbool} 是否包含结束标志，如C风格字符串将字符0作为结束标志，
**     默认为false
** @template END_FLAG {T} 结束标志，当HAS_END_FLAG为true时有效
**
********************************************************************************/
template<typename T, 
	gsize LOCAL_SIZE,
	gbool HAS_END_FLAG = false, 
	T END_FLAG = T()>
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
	GSeries(const T *arr, gsize size);
	GSeries(const GArray<T> &arr);
	GSeries(GArray<T> &&arr);
	GSeries(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &arr);
	GSeries(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&arr);
	~GSeries();

	GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &operator=(const GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &arr);
	GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &operator=(GSeries<T, LOCAL_SIZE, HAS_END_FLAG, END_FLAG> &&arr);

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

#include "inline/gseries.inl"

#endif // _CORE_SERIES_H_