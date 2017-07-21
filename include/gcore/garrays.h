/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file garrays.h
** @brief 数组帮助类
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-24
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_ARRAYS_H_
#define _CORE_ARRAYS_H_

#include "gtype.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 数组帮助类
** 
** 数组帮助类封装了几个常用的C风格数组的静态方法
**
********************************************************************************/
class GArrays
{
public:
	/****************************************************************************
	**
	** @name CreateArray
	** @brief 静态方法，创建数组
	** @template DataT 数组元素的类型
	** @param [in] size {gsize} 数组的元素个数
	** @return {DataT *} 返回创建数组的首地址，若创建失败，则返回GNULL
	**
	** 创建一个元素个数为size的数组，会调用每一个元素的默认构造函数。
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *CreateArray(gsize size) GEXCEPT(false);

	/****************************************************************************
	**
	** @name CreateArray
	** @brief 静态方法，创建数组，并对数组的每一个元素赋初始值
	** @template DataT 数组元素的类型
	** @param [in] size {gsize} 数组的元素个数
	** @param [in] copyable {const DataT &} 初始值
	** @return {DataT *} 返回创建数组的首地址，若创建失败，则返回GNULL
	**
	** 创建一个元素个数为size的数组，并依次使用copyable去初始化数组中的每一个元素，在初始化的
	** 过程中会调用每一个元素的拷贝构造函数。
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *CreateArray(gsize size, const DataT &copyable) GEXCEPT(false);

	/****************************************************************************
	**
	** @name CreateArray
	** @brief 静态方法，拷贝创建数组的一部分元素成为一个新的数组
	** @template DataT 数组元素的元素个数
	** @param [in] copy_arr {const DataT *} 被拷贝的数组的首地址
	** @param [in] copy_start_pos {gsize} 被拷贝数组的起始位置
	** @param [in] copy_size {gsize} 希望拷贝的元素的个数
	** @return {DataT *} 返回创建数组的首地址，若创建失败，则返回GNULL
	**
	** 将数组copy_arr第copy_start_pos个元素（从0开始计数）开始的copy_size个元素拷贝出来并
	** 创建一个新的数组，在初始化新数组的过程中，会调用每一个元素的拷贝构造函数。
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *CreateArray(const DataT *copy_arr, gsize copy_start_pos, 
		gsize copy_size) GEXCEPT(false);

	/****************************************************************************
	**
	** @name CreateArray
	** @brief 静态方法，创建数组，并将一个数组的一部分元素拷贝到新创建数组的指定位置
	** @template DataT 数组元素的类型
	** @param [in] size {gsize} 创建数组的元素个数
	** @param [in] start {gsize} 新数组接收元素的位置
	** @param [in] copy_arr {const DataT *} 被拷贝的数组的首地址
	** @param [in] copy_start {gsize} 被拷贝数组的起始位置
	** @param [in] copy_size {gsize} 希望拷贝的元素的个数
	** @return {DataT *} 返回创建数组的首地址，若创建失败，则返回GNULL
	**
	** 创建一个长度为size的数组，并用数组copy_arr的第copy_start起的copy_size元素去初始化新
	** 创建的数组的第start开始的copy_size个元素
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *CreateArray(gsize size, gsize start, const DataT *copy_arr, 
		gsize copy_start, gsize copy_size) GEXCEPT(false);

	/****************************************************************************
	**
	** @name ResizeArray
	** @brief 静态方法，重置数组元素的个数
	** @template DataT 数组元素的类型
	** @param [in] old_arr {DataT *} 待重置的数组的首地址
	** @param [in] old_size {gsize} 待重置的数组的元素个数
	** @param [in] new_size {gsize} 重置后的数组的元素个数
	** @return {DataT *} 重置后的数组的首地址，若重置失败，则返回GNULL
	**
	** 将数组old_arr的数组元素数目由old_size调整为new_size，若旧数组不存在或元素个数为空，会
	** 创建一个长度为new_size的新的数组。在重置的过程中，若新的数组元素个数大于原有个数，会创建
	** 新的元素，反之会有部分元素被析构。
	** 在调整大小的过程中，会优先调用移动构造
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *ResizeArray(DataT *old_arr, gsize old_size, gsize new_size) 
		GEXCEPT(false);

	/****************************************************************************
	**
	** @name ResizeArray
	** @brief 静态方法，重置数组元素的个数，并对新创建的元素赋初始值
	** @template DataT 数组元素的类型
	** @param [in] old_arr {DataT *} 待重置的数组的首地址
	** @param [in] old_size {gsize} 待重置的数组的元素个数
	** @param [in] new_size {gsize} 重置后的数组的元素个数
	** @param [in] copyable {const DataT &} 初始值
	** @return {DataT *} 重置后的数组的首地址，若重置失败，则返回GNULL
	**
	** 将数组old_arr的数组元素数目由old_size调整为new_size，若旧数组不存在或元素个数为空，会
	** 创建一个长度为new_size的新的数组。在重置的过程中，若新的数组元素个数大于原有个数，会用
	** copyable去初始化新的元素，反之会有部分元素被析构。
	** 在调整大小的过程中，会优先调用移动构造
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *ResizeArray(DataT *old_arr, gsize old_size, gsize new_size, 
		const DataT &copyable) GEXCEPT(false);

	/****************************************************************************
	**
	** @name ResizeArray
	** @brief 静态方法，重置数组元素的个数，并且仅保留原数组的部分元素
	** @template DataT 数组元素的类型
	** @param [in] old_arr {DataT *} 待重置的数组的首地址
	** @param [in] old_start {gsize} 待重置的数组需要保留元素的位置
	** @param [in] old_size {gsize} 待重置的数组需要保留元素的个数
	** @param [in] new_size {gsize} 重置后的数组的元素个数 
	** @param [in] new_start {gsize} 重置后的数组放置保留元素的位置
	** @return {DataT *} 重置后的数组的首地址，若重置失败，则返回GNULL
	**
	** 将数组old_arr的数组元素数目调整为new_size。在重置的过程中，仅保留原来数组的从old_start
	** 位开始的old_size个元素，将其放置到重置后数组的第new_start位。
	** 在调整大小的过程中，会优先调用移动构造
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, 
		gsize new_size, gsize new_start) GEXCEPT(false);

	/****************************************************************************
	**
	** @name ResizeArray
	** @brief 静态方法，重置数组元素的个数，并且仅保留原数组的部分元素，对新创建出来的元素赋初始值
	** @template DataT 数组元素的类型
	** @param [in] old_arr {DataT *} 待重置的数组的首地址
	** @param [in] old_start {gsize} 待重置的数组需要保留元素的位置
	** @param [in] old_size {gsize} 待重置的数组需要保留元素的个数
	** @param [in] new_size {gsize} 重置后的数组的元素个数
	** @param [in] new_start {gsize} 重置后的数组放置保留元素的位置
	** @param [in] copyable {const DataT &} 初始值
	** @return {DataT *} 重置后的数组的首地址，若重置失败，则返回GNULL
	**
	** 将数组old_arr的数组元素数目调整为new_size。在重置的过程中，仅保留原来数组的从old_start
	** 位开始的old_size个元素，将其放置到重置后数组的第new_start位。若在重置的过程中有新的元素
	** 被创建出来，则使用copyable进行初始化。
	** 在调整大小的过程中，会优先调用移动构造
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, 
		gsize new_size, gsize new_start, const DataT &copyable) GEXCEPT(false);

	/****************************************************************************
	**
	** @name RemoveArrayElementAt
	** @brief 静态方法，移除数组指定位置的元素
	** @template DataT 数组元素的类型
	** @param [in] arr {DataT *} 数组的首地址
	** @param [in] size {gsize} 数组的长度
	** @param [in] pos {gsize} 待移除元素的位置，从0开始计数
	** @return {DataT *} 移除元素后的数组的首地址，若移除失败，则返回GNULL
	**
	** 对移除掉的元素调用析构函数
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *RemoveArrayElementAt(DataT *arr, gsize size, gsize pos) 
		GEXCEPT(false);

	/****************************************************************************
	**
	** @name DestoryArray
	** @brief 静态方法，销毁数组
	** @template DataT 数组元素的类型
	** @param [in] arr {DataT *} 数组的首地址
	** @param [in] size {gsize} 数组的长度
	**
	** 依次调用每一个元素的析构函数，并释放内存
	**
	****************************************************************************/
	template <typename DataT> 
	static gvoid DestoryArray(DataT *arr, gsize size) GNOEXCEPT;

