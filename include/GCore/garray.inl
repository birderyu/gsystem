#ifndef _CORE_ARRAY_INLINE_
#define _CORE_ARRAY_INLINE_

namespace GNova {
	namespace Array {
		namespace Private {

			/// DataT具有内置的构造函数，无需构造，仅分配内存
			template <typename DataT> GINLINE DataT *_GArrayCreate(gsize size, GTrueType) noexcept(false)
			{
				/// 创建结束不需要构造
				return GAllocate<DataT>(size);
			}

			/// DataT不具有内置的构造函数，分配内存之后，依次调用元素的构造函数
			template <typename DataT> GINLINE DataT *_GArrayCreate(gsize size, GFalseType) noexcept(false)
			{
				DataT *arr = GAllocate<DataT>(size);
				for (gsize i = 0; i < size; i++)
				{
					GConstruct<DataT>(arr + i);
				}
				return arr;
			}

			/// DataT是内置类型，直接使用内存拷贝操作完成拷贝处理逻辑
			template <typename DataT> GINLINE DataT *_GArrayCreate(const DataT *copy_arr, gsize copy_start, gsize copy_size, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(copy_size);
				GMemCopy(new_arr, copy_arr + copy_start, copy_size);
				return new_arr;
			}

			/// DataT不是内置类型，调用拷贝操作构造函数处理
			template <typename DataT> GINLINE DataT *_GArrayCreate(const DataT *copy_arr, gsize copy_start, gsize copy_size, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(copy_size);
				for (gsize i = 0; i < copy_size; i++)
				{
					GConstruct<DataT>(new_arr + i, copy_arr[i + copy_start]);
				}
				return new_arr;
			}

			/// DataT是内置类型，直接使用内存拷贝操作完成拷贝处理逻辑，其余元素无需构造，仅分配内存
			template <typename DataT> GINLINE DataT *_GArrayCreate(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size);
				gsize new_copy_size = size - start;
				gsize real_copy_size = copy_size < new_copy_size ? copy_size : new_copy_size;
				GMemCopy(new_arr + start, copy_arr + copy_start, real_copy_size);
				return new_arr;
			}

			/// DataT不是内置类型，调用拷贝操作构造函数处理
			template <typename DataT> GINLINE DataT *_GArrayCreate(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size);
				gsize new_copy_size = size - start;

				for (gsize i = 0; i < start; i++)
				{
					GConstruct<DataT>(new_arr + i);
				}

				if (copy_size < new_copy_size)
				{
					for (gsize i = start; i < start + copy_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copy_arr[i + copy_start]);
					}
					for (gsize i = start + copy_size; i < size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else
				{
					for (gsize i = start; i < size; i++)
					{
						GConstruct<DataT>(new_arr + i, copy_arr[i + copy_start]);
					}
				}

				return new_arr;
			}

			/// DataT具有内置的移动构造函数，且当前类型是内置类型，直接调用内存操作完成数组元素数目的调整
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GTrueType) noexcept(false)
			{
				return GReallocate<DataT>(old_arr, new_size);
			}

