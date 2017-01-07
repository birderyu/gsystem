#ifndef _SORT_STACK_H_
#define _SORT_STACK_H_

#include <string.h>

/// 有序栈
template <typename T>
class CSortStack
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;

public:
	CSortStack();
	~CSortStack();

public:
	/// 分配容量
	/// 只分配容量，超出有效范围的数据依然是无效的
	bool reserve(const size_t len);

	/// 有效数据的长度
	size_t size() const;

	/// 容量
	size_t capacity() const;

	/// 是否为空
	bool empty() const;

	/// 清空记录
	void clear();

	/// 插入一条记录
	bool insert(const T &t);

	/// 删除一条记录
	bool remove(const T &t);

	/// 根据下标删除一条记录
	bool removeAt(const size_t id);

	/// 查找某条数据，返回其下标，返回-1表示该数据不存在
	int search(const T &t) const;

	/// 取尾记录的迭代器
	inline const_iterator cfind(const T &t) const
	{
		int id = search(t);
		if (id < 0)
		{
			return NULL;
		}
		return at(id);
	}

	/// 取出首记录，返回该记录的迭代器
	inline const_iterator pop_front()
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + m_nHead++;
	}

	/// 取出尾记录，返回该记录的迭代器
	inline const_iterator pop_back()
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + (m_nTail--) - 1;
	}

	/// 取首记录的迭代器
	inline const_iterator cbegin() const
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + m_nHead;
	}

	/// 取尾记录的迭代器
	inline const_iterator cend() const
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + m_nTail;
	}

	/// 获取指定位置的迭代器
	inline const_iterator at(const size_t id) const
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + real_id(id);
	}

	/// 通过下标获取数据（只读）
	inline const T &operator[](const size_t id) const
	{
		return *(m_pData + real_id(id));
	}
	
private:
	/// 分配有效数据
	/// 使用默认构造函数分配有效数据，范围内的数据都是有效的
	bool resize(const size_t len);

	/// 是否有效
	bool valid() const;

	/// 获取插入数据的位置
	size_t insertPos(const T &t) const;

	/// 在指定位置插入一条数据
	bool insertAt(const size_t id, const T &t);

	/// 拷贝部分内存至pData，pData需要是一块已经分配的合法内存
	bool copyPartTo(const size_t start, const size_t len, T *pData) const;

	/// 实际ID
	size_t real_id(const size_t id) const;

private:
	// 内存块首地址
	T *m_pData;

	// 头指针，指向首元素，默认情况下指向-1
	int m_nHead; 

	// 尾指针，指向末尾元素的下一位，默认情况下指向-1
	int m_nTail;

	// 内存的长度
	size_t m_nMemSize; 
};

template <typename T>
CSortStack<T>::CSortStack()
:m_pData(NULL), m_nHead(-1), m_nTail(-1), m_nMemSize(0)
{

}

template <typename T>
CSortStack<T>::~CSortStack()
{
	clear();
}

template <typename T>
bool CSortStack<T>::reserve(const size_t len)
{
	if (len <= capacity())
	{
		// 无需扩容
		return true;
	}

	T *pData = (T*)malloc(sizeof(T)* len);
	if (!pData)
	{
		// 扩容失败
		return false;
	}

	size_t n_size = size();
	if (m_pData && n_size > 0)
	{
		// 备份旧的数据（只备份有效数据）
		if (!copyPartTo(m_nHead, n_size, pData))
		{
			return false;
		}
	}

	clear();
	m_pData = pData;
	m_nHead = 0;
	m_nTail = n_size;
	m_nMemSize = len;
	return true;
}

template <typename T>
bool CSortStack<T>::resize(const size_t len)
{
	if (len <= size())
	{
		return true;
	}
	if (len > capacity())
	{
		if (!reserve(len))
		{
			return false;
		}
	}
	for (size_t i = m_nTail; i < len - m_nHead; i++)
	{
		m_pData[i] = T();
	}
	m_nTail = len - m_nHead;
	return true;
}

