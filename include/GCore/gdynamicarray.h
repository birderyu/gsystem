// 动态数组
#ifndef _CORE_DYNAMIC_ARRAY_H_
#define _CORE_DYNAMIC_ARRAY_H_

#include "garray.h"
#include "gserializable.h"

namespace gsystem { // gsystem

template <typename DataT>
class GDynamicArray final
	: public GArray<DataT>
	, public GSerializable
{
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

	// 重分配数组的长度
	gvoid Resize(gsize new_size);

	// 重分配数组的长度，并将多出来的元素赋默认值t
	gvoid Resize(gsize new_size, const DataT &data);

	// 重分配数组长度，并保留原来从start开始的size个元素作为新数组的第new_start位
	gvoid Resize(gsize new_size, gsize start, gsize size, gsize new_start = 0);

	// 重分配数组长度，并保留原来从start开始的size个元素作为新数组的第new_start位，其余元素使用data赋初始值
	gvoid Resize(gsize new_size, gsize start, gsize size, gsize new_start, const DataT &data);

	// 清空数组，不释放内存
	gvoid Clear();

	// 销毁数组
	gvoid Destroy();

	DataT &GetAt(gsize);
	const DataT &GetAt(gsize) const;

	DataT *CursorAt(gsize);
	const DataT *CursorAt(gsize) const;

	// 通过下标访问和修改数组元素
	DataT &operator[](gsize);
	const DataT &operator[](gsize) const;
	
	// 移除特定位置的元素
	gvoid RemoveAt(gsize pos);

	// 拷贝和移动
	GDynamicArray<DataT> &operator=(const GDynamicArray<DataT> &);
	GDynamicArray<DataT> &operator=(GDynamicArray<DataT> &&);

	// 相等
	gbool operator==(const GDynamicArray<DataT> &);

	///
	guint ClassCode() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

private:
	DataT *m_pData;
	gsize m_nSize;
};

typedef GDynamicArray<gint> GIntegerArray;
typedef GDynamicArray<gsize> GSizeArray;

} // namespace gsystem

#include "inline/gdynamicarray.inl"

#endif // _CORE_DYNAMIC_ARRAY_H_