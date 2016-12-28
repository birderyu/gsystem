// 使用双向队列实现
#ifndef _CORE_LIST_H_
#define _CORE_LIST_H_

#include "CsDoubleLinkedList.h"

template <typename DataT>
class CsList final
	: public CsListT<CsList<DataT>>
	, public CsObject
{
public:
	struct CsListNode
		: public CsPreviousNextNodeT<CsListNode>
		, public CsDataNodeT<DataT>
		, public CsNewT<CsListNode>
	{
		CsListNode(const DataT &data = DataT(),
			CsListNode *previous = NULL,
			CsListNode *next = NULL)
			: CsPreviousNextNodeT<CsListNode>(previous, next)
			, CsDataNodeT<DataT>(data)
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
		inline DataT &operator[](cs_size_t i) const 
		{ 
			CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			CS_ASSERT(node);
			return node->m_tData;
		}
		inline cs_bool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		inline cs_bool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }
		inline cs_bool operator<(const Iterator &iter) const { return m_pNode < iter.m_pNode; }
		inline cs_bool operator<=(const Iterator &iter) const { return m_pNode <= iter.m_pNode; }
		inline cs_bool operator>(const Iterator &iter) const { return m_pNode > iter.m_pNode; }
		inline cs_bool operator>=(const Iterator &iter) const { return m_pNode >= iter.m_pNode; }
		inline cs_bool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		inline cs_bool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		inline cs_bool operator<(const ConstIterator &citer) const { return m_pNode < citer.m_pNode; }
		inline cs_bool operator<=(const ConstIterator &citer) const { return m_pNode <= citer.m_pNode; }
		inline cs_bool operator>(const ConstIterator &citer) const { return m_pNode > citer.m_pNode; }
		inline cs_bool operator>=(const ConstIterator &citer) const { return m_pNode >= citer.m_pNode; }
		inline Iterator &operator++() 
		{
			CS_ASSERT(m_pNode);
			m_pNode = m_pNode->m_pNext; 
			return *this; 
		}
		inline Iterator operator++(cs_int)
		{
			CS_ASSERT(m_pNode);
			CsListNode *node = m_pNode; 
			m_pNode = m_pNode->m_pNext; 
			return node; 
		}
		inline Iterator &operator--() 
		{
			CS_ASSERT(m_pNode);
			m_pNode = m_pNode->m_pPrevious; 
			return *this; 
		}
		inline Iterator operator--(cs_int) 
		{
			CS_ASSERT(m_pNode);
			CsListNode *node = m_pNode; 
			m_pNode = m_pNode->m_pPrevious; 
			return node; 
		}
		inline Iterator &operator+=(cs_size_t i)
		{
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pNext;
				i--;
			}
			return *this;
		}
		inline Iterator &operator-=(cs_size_t i) 
		{ 
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pPrevious;
				i--;
			}
			return *this;
		}
		inline Iterator operator+(cs_size_t i) const
		{
			CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			return Iterator(node);
		}
		inline Iterator operator-(cs_size_t i) const
		{
			CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pPrevious;
				i--;
			}
			return Iterator(node);
		}
		inline cs_int operator-(const Iterator &iter) const
		{
			CsListNode *pnode = m_pNode;
			CsListNode *nnode = m_pNode;
			cs_int i = 0;
			cs_int j = 0;
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
			return CsList<DataT>::NULL_POS;
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
		inline const DataT &operator[](cs_size_t i) const
		{
			const CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			CS_ASSERT(node);
			return node->m_tData;
		}
		inline cs_bool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		inline cs_bool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		inline cs_bool operator<(const ConstIterator &citer) const { return m_pNode < citer.m_pNode; }
		inline cs_bool operator<=(const ConstIterator &citer) const { return m_pNode <= citer.m_pNode; }
		inline cs_bool operator>(const ConstIterator &citer) const { return m_pNode > citer.m_pNode; }
		inline cs_bool operator>=(const ConstIterator &citer) const { return m_pNode >= citer.m_pNode; }
		inline ConstIterator &operator++()
		{
			CS_ASSERT(m_pNode);
			m_pNode = m_pNode->m_pNext;
			return *this;
		}
		inline ConstIterator operator++(cs_int)
		{
			CS_ASSERT(m_pNode);
			const CsListNode *node = m_pNode;
			m_pNode = m_pNode->m_pNext;
			return node;
		}
		inline ConstIterator &operator--()
		{
			CS_ASSERT(m_pNode);
			m_pNode = m_pNode->m_pPrevious;
			return *this;
		}
		inline ConstIterator operator--(cs_int)
		{
			CS_ASSERT(m_pNode);
			const CsListNode *node = m_pNode;
			m_pNode = m_pNode->m_pPrevious;
			return node;
		}
		inline ConstIterator &operator+=(cs_size_t i)
		{
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pNext;
				i--;
			}
			return *this;
		}
		inline ConstIterator &operator-=(cs_size_t i)
		{
			while (i && m_pNode)
			{
				m_pNode = m_pNode->m_pPrevious;
				i--;
			}
			return *this;
		}
		inline ConstIterator operator+(cs_size_t i) const
		{
			const CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pNext;
				i--;
			}
			return ConstIterator(node);
		}
		inline ConstIterator operator-(cs_size_t i) const
		{
			const CsListNode *node = m_pNode;
			while (node && i)
			{
				node = node->m_pPrevious;
				i--;
			}
			return ConstIterator(node);
		}
		inline cs_int operator-(const ConstIterator &citer) const
		{
			const CsListNode *pnode = m_pNode;
			const CsListNode *nnode = m_pNode;
			cs_int i = 0, j = 0;
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
			return CsList<DataT>::NULL_POS;
		}

	private:
		const CsListNode *m_pNode;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	CsList();
	explicit CsList(cs_size_t size, const DataT &data = DataT());
	CsList(const CsList<DataT> &);

	cs_bool Resize(cs_size_t);
	cs_size_t Size() const;
	cs_bool IsEmpty() const;
	cs_void Clear();

	DataT &GetAt(cs_size_t);
	const DataT &GetAt(cs_size_t) const;

	DataT &operator[](cs_size_t);
	const DataT &operator[](cs_size_t) const;

	cs_void PushBack(const DataT &data);
	cs_void PushFront(const DataT &data);
	cs_void PopBack();
	cs_void PopFront();

	cs_void	Append(const DataT &);
	cs_void	Append(const CsList<DataT> &);

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

	cs_bool StartWith(const DataT &) const;
	cs_bool EndWith(const DataT &) const;

private:
	CsDoubleLinkedList<DataT, CsListNode> m_tList;
};








#include "CsList.inl"

#endif // _CORE_LIST_H_