template <typename T>
size_t CSortStack<T>::size() const
{
	if (m_nHead < 0 || m_nTail <= m_nHead)
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename T>
size_t CSortStack<T>::capacity() const
{
	if (m_nHead < 0 || m_nMemSize <= m_nHead)
	{
		return 0;
	}
	return m_nMemSize - m_nHead;
}

template <typename T>
bool CSortStack<T>::empty() const
{
	return m_pData == NULL || size() == 0;
}

template <typename T>
void CSortStack<T>::clear()
{
	if (m_pData)
	{
		free(m_pData);
		m_pData = NULL;
	}
	m_nHead = m_nTail = -1;
	m_nMemSize = 0;
}

template <typename T>
bool CSortStack<T>::insert(const T &t)
{
	return insertAt(insertPos(t), t);
}

template <typename T>
bool CSortStack<T>::remove(const T &t)
{
	int id = search(t);
	if (id < 0)
	{
		return false;
	}
	return removeAt(id);
}

template <typename T>
bool CSortStack<T>::removeAt(const size_t id)
{
	size_t n_real_id = real_id(id);
	if (n_real_id < m_nHead || n_real_id >= m_nTail)
	{
		// 无效数据，无需删除
		return true;
	}

	// 首尾直接移动指针
	if (n_real_id == m_nHead)
	{
		return pop_front() != NULL;
	}
	if (n_real_id == m_nTail - 1)
	{
		return pop_back() != NULL;
	}

	// 其他位置，将数据后移
	T bakup(m_pData[n_real_id]);
	if (!copyPartTo(n_real_id + 1, m_nTail - n_real_id - 1, m_pData + n_real_id))
	{
		return false;
	}
	m_nTail--;
	memcpy(m_pData + m_nTail, &bakup, sizeof(T));
	return true;
}

template <typename T>
int CSortStack<T>::search(const T &t) const
{
	if (!valid()
		|| t < m_pData[m_nHead]
		|| t > m_pData[m_nTail - 1])
	{
		return -1;
	}

	size_t start = m_nHead;
	size_t end = m_nTail - 1;
	while (start <= end)
	{
		size_t middle = start + ((end - start) >> 1);
		if (t == m_pData[middle])
		{
			return middle - m_nHead;
		}
		else if (t > m_pData[middle])
		{
			start = middle + 1;
		}
		else
		{
			end = middle - 1;
		}
	}
	return -1;
}

template <typename T>
bool CSortStack<T>::valid() const
{
	return m_pData != NULL && m_nHead >= 0 && m_nTail > m_nHead && m_nTail <= m_nMemSize;
}

template <typename T>
size_t CSortStack<T>::insertPos(const T &t) const
{
	if (!valid()
		|| t < m_pData[m_nHead])
	{
		return 0;
	}
	if (t > m_pData[m_nTail - 1])
	{
		return m_nTail;
	}

	size_t start = m_nHead;
	size_t end = m_nTail - 1;

	while (start <= end)
	{
		size_t middle = start + ((end - start) >> 1);
		if (t == m_pData[middle] ||
			(middle - 1 >= m_nHead && t > m_pData[middle - 1] && t < m_pData[middle]))
		{
			return middle;
		}
		else if (t > m_pData[middle])
		{
			start = middle + 1;
		}
		else
		{
			end = middle - 1;
		}
	}
	return 0;
}

template <typename T>
bool CSortStack<T>::insertAt(const size_t id, const T &t)
{
	if (id >= capacity())
	{
		reserve(capacity() + 1);
	}
	size_t n_real_id = real_id(id); // 实际下标（m_nHead + id）
	if (m_nTail < m_nMemSize)
	{
		// 不需要创建新的内存，直接后移
		if (copyPartTo(n_real_id, m_nTail - n_real_id, m_pData + n_real_id + 1))
		{
			m_pData[n_real_id] = t;
			m_nTail++;
		}
	}
	else
	{
		// 创建新的内存
		size_t len = size() + 1; // 新内存的长度（m_nTail - m_nHead + 1）
		T *pData = (T*)malloc(sizeof(T)* len);
		if (!pData)
		{
			// 新内存分配失败
			return false;
		}
		if (copyPartTo(m_nHead, id, pData))
		{
			if (copyPartTo(m_nHead + id, m_nTail - m_nHead - id, pData + id + 1))
			{
				clear();
				m_pData = pData;
				m_nHead = 0;
				m_nTail = len;
				m_nMemSize = len;
				m_pData[id] = t;
				return true;
			}
		}
	}
	return false;
}

template <typename T>
bool CSortStack<T>::copyPartTo(const size_t start, const size_t len, T *pData) const
{
	if (!pData || !m_pData || start >= m_nMemSize || len + start > m_nMemSize)
	{
		return false;
	}
	memcpy(pData, m_pData + start, sizeof(T)* len);
	return true;
}

template <typename T>
size_t CSortStack<T>::real_id(const size_t id) const
{
	return m_nHead + id;
}

#endif // _SORT_STACK_H_