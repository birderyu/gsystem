// 使用双向队列实现
#ifndef _CORE_LIST_H_
#define _CORE_LIST_H_

#include "gdoublelinkedlist.h"

template <typename DataT>
class GList final
	: public GListT<GList<DataT>>
	, public GObject
{
public:
	struct CsListNode
		: public GPreviousNextNodeT<CsListNode>
		, public GDataNodeT<DataT>
		, public GNewT<CsListNode>
	{
		CsListNode(const DataT &data = DataT(),
			CsListNode *previous = NULL,
			CsListNode *next = NULL)
			: GPreviousNextNodeT<CsListNode>(previous, next)
			, GDataNodeT<DataT>(data)
		{

		}
	};
	typedef CsListNode Node;

public:
	class ConstIterator;
	class Iterator 
	{
		friend class ConstIterator;
	public:
		inline Iterator() : m_pNode(NULL) {}
		inline Iterator(CsListNode *node) : m_pNode(node) {}
		inline Iterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}

		inline DataT &operator*() const { return m_pNode->m_tData; }
		inline DataT *operator->() const { return &m_pNode->m_tData; }
		inline DataT &operator[](gsize i) const 
		{ 
			CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			GASSERT(node);
			return node->m_tData;
		}
		inline gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		inline gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }
		inline gbool operator<(const Iterator &iter) const { return m_pNode < iter.m_pNode; }
		inline gbool operator<=(const Iterator &iter) const { return m_pNode <= iter.m_pNode; }
		inline gbool operator>(const Iterator &iter) const { return m_pNode > iter.m_pNode; }
		inline gbool operator>=(const Iterator &iter) const { return m_pNode >= iter.m_pNode; }
		inline gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		inline gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		inline gbool operator<(const ConstIterator &citer) const { return m_pNode < citer.m_pNode; }
		inline gbool operator<=(const ConstIterator &citer) const { return m_pNode <= citer.m_pNode; }
		inline gbool operator>(const ConstIterator &citer) const { return m_pNode > citer.m_pNode; }
		inline gbool operator>=(const ConstIterator &citer) const { return m_pNode >= citer.m_pNode; }
		inline Iterator &operator++() 
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->m_pNext; 
			return *this; 
		}
		inline Iterator operator++(gint)
		{
			GASSERT(m_pNode);
			CsListNode *node = m_pNode; 
			m_pNode = m_pNode->m_pNext; 
			return node; 
		}
		inline Iterator &operator--() 
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->m_pPrevious; 
			return *this; 
		}
		inline Iterator operator--(gint) 
		{
			GASSERT(m_pNode);
			CsListNode *node = m_pNode; 
			m_pNode = m_pNode->m_pPrevious; 
			return node; 
		}
		inline Iterator &operator+=(gsize i)
		{
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pNext;
				i--;
			}
			return *this;
		}
		inline Iterator &operator-=(gsize i) 
		{ 
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pPrevious;
				i--;
			}
			return *this;
		}
		inline Iterator operator+(gsize i) const
		{
			CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			return Iterator(node);
		}
		inline Iterator operator-(gsize i) const
		{
			CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pPrevious;
				i--;
			}
			return Iterator(node);
		}
		inline gint operator-(const Iterator &iter) const
		{
			CsListNode *pnode = m_pNode;
			CsListNode *nnode = m_pNode;
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
		CsListNode *m_pNode;
	};

	class ConstIterator
	{
		friend class Iterator;
	public:
		inline ConstIterator() : m_pNode(NULL) {}
		inline ConstIterator(const CsListNode *node) : m_pNode(const_cast<CsListNode*>(node)) {}
		inline ConstIterator(const ConstIterator &citer) : m_pNode(iter.m_pNode) {}
		explicit inline ConstIterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}

		inline const DataT &operator*() const { return m_pNode->m_tData; }
		inline const DataT *operator->() const { return &m_pNode->m_tData; }
		inline const DataT &operator[](gsize i) const
		{
			const CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			GASSERT(node);
			return node->m_tData;
		}
		inline gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		inline gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		inline gbool operator<(const ConstIterator &citer) const { return m_pNode < citer.m_pNode; }
		inline gbool operator<=(const ConstIterator &citer) const { return m_pNode <= citer.m_pNode; }
		inline gbool operator>(const ConstIterator &citer) const { return m_pNode > citer.m_pNode; }
		inline gbool operator>=(const ConstIterator &citer) const { return m_pNode >= citer.m_pNode; }
		inline ConstIterator &operator++()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->m_pNext;
			return *this;
		}
		inline ConstIterator operator++(gint)
		{
			GASSERT(m_pNode);
			const CsListNode *node = m_pNode;
			m_pNode = m_pNode->m_pNext;
			return node;
		}
		inline ConstIterator &operator--()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->m_pPrevious;
			return *this;
		}
		inline ConstIterator operator--(gint)
		{
			GASSERT(m_pNode);
			const CsListNode *node = m_pNode;
			m_pNode = m_pNode->m_pPrevious;
			return node;
		}
		inline ConstIterator &operator+=(gsize i)
		{
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pNext;
				i--;
			}
			return *this;
		}
		inline ConstIterator &operator-=(gsize i)
		{
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pPrevious;
				i--;
			}
			return *this;
		}
		inline ConstIterator operator+(gsize i) const
		{
			const CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			return ConstIterator(node);
		}
		inline ConstIterator operator-(gsize i) const
		{
			const CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pPrevious;
				i--;
			}
			return ConstIterator(node);
		}
		inline gint operator-(const ConstIterator &citer) const
		{
			const CsListNode *pnode = m_pNode;
			const CsListNode *nnode = m_pNode;
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
		const CsListNode *m_pNode;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	GList();
	explicit GList(gsize size, const DataT &data = DataT());
	GList(const GList<DataT> &);

	gbool Resize(gsize);
	gsize Size() const;
	gbool IsEmpty() const;
	gvoid Clear();

	DataT &GetAt(gsize);
	const DataT &GetAt(gsize) const;

	DataT &operator[](gsize);
	const DataT &operator[](gsize) const;

	gvoid PushBack(const DataT &data);
	gvoid PushFront(const DataT &data);
	gvoid PopBack();
	gvoid PopFront();

	gvoid	Append(const DataT &);
	gvoid	Append(const GList<DataT> &);

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
	GDoubleLinkedList<DataT, CsListNode> m_tList;
};

#include "glist.inl"

#endif // _CORE_LIST_H_