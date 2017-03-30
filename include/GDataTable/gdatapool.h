// 数据池

#include "GCore/ghashtable.h"

namespace gsystem {
namespace data {

template<typename DataT, gsize GROW_SIZE = 1024>
class GDataPool
{
public:
	GDataPool()
	{

	}

	~GDataPool()
	{
		for (GList<GDynamicArray<DataT> *>::Iterator iter = m_tMemory.Begin();
			iter != m_tMemory.End(); iter++)
		{
			GDynamicArray<DataT> *arr = *iter;
			delete arr;
		}
	}

	DataT *Alloc(gsize size)
	{
		DataT *alloc = GNULL;
		// 优先从回收站中回收内存
		GHashTable<gsize, GArrayStack<DataT *>>::Node *node = m_tRecycle.Find(size);
		if (GNULL == node)
		{
			// 
			if (GNULL == m_pCursor)
			{
				// 重新分配内存
				gsize real_alloc_size = GROW_SIZE > size ? GROW_SIZE : size;
				GDynamicArray<DataT> *arr = new GDynamicArray<DataT>(real_alloc_size);
				m_tMemory.PushBack(arr);
				if (real_alloc_size != size)
				{
					m_pCursor = arr;
					//m_nCursor = 
				}
				return arr->CursorAt(0);
			}
			else
			{

			}
			
		}
		else
		{
			node->m_tValue.Pop(&alloc);
			if (node->m_tValue.IsEmpty())
			{
				m_tRecycle.Delete(size);
			}
		}
		return alloc;
	}

	gvoid Free(DataT *free, gsize size)
	{
		GHashTable<gsize, GArrayStack<DataT *>>::Node *node = m_tRecycle.Find(size);
		if (GNULL == node)
		{
			GArrayStack<DataT *> list;
			list.Push(free);
			m_tRecycle.Insert(size, list);
		}
		else
		{
			node->m_tValue.Push(free);
		}
	}

private:
	// 内存回收站
	GHashTable<gsize, GArrayStack<DataT *>> m_tRecycle;

	// 内存块
	GList<GDynamicArray<DataT> *> m_tMemory;

	// 当前的游标
	GDynamicArray<DataT> *m_pCursor;
	gsize m_nCursor;
};

}
}