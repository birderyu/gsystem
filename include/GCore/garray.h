#ifndef _CORE_ARRAY_H_
#define _CORE_ARRAY_H_

#include "gobject.h"
#include "gserialize.h"
#include "gstructure.h"
#include "gallocator.h"
#include "gconstructor.h"

template <typename DataT>
class GArray
	: public GListT<GArray<DataT>>
	, virtual public GObject
{
public:
	/// 静态方法，创建一个长度为size的数组，并依次调用每一个元素的默认构造函数
	static DataT *CreateArray(gsize size) noexcept(false);

	/// 静态方法，创建一个长度为size的数组，并依次使用copyable去初始化数组中的每一个元素
	static DataT *CreateArray(gsize size, const DataT &copyable) noexcept(false);

	/// 静态方法，创建一个长度为copy_size的数组，并用copy_arr的第copy_start起的copy_size元素去初始化新的数组
	static DataT *CreateArray(const DataT *copy_arr, gsize copy_start, gsize copy_size) noexcept(false);

	/// 静态方法，创建一个长度为size的数组，并用copy_arr的第copy_start起的copy_size元素去初始化新的数组的第start开始的copy_size个元素
	/// 其余的元素使用默认的构造函数构造
	static DataT *CreateArray(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size) noexcept(false);

	/// 静态方法，将数组old_arr的数组元素数目由old_size调整为new_size
	/// 若旧数组不存在（old_arr == GNULL && old_size == 0），会创建一个长度为new_size的新的数组
	/// 在调整大小的过程中，若新的数组元素数目大于原有数目，会创建新的元素，反之会有部分元素被析构
	/// 在调整大小的过程中，会优先调用移动构造
	static DataT *ResizeArray(DataT *old_arr, gsize old_size, gsize new_size) noexcept(false);

	/// 静态方法，将数组old_arr的数组元素数目由old_size调整为new_size
	/// 在调整大小的过程中，若新的数组元素数目大于原有数目，会用copyable去初始化新的元素，反之会有部分元素被析构
	/// 在调整大小的过程中，会优先调用移动构造
	static DataT *ResizeArray(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable) noexcept(false);

	/// 静态方法，将数组old_arr的数组元素数目调整为new_size
	/// 在调整大小的过程中，仅保留原来数组的从old_start位开始的old_size个元素，放置到新数组的第new_start位
	/// 在调整大小的过程中，会优先调用移动构造
	static DataT *ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start) noexcept(false);

	/// 静态方法，将数组old_arr的数组元素数目调整为new_size
	/// 在调整大小的过程中，仅保留原来数组的从old_start位开始的old_size个元素，放置到新数组的第new_start位
	/// 在调整大小的过程中，新创建出来的元素，会使用copyable进行初始化
	/// 在调整大小的过程中，会优先调用移动构造
	static DataT *ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable) noexcept(false);

	/// 静态方法，移除数组中的某一位元素，会对移除掉的元素调用析构函数
	static DataT *RemoveArrayElementAt(DataT *arr, gsize size, gsize pos) noexcept(false);

	/// 静态方法，销毁一个数组，并依次调用每一个元素的析构函数
	static gvoid DestoryArray(DataT *arr, gsize size) noexcept;

	/// 静态方法，依次调用每一个元素的析构函数，不释放内存
	static gvoid ClearArray(DataT *arr, gsize size) noexcept;

	/// 静态方法，将数组copy_arr的内容拷贝到arr中
	/// 必须保证copy_arr至少包含了size个元素
	static gvoid CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr) noexcept(false);

	/// 静态方法，将数组copy_arr的内容拷贝到arr中
	/// 在拷贝的过程中，arr的地址和长度会随着copy_arr的不同而改变
	/// 若size与copy_size不一致，将重新分配内存
	/// 返回拷贝之后的数据的地址
	static DataT *CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size) noexcept(false);

public:
	enum { CLASS_CODE = CLASS_CODE_ARRAY, };

public:
	virtual ~GArray() = 0 {}

	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;

	//virtual DataT &ConstGetAt(gsize pos) = 0;
	virtual DataT &GetAt(gsize pos) = 0;
	virtual const DataT &GetAt(gsize pos) const = 0;

	//virtual DataT *ConstCursorAt(gsize pos) = 0;
	virtual DataT *CursorAt(gsize pos) = 0;
	virtual const DataT *CursorAt(gsize pos) const = 0;

	virtual DataT &operator[](gsize pos) = 0;
	virtual const DataT &operator[](gsize pos) const = 0;

	gbool Contains(const DataT &) const;
	gsize FirstIndexOf(const DataT &) const;
	gsize LastIndexOf(const DataT &) const;
	gsize CountOf(const DataT &) const;

	///
	virtual guint ClassCode() const;
};

#include "garray.inl"

#endif // _CORE_ARRAY_H_