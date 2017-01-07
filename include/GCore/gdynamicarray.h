// 动态数组

#ifndef _CORE_DYNAMIC_ARRAY_H_
#define _CORE_DYNAMIC_ARRAY_H_

#include "garray.h"

template <typename DataT>
class GDynamicArray final
	: public GArray<DataT>
{
public:
	enum { CLASS_CODE = CLASS_CODE_DYNAMIC_ARRAY, };

public:
	// 从src的start位开始，拷贝len个元素，到dst的first位
	static gbool ArrayCopy(const GDynamicArray<DataT> &src, gsize start, gsize len,
		GDynamicArray<DataT> &dst, gsize first = 0);

public:
	GDynamicArray();
	GDynamicArray(gsize size);
	GDynamicArray(gsize size, const DataT &data);
	GDynamicArray(const GDynamicArray<DataT> &);
	GDynamicArray(const GArray<DataT> &, gsize start, gsize size);
	~GDynamicArray();

	// 获取数组的长度
	gsize Size() const;

	// 数组是否为空
	gbool IsEmpty() const;

	// 重分配数组的长度，可能会造成内存泄漏
	gbool Resize(gsize new_size);

	// 重分配数组的长度，并将多出来的元素赋默认值t，可能会造成内存泄漏
	gbool Resize(gsize new_size, const DataT &data);

	// 重分配数组长度，并保留原来从start开始的size个元素作为新数组的第0位
	gbool Resize(gsize new_size, gsize start, gsize size, gsize new_start = 0);
	gbool Resize(gsize new_size, gsize start, gsize size, gsize new_start, const DataT &data);

	// 销毁数组
	gvoid Dispose();

	DataT &GetAt(gsize);
	const DataT &GetAt(gsize) const;

	// 通过下标访问和修改数组元素
	DataT &operator[](gsize);
	const DataT &operator[](gsize) const;
	
	DataT *operator+=(gsize);
	const DataT *operator+=(gsize) const;

	// 移除特定位置的元素
	gbool RemoveAt(gsize);

	// 拷贝
	GDynamicArray<DataT> &operator=(const GDynamicArray<DataT> &);

	// 相等
	gbool operator==(const GDynamicArray<DataT> &);

	///
	guint ClassCode() const;
	gbool Serializable() const;
	template<typename ArchiveT> gbool Serialize(ArchiveT &) const;
	template<typename ArchiveT> gbool Deserialize(ArchiveT &);

	// 注意：以下两个方法，只拷贝内存，即浅拷贝
	// 从pData的start位开始，拷贝len长度的内存到first位
	gbool CopyMemoryFrom(gsize first, gsize size,
		const DataT *pData, gsize start = 0);

	// 从start位开始，拷贝len长度的内存到pData的first位
	gbool CopyMemoryTo(gsize start, gsize size,
		DataT *pData, gsize first = 0) const;

private:
	DataT *m_pData;
	gsize m_nSize;
};

typedef GDynamicArray<gint> GIntegerArray;
typedef GDynamicArray<gsize> GSizeArray;

#include "gdynamicarray.inl"

#endif // _CORE_DYNAMIC_ARRAY_H_