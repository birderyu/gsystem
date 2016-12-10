// 动态数组

#ifndef _CORE_DYNAMIC_ARRAY_H_
#define _CORE_DYNAMIC_ARRAY_H_

#include "CsArray.h"

template <typename DataT>
class CsDynamicArray 
	: public CsArray<DataT>
{
public:
	CsDynamicArray();
	CsDynamicArray(cs_size_t len);
	CsDynamicArray(cs_size_t len, const DataT &t);
	CsDynamicArray(const CsDynamicArray<DataT> &tArray);
	~CsDynamicArray();

	// 获取数组的长度
	cs_size_t Size() const;

	// 数组是否为空
	cs_bool IsEmpty() const;

	// 重分配数组的长度，可能会造成内存泄漏
	cs_bool Resize(cs_size_t len);

	// 重分配数组的长度，并将多出来的元素赋默认值t，可能会造成内存泄漏
	cs_bool Resize(cs_size_t len, const DataT &t);

	// 清空数组
	cs_void Clear();

	DataT &GetAt(cs_size_t);
	const DataT &GetAt(cs_size_t) const;

	// 通过下标访问和修改数组元素
	DataT &operator[](cs_size_t);
	const DataT &operator[](cs_size_t) const;
	
	// 移除特定位置的元素
	cs_bool RemoveAt(cs_size_t);

	// 拷贝
	CsDynamicArray<DataT> &operator=(const CsDynamicArray<DataT> &arr);

public:
	// 从src的start位开始，拷贝len个元素，到dst的first位
	static cs_bool ArrayCopy(const CsDynamicArray<DataT> &src, cs_size_t start, cs_size_t len,
		CsDynamicArray<DataT> &dst, cs_size_t first = 0);

private:
	// 注意：以下两个方法，只拷贝内存，即浅拷贝
	// 从pData的start位开始，拷贝len长度的内存到first位
	cs_bool CopyMemoryFrom(cs_size_t first, cs_size_t len,
		const DataT *pData, cs_size_t start = 0);

	// 从start位开始，拷贝len长度的内存到pData的first位
	cs_bool CopyMemoryTo(cs_size_t start, cs_size_t len,
		DataT *pData, cs_size_t first = 0) const;

private:
	DataT *m_pData;
	cs_size_t m_nSize;
};

#include "CsDynamicArray.inl"

#endif // _CORE_DYNAMIC_ARRAY_H_