			/// DataT具有内置的移动构造函数，且当前类型是不内置类型，使用拷贝操作代替移动操作
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				if (old_size < new_size)
				{
					for (gsize i = 0; i < old_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[i]);
					}
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[i]);
					}
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(old_arr, old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，由于要析构元素，此时分两种情况考虑
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GTrueType) noexcept(false)
			{
				/// 根据DataT是否是内置类型，调用不同的处理逻辑
				return __GArrayResize(old_arr, old_size, new_size,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT不具有内置的移动构造函数，调用移动构造完成数组元素的构造，多出来的元素调用默认构造函数
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				if (old_size < new_size)
				{
					for (gsize i = 0; i < old_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
					}
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
					}
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(old_arr, old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，且当前类型是内置类型，优先使用内存操作
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GTrueType) noexcept(false)
			{
				DataT *new_arr = GReallocate<DataT>(old_arr, new_size);
				if (old_size < new_size)
				{
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，且当前类型是不内置类型，使用拷贝操作代替移动操作
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				if (old_size < new_size)
				{
					for (gsize i = 0; i < old_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[i]);
					}
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[i]);
					}
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(old_arr, old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，此时分两种情况考虑
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GTrueType) noexcept(false)
			{
				/// 根据DataT是否是内置类型，调用不同的处理逻辑
				return __GArrayResize(old_arr, old_size, new_size, copyable,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT不具有内置的移动构造函数，使用移动操作
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				if (old_size < new_size)
				{
					for (gsize i = 0; i < old_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
					}
					for (gsize i = old_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
					}
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(old_arr, old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，且当前类型是内置类型，优先使用等号操作
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
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
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，且当前类型是不内置类型，使用拷贝操作代替移动操作
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;

				gsize j = old_start;
				if (new_real_size < new_size)
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
					for (gsize i = new_start; i < new_real_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[j++]);
					}
					for (gsize i = new_real_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
					for (gsize i = new_start; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[j++]);
					}
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，此时分两种情况考虑
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) noexcept(false)
			{
				/// 根据DataT是否是内置类型，调用不同的处理逻辑
				return __GArrayResize(old_arr, old_start, old_size, new_size, new_start,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT不具有内置的移动构造函数，使用移动操作
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;
				gsize j = old_start;

				if (new_real_size < new_size)
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
					for (gsize i = new_start; i < new_real_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
					}
					for (gsize i = new_real_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i);
					}
					for (gsize i = new_start; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
					}
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，且当前类型是内置类型，优先使用等号操作
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
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
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，且当前类型是不内置类型，使用拷贝操作代替移动操作
			template <typename DataT> GINLINE DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;

				gsize j = old_start;
				if (new_real_size < new_size)
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
					for (gsize i = new_start; i < new_real_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[j++]);
					}
					for (gsize i = new_real_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
					for (gsize i = new_start; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, old_arr[j++]);
					}
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，此时分两种情况考虑
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GTrueType) noexcept(false)
			{
				/// 根据DataT是否是内置类型，调用不同的处理逻辑
				return __GArrayResize(old_arr, old_start, old_size, new_size, new_start, copyable,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT不具有内置的移动构造函数，使用移动操作
			template <typename DataT> GINLINE DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(new_size);
				gsize new_real_size = new_start + old_size;
				gsize j = old_start;

				if (new_real_size < new_size)
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
					for (gsize i = new_start; i < new_real_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
					}
					for (gsize i = new_real_size; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
				}
				else // old_size >= new_size
				{
					for (gsize i = 0; i < new_start; i++)
					{
						GConstruct<DataT>(new_arr + i, copyable);
					}
					for (gsize i = new_start; i < new_size; i++)
					{
						GConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
					}
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(old_arr, old_start + old_size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，且当前类型是内置类型，使用内存拷贝
			template <typename DataT> GINLINE DataT *__GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GTrueType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size - 1);
				if (pos > 0)
				{
					GMemCopy(new_arr, arr, pos);
				}
				GMemCopy(new_arr + pos, arr + pos + 1, size - pos - 1);

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(arr, size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，且当前类型是内置类型，使用拷贝操作
			template <typename DataT> GINLINE DataT *__GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size - 1);
				for (gsize i = 0; i < pos; i++)
				{
					GConstruct<DataT>(new_arr + i, arr[i]);
				}
				for (gsize i = pos + 1; i < size; i++)
				{
					GConstruct<DataT>(new_arr + i - 1, arr[i]);
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(arr, size);
				return new_arr;
			}

			/// DataT具有内置的移动构造函数，此时分两种情况考虑
			template <typename DataT> GINLINE DataT *_GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GTrueType) noexcept(false)
			{
				/// 根据DataT是否是内置类型，调用不同的处理逻辑
				return __GArrayRemoveAt(arr, size, pos,
					GTypeTraits<DataT>::Arithmetic());
			}

			/// DataT不具有内置的移动构造函数，使用移动操作
			template <typename DataT> GINLINE DataT *_GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GFalseType) noexcept(false)
			{
				DataT *new_arr = GAllocate<DataT>(size - 1);
				for (gsize i = 0; i < pos; i++)
				{
					GConstruct<DataT>(new_arr + i, GMove(arr[i]));
				}
				for (gsize i = pos + 1; i < size; i++)
				{
					GConstruct<DataT>(new_arr + i - 1, GMove(arr[i]));
				}

				// 销毁旧的数组
				GArray<DataT>::DestoryArray(arr, size);
				return new_arr;
			}

			/// DataT不具有内置的析构函数，不析构
			template <typename DataT> GINLINE gvoid _GArrayClear(DataT *arr, gsize size, GTrueType) noexcept
			{

			}

			/// DataT不具有内置的析构函数，依次调用析构函数
			template <typename DataT> GINLINE gvoid _GArrayClear(DataT *arr, gsize size, GFalseType) noexcept
			{
				if (!arr)
				{
					return;
				}
				for (gsize i = 0; i < size; i++)
				{
					arr[i].~DataT();
				}
			}

			/// DataT是内置类型，无需析构，并直接使用内存拷贝
			template <typename DataT> GINLINE gvoid _GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, GTrueType)
			{
				GMemCopy(arr, copy_arr, size);
			}

			/// DataT不是内置类型，先析构，在调用拷贝构造
			template <typename DataT> GINLINE gvoid _GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, GFalseType) noexcept(false)
			{
				for (gsize i = 0; i < size; i++)
				{
					// 析构原有元素
					GDestruct<DataT>(arr + i);

					// 拷贝构造新的元素
					GConstruct<DataT>(arr + i, copy_arr[i]);
				}
			}

			/// DataT是内置类型，无需析构，并直接使用内存拷贝
			template <typename DataT> GINLINE DataT *_GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size, GTrueType) noexcept(false)
			{
				if (size != copy_size)
				{
					GDeallocate<DataT>(arr);
					arr = GAllocate<DataT>(copy_size);
				}

				GMemCopy(arr, copy_arr, copy_size);
				return arr;
			}

			/// DataT不是内置类型，先析构，再调用拷贝构造
			template <typename DataT> GINLINE DataT *_GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size, GFalseType) noexcept(false)
			{
				for (gsize i = 0; i < size; i++)
				{
					GDestruct<DataT>(arr + i);
				}
				if (size != copy_size)
				{
					GDeallocate<DataT>(arr);
					arr = GAllocate<DataT>(copy_size);
				}
				for (gsize i = 0; i < copy_size; i++)
				{
					GConstruct<DataT>(arr + i, copy_arr[i]);
				}
				return arr;
			}

		}
	}
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CreateArray(gsize size) noexcept(false)
{
	GASSERT(size > 0);

	/// 根据DataT是否具有内置的默认构造函数，去调用不同的处理逻辑
	return GNova::Array::Private::_GArrayCreate<DataT>(size,
		GTypeTraits<DataT>::TrivialDefaultConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CreateArray(gsize size, const DataT &copyable) noexcept(false)
{
	GASSERT(size > 0);

	DataT *arr = GAllocate<DataT>(size);
	for (gsize i = 0; i < size; i++)
	{
		// 在GConstruct的调用过程中，已经处理了针对内置类型的处理逻辑
		GConstruct<DataT>(arr + i, copyable);
	}
	return arr;
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CreateArray(const DataT *copy_arr, gsize copy_start, gsize copy_size) noexcept(false)
{
	// 若copy_arr不存在，或者copy_start超过了范围，则会报错
	GASSERT(copy_arr && copy_start < copy_size);

	// 根据DataT是否是内置类型，去调用不同的处理逻辑
	return GNova::Array::Private::_GArrayCreate<DataT>(copy_arr, copy_start, copy_size,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CreateArray(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size) noexcept(false)
{
	GASSERT(start < size && copy_arr && copy_start < copy_size);

	// 根据DataT是否是内置类型，去调用不同的处理逻辑
	return GNova::Array::Private::_GArrayCreate(size, start, copy_arr, copy_start, copy_size,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::ResizeArray(DataT *old_arr, gsize old_size, gsize new_size) noexcept(false)
{
	// 判断DataT是否具有移动构造函数，以判断是否需要调用不同的函数
	return GNova::Array::Private::_GArrayResize<DataT>(old_arr, old_size, new_size,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::ResizeArray(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable) noexcept(false)
{
	// 判断DataT是否具有移动构造函数，以判断是否需要调用不同的函数
	return GNova::Array::Private::_GArrayResize<DataT>(old_arr, old_size, new_size, copyable,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start) noexcept(false)
{
	GASSERT(old_start < old_size);

	// 判断DataT是否具有移动构造函数，以判断是否需要调用不同的函数
	return GNova::Array::Private::_GArrayResize<DataT>(old_arr, old_start, old_size, new_size, new_start,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable) noexcept(false)
{
	// 判断DataT是否具有移动构造函数，以判断是否需要调用不同的函数
	return GNova::Array::Private::_GArrayResize<DataT>(old_arr, old_start, old_size, new_size, new_start, copyable,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::RemoveArrayElementAt(DataT *arr, gsize size, gsize pos) noexcept(false)
{
	GASSERT(size > 0 && pos < size);

	// 判断DataT是否具有移动构造函数，以判断是否需要调用不同的函数
	return GNova::Array::Private::_GArrayRemoveAt(arr, size, pos,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT>
GINLINE gvoid GArray<DataT>::ClearArray(DataT *arr, gsize size) noexcept
{
	GNova::Array::Private::_GArrayClear(arr, size,
		GTypeTraits<DataT>::TrivialDestructible());
}

template <typename DataT>
GINLINE gvoid GArray<DataT>::DestoryArray(DataT *arr, gsize size) noexcept
{
	// 判断DataT是否具有析构函数，以判断是否需要调用不同的函数
	GNova::Array::Private::_GArrayClear(arr, size,
		GTypeTraits<DataT>::TrivialDestructible());

	// 释放内存
	GDeallocate<DataT>(arr);
}

template <typename DataT>
GINLINE gvoid GArray<DataT>::CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr) noexcept(false)
{
	GASSERT(arr && copy_arr);

	// 判断DataT是否是基本类型，以判断是否需要调用不同的函数
	GNova::Array::Private::_GArrayCopyFrom<DataT>(arr, size, copy_arr,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT>
GINLINE DataT *GArray<DataT>::CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size) noexcept(false)
{
	GASSERT(arr && copy_arr);

	// 判断DataT是否是基本类型，以判断是否需要调用不同的函数
	return GNova::Array::Private::_GArrayCopyFrom<DataT>(arr, size, copy_arr, copy_size,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT>
GINLINE gbool GArray<DataT>::Contains(const DataT &data) const
{
	gsize size = Size();
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			return true;
		}
	}
	return false;
}

template <typename DataT>
GINLINE gsize GArray<DataT>::FirstIndexOf(const DataT &data) const
{
	gsize size = Size();
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			return i;
		}
	}
	return NULL_POS;
}

template <typename DataT>
GINLINE gsize GArray<DataT>::LastIndexOf(const DataT &data) const
{
	gsize size = Size();
	for (gsize i = size; i > 0; i--)
	{
		// 注意不能让i减到0
		if (GetAt(i - 1) == data)
		{
			return i - 1;
		}
	}
	return NULL_POS;
}

template <typename DataT>
GINLINE gsize GArray<DataT>::CountOf(const DataT &data) const
{
	gsize size = Size();
	gsize count = 0;
	for (gsize i = 0; i < size; i++)
	{
		if (GetAt(i) == data)
		{
			count++;
		}
	}
	return count;
}

template <typename DataT>
GINLINE guint GArray<DataT>::ClassCode() const
{
	return GArray<DataT>::CLASS_CODE;
}

#endif // _CORE_ARRAY_INLINE_