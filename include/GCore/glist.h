// 使用双向队列实现
#ifndef _CORE_LIST_H_
#define _CORE_LIST_H_

#include "gdeque.h"
#include "gdlist.h"

namespace gsystem { // gsystem

template <typename DataT>
class GList final
	: public GDeque<DataT>
	, public GObject
{
public:
	struct GListNode
		: public GPreviousNextNodeT<GListNode>
		, public GDataNodeT<DataT>
		, public GNewT<GListNode>
	{
		GListNode(const DataT &data = DataT(),
			GListNode *previous = GNULL,
			GListNode *next = GNULL)
			: GPreviousNextNodeT<GListNode>(previous, next)
			, GDataNodeT<DataT>(data)
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

		GINLINE DataT &operator*() const { return m_pNode->m_tData; }
		GINLINE DataT *operator->() const { return &m_pNode->m_tData; }
		GINLINE DataT &operator[](gsize i) const 
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
			return GList<DataT>::NULL_POS;
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

		GINLINE const DataT &operator*() const { return m_pNode->m_tData; }
		GINLINE const DataT *operator->() const { return &m_pNode->m_tData; }
		GINLINE const DataT &operator[](gsize i) const
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
			return GList<DataT>::NULL_POS;
		}

	private:
		const GListNode *m_pNode;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	GList();
	explicit GList(gsize size, const DataT &data = DataT());
	GList(const GList<DataT> &list);
	GList(GList<DataT> &&list);

	GList<DataT> &operator=(const GList<DataT> &list);
	GList<DataT> &operator=(GList<DataT> &&list);

	gvoid Resize(gsize);
	gsize Size() const;
	gbool IsEmpty() const;
	gvoid Clear();
	gvoid Destroy();

	DataT &GetAt(gsize);
	const DataT &GetAt(gsize) const;

	DataT &operator[](gsize);
	const DataT &operator[](gsize) const;

	gvoid PushBack(const DataT &data);
	gvoid PushBack(DataT &&data);

	gvoid PushFront(const DataT &data);
	gvoid PushFront(DataT &&data);

	gvoid PopBack(DataT *data = GNULL);
	gvoid PopFront(DataT *data = GNULL);

	gvoid Append(const DataT &data);
	gvoid Append(DataT &&data);

	gvoid Append(const GList<DataT> &);
	gvoid Append(GList<DataT> &&);

	Iterator Begin();
	ConstIterator Begin() const;
	ConstIterator ConstBegin() const;
	Iterator End();
	ConstIterator End() const;
	ConstIterator ConstEnd() const;

	DataT &First();
	const DataT &First() const;
	DataT &Last();
	const DataT &Last() const;

	gbool StartWith(const DataT &) const;
	gbool EndWith(const DataT &) const;

private:
	GDList<DataT, GListNode> m_tList;
};

} // namespace gsystem

#include "inline/glist.inl"

#endif // _CORE_LIST_H_