	/****************************************************************************
	**
	** @name ClearArray
	** @brief 静态方法，清空数组
	** @template DataT 数组元素的类型
	** @param [in] arr {DataT *} 数组的首地址
	** @param [in] size {gsize} 数组的长度
	**
	** 依次调用每一个元素的析构函数，但不释放内存
	**
	****************************************************************************/
	template <typename DataT> 
	static gvoid ClearArray(DataT *arr, gsize size) GNOEXCEPT;

	/****************************************************************************
	**
	** @name CopyArrayFrom
	** @brief 静态方法，拷贝数组元素
	** @template DataT 数组元素的类型
	** @param [in] arr {DataT *} 数组的首地址
	** @param [in] size {gsize} 数组的长度
	** @param [in] copy_arr {const DataT *} 被拷贝的数组，需至少包含size个元素
	**
	** 将数组copy_arr的元素拷贝到arr中，arr的元素个数不会改变
	**
	****************************************************************************/
	template <typename DataT> 
	static gvoid CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr) 
		GEXCEPT(false);

	/****************************************************************************
	**
	** @name CopyArrayFrom
	** @brief 静态方法，拷贝数组的部分元素
	** @template DataT 数组元素的类型
	** @param [in] arr {DataT *} 数组的首地址
	** @param [in] size {gsize} 数组的长度
	** @param [in] copy_arr {const DataT *} 被拷贝的数组
	** @param [in] copy_size {gsize} 被拷贝的数组的长度
	** @return {DataT *} 拷贝元素之后的数组首地址，若拷贝失败，则返回GNULL
	**
	** 将数组copy_arr的元素拷贝到arr中，在拷贝的过程中，arr的地址和长度会随着copy_arr的不同而改变，
	** 若size与copy_size不一致，将重新分配内存
	**
	****************************************************************************/
	template <typename DataT> 
	static DataT *CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr, 
		gsize copy_size) GEXCEPT(false);
};

}

#include "inline/garrays.inl"

#endif // _CORE_ARRAYS_H_
