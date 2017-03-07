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
	GDynamicArray();
	GDynamicArray(gsize size);
	GDynamicArray(gsize size, const DataT &data);
	GDynamicArray(const GDynamicArray<DataT> &arr);
	GDynamicArray(GDynamicArray<DataT> &&arr);
	GDynamicArray(const GArray<DataT> &arr, gsize start, gsize size);
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

	// 清空数组，不释放内存
	gvoid Clear();

	// 销毁数组
	gvoid Dispose();

	DataT &GetAt(gsize);
	const DataT &GetAt(gsize) const;

	DataT *CursorAt(gsize);
	const DataT *CursorAt(gsize) const;

	// 通过下标访问和修改数组元素
	DataT &operator[](gsize);
	const DataT &operator[](gsize) const;
	
	// 移除特定位置的元素
	gbool RemoveAt(gsize);

	// 拷贝和移动
	GDynamicArray<DataT> &operator=(const GDynamicArray<DataT> &);
	GDynamicArray<DataT> &operator=(GDynamicArray<DataT> &&);

	// 相等
	gbool operator==(const GDynamicArray<DataT> &);

	///
	guint ClassCode() const;
	gbool Serializable() const;
	template<typename ArchiveT> gbool Serialize(ArchiveT &) const;
	template<typename ArchiveT> gbool Deserialize(ArchiveT &);

private:
	DataT *m_pData;
	gsize m_nSize;
};

typedef GDynamicArray<gint> GIntegerArray;
typedef GDynamicArray<gsize> GSizeArray;

#include "gdynamicarray.inl"

#endif // _CORE_DYNAMIC_ARRAY_H_