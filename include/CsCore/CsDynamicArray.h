// 动态数组

#ifndef _CORE_DYNAMIC_ARRAY_H_
#define _CORE_DYNAMIC_ARRAY_H_

#include "CsArray.h"

template <typename DataT>
class CsDynamicArray final
	: public CsArray<DataT>
{
public:
	enum { CLASS_CODE = CLASS_CODE_DYNAMIC_ARRAY, };

public:
	// 从src的start位开始，拷贝len个元素，到dst的first位
	static cs_bool ArrayCopy(const CsDynamicArray<DataT> &src, cs_size_t start, cs_size_t len,
		CsDynamicArray<DataT> &dst, cs_size_t first = 0);

public:
	CsDynamicArray();
	CsDynamicArray(cs_size_t size);
	CsDynamicArray(cs_size_t size, const DataT &data);
	CsDynamicArray(const CsDynamicArray<DataT> &);
	CsDynamicArray(const CsArray<DataT> &, cs_size_t start, cs_size_t size);
	~CsDynamicArray();

	// 获取数组的长度
	cs_size_t Size() const;

	// 数组是否为空
	cs_bool IsEmpty() const;

	// 重分配数组的长度，可能会造成内存泄漏
	cs_bool Resize(cs_size_t new_size);

	// 重分配数组的长度，并将多出来的元素赋默认值t，可能会造成内存泄漏
	cs_bool Resize(cs_size_t new_size, const DataT &data);

	// 重分配数组长度，并保留原来从start开始的size个元素作为新数组的第0位
	cs_bool Resize(cs_size_t new_size, cs_size_t start, cs_size_t size, cs_size_t new_start = 0);
	cs_bool Resize(cs_size_t new_size, cs_size_t start, cs_size_t size, cs_size_t new_start, const DataT &data);

	// 销毁数组
	cs_void Dispose();

	DataT &GetAt(cs_size_t);
	const DataT &GetAt(cs_size_t) const;

	// 通过下标访问和修改数组元素
	DataT &operator[](cs_size_t);
	const DataT &operator[](cs_size_t) const;
	
	DataT *operator+=(cs_size_t);
	const DataT *operator+=(cs_size_t) const;

	// 移除特定位置的元素
	cs_bool RemoveAt(cs_size_t);

	// 拷贝
	CsDynamicArray<DataT> &operator=(const CsDynamicArray<DataT> &);

	// 相等
	cs_bool operator==(const CsDynamicArray<DataT> &);

	///
	cs_uint ClassCode() const;
	cs_bool Serializable() const;
	template<typename ArchiveT> cs_bool Serialize(ArchiveT &) const;
	template<typename ArchiveT> cs_bool Deserialize(ArchiveT &);

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

typedef CsDynamicArray<cs_int> CsIntegerArray;
typedef CsDynamicArray<cs_size_t> CsSizeTypeArray;

#include "CsDynamicArray.inl"

#endif // _CORE_DYNAMIC_ARRAY_H_