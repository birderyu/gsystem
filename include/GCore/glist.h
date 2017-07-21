// 使用双向队列实现
#ifndef _CORE_LIST_H_
#define _CORE_LIST_H_

#include "gdeque.h"
#include "gdlist.h"

namespace gsystem { // gsystem

template <typename T>
class GList final
	: public GDeque<T>
{
public:
	struct GListNode
		: public GPreviousNextNodeT<GListNode>
		, public GValueNodeT<T>
		, public GNewT<GListNode>
	{
		GListNode(const T &data = T(),
			GListNode *previous = GNULL,
			GListNode *next = GNULL)
			: GPreviousNextNodeT<GListNode>(previous, next)
			, GValueNodeT<T>(data)
		{

		}
	};
	typedef GListNode Node;

public:
	class ConstIterator;
	class Iterator 
	{
		friend class ConstIterator;
	public:
		GINLINE Iterator() : m_pNode(GNULL) {}
		GINLINE Iterator(GListNode *node) : m_pNode(node) {}
		GINLINE Iterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}

		GINLINE T &operator*() const { return m_pNode->m_tData; }
		GINLINE T *operator->() const { return &m_pNode->m_tData; }
		GINLINE T &operator[](gsize i) const 
		{ 
			GListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			GASSERT(node);
			return node->m_tData;
		}
		GINLINE gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		GINLINE gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }
		GINLINE gbool operator<(const Iterator &iter) const { return m_pNode < iter.m_pNode; }
		GINLINE gbool operator<=(const Iterator &iter) const { return m_pNode <= iter.m_pNode; }
		GINLINE gbool operator>(const Iterator &iter) const { return m_pNode > iter.m_pNode; }
		GINLINE gbool operator>=(const Iterator &iter) const { return m_pNode >= iter.m_pNode; }
		GINLINE gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		GINLINE gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		GINLINE gbool operator<(const ConstIterator &citer) const { return m_pNode < citer.m_pNode; }
		GINLINE gbool operator<=(const ConstIterator &citer) const { return m_pNode <= citer.m_pNode; }
		GINLINE gbool operator>(const ConstIterator &citer) const { return m_pNode > citer.m_pNode; }
		GINLINE gbool operator>=(const ConstIterator &citer) const { return m_pNode >= citer.m_pNode; }
		GINLINE Iterator &operator++() 
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->m_pNext; 
			return *this; 
		}
		GINLINE Iterator operator++(gint)
		{
			GASSERT(m_pNode);
			GListNode *node = m_pNode; 
			m_pNode = m_pNode->m_pNext; 
			return node; 
		}
		GINLINE Iterator &operator--() 
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->m_pPrevious; 
			return *this; 
		}
		GINLINE Iterator operator--(gint) 
		{
			GASSERT(m_pNode);
			GListNode *node = m_pNode; 
			m_pNode = m_pNode->m_pPrevious; 
			return node; 
		}
		GINLINE Iterator &operator+=(gsize i)
		{
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pNext;
				i--;
			}
			return *this;
		}
		GINLINE Iterator &operator-=(gsize i) 
		{ 
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pPrevious;
				i--;
			}
			return *this;
		}
		GINLINE Iterator operator+(gsize i) const
		{
			GListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			return Iterator(node);
		}
		GINLINE Iterator operator-(gsize i) const
		{
			GListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pPrevious;
				i--;
			}
			return Iterator(node);
		}
		GINLINE gint operator-(const Iterator &iter) const
		{
			GListNode *pnode = m_pNode;
			GListNode *nnode = m_pNode;
			gint i = 0;
			gint j = 0;
			while (pnode && nnode)
			{
				if (pnode == iter.m_pNode)
				{
					return i;
				}
				if (nnode == iter.m_pNode)
				{
					return j;
				}

				if (pnode)
				{
					pnode = pnode->m_pPrevious;
					i++;
				}

				if (nnode)
				{
					nnode = nnode->m_pPrevious;
					j--;
				}
			}
			return GList<T>::NULL_POS;
		}

	private:
		GListNode *m_pNode;
	};

	class ConstIterator
	{
		friend class Iterator;
	public:
		GINLINE ConstIterator() : m_pNode(GNULL) {}
		GINLINE ConstIterator(const GListNode *node) : m_pNode(const_cast<GListNode*>(node)) {}
		GINLINE ConstIterator(const ConstIterator &citer) : m_pNode(iter.m_pNode) {}
		explicit GINLINE ConstIterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}

		GINLINE const T &operator*() const { return m_pNode->m_tData; }
		GINLINE const T *operator->() const { return &m_pNode->m_tData; }
		GINLINE const T &operator[](gsize i) const
		{
			const GListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			GASSERT(node);
			return node->m_tData;
		}
		GINLINE gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		GINLINE gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		GINLINE gbool operator<(const ConstIterator &citer) const { return m_pNode < citer.m_pNode; }
		GINLINE gbool operator<=(const ConstIterator &citer) const { return m_pNode <= citer.m_pNode; }
		GINLINE gbool operator>(const ConstIterator &citer) const { return m_pNode > citer.m_pNode; }
		GINLINE gbool operator>=(const ConstIterator &citer) const { return m_pNode >= citer.m_pNode; }
		GINLINE ConstIterator &operator++()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->m_pNext;
			return *this;
		}
		GINLINE ConstIterator operator++(gint)
		{
			GASSERT(m_pNode);
			const GListNode *node = m_pNode;
			m_pNode = m_pNode->m_pNext;
			return node;
		}
		GINLINE ConstIterator &operator--()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->m_pPrevious;
			return *this;
		}
		GINLINE ConstIterator operator--(gint)
		{
			GASSERT(m_pNode);
			const GListNode *node = m_pNode;
			m_pNode = m_pNode->m_pPrevious;
			return node;
		}
		GINLINE ConstIterator &operator+=(gsize i)
		{
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pNext;
				i--;
			}
			return *this;
		}
		GINLINE ConstIterator &operator-=(gsize i)
		{
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pPrevious;
				i--;
			}
			return *this;
		}
		GINLINE ConstIterator operator+(gsize i) const
		{
			const GListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			return ConstIterator(node);
		}
		GINLINE ConstIterator operator-(gsize i) const
		{
			const GListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pPrevious;
				i--;
			}
			return ConstIterator(node);
		}
		GINLINE gint operator-(const ConstIterator &citer) const
		{
			const GListNode *pnode = m_pNode;
			const GListNode *nnode = m_pNode;
			gint i = 0, j = 0;
			while (pnode && nnode)
			{
				if (pnode == citer.m_pNode)
				{
					return i;
				}
				if (nnode == citer.m_pNode)
				{
					return j;
				}

				if (pnode)
				{
					pnode = pnode->m_pPrevious;
					i++;
				}

				if (nnode)
				{
					nnode = nnode->m_pPrevious;
					j--;
				}
			}
			return GList<T>::NULL_POS;
		}

	private:
		const GListNode *m_pNode;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	GList();
	explicit GList(gsize size, const T &data = T());
	GList(const GList &list);
	GList(GList &&list);

	GList &operator=(const GList &list);
	GList &operator=(GList &&list);

	gvoid Resize(gsize);
	gsize Size() const;
	gbool IsEmpty() const;
	gvoid Clear();
	gvoid Destroy();

	T &GetAt(gsize);
	const T &GetAt(gsize) const;

	T &operator[](gsize);
	const T &operator[](gsize) const;

	gvoid PushBack(const T &data);
	gvoid PushBack(T &&data);

	gvoid PushFront(const T &data);
	gvoid PushFront(T &&data);

	gvoid PopBack(T *data = GNULL);
	gvoid PopFront(T *data = GNULL);

	gvoid Append(const T &data);
	gvoid Append(T &&data);

	gvoid Append(const GList<T> &);
	gvoid Append(GList<T> &&);

	Iterator Begin();
	ConstIterator Begin() const;
	ConstIterator ConstBegin() const;
	Iterator End();
	ConstIterator End() const;
	ConstIterator ConstEnd() const;

	T &First();
	const T &First() const;
	T &Last();
	const T &Last() const;

	gbool StartWith(const T &) const;
	gbool EndWith(const T &) const;

private:
	GDList<T, GListNode> m_tList;
};

} // namespace gsystem

#include "inline/glist.inl"

#endif // _CORE_LIST_H_