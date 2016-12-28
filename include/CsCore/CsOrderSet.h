// ÓÐÐò¼¯ºÏ
#ifndef _CORE_ORDER_SET_H_
#define _CORE_ORDER_SET_H_

#include "CsReadBlackTree.h"

#define CS_ORDER_SET_NODE_RED	0
#define CS_ORDER_SET_NODE_BLACK	1

template < typename KeyT, typename CompareT = CsCompareToF<KeyT>>
class CsOrderSet
	: public CsObject
{
public:
	struct CsOrderSetNode
		: public CsBinaryTreeNodeT<CsOrderSetNode>
		, public CsKeyValueNodeT<KeyT, CsDummyNodeT>
		, public CsNewT<CsOrderSetNode>
	{
		cs_small m_nColor;

		CsOrderSetNode(
			const KeyT &key = KeyT(),
			const CsDummyNodeT &value = CsDummyNodeT(),
			CsOrderSetNode *parent = NULL,
			CsOrderSetNode *left = NULL,
			CsOrderSetNode *right = NULL,
			cs_small color = CS_ORDER_SET_NODE_RED)
			: CsBinaryTreeNodeT<CsOrderSetNode>(parent, left, right)
			, CsKeyValueNodeT<KeyT, CsDummyNodeT>(key, value)
			, m_nColor(color)
		{

		}
	};
	typedef CsOrderSetNode Node;

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		Iterator() : m_pNode(NULL) {}
		Iterator(CsOrderSetNode *node = NULL) : m_pNode(node) {}
		Iterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}

		inline const KeyT &operator*() const { CS_ASSERT(m_pNode); return m_pNode->m_tKey; }
		inline const KeyT *operator->() const { CS_ASSERT(m_pNode); return &m_pNode->m_tKey; }

		inline cs_bool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		inline cs_bool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }
		inline Iterator &operator++()
		{
			CS_ASSERT(m_pNode);
			m_pNode = m_pNode->Next();
			return *this;
		}
		inline Iterator operator++(cs_int)
		{
			CS_ASSERT(m_pNode);
			CsOrderSetNode *node = m_pNode;
			m_pNode = m_pNode->Next();
			return Iterator(node);
		}
		inline Iterator &operator--()
		{
			CS_ASSERT(m_pNode);
			m_pNode = m_pNode->Previous();
			return *this;
		}
		inline Iterator operator--(cs_int) {
			CS_ASSERT(m_pNode);
			CsOrderSetNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return Iterator(node);
		}
		inline Iterator operator+(cs_int i) const
		{
			CsOrderSetNode *node = m_pNode;
			if (i > 0)
			{
				while (i-- && node)
				{
					node = node->Next();
				}
			}
			else if (i < 0)
			{
				while (i++ && node)
				{
					node = node->Previous();
				}
			}
			return Iterator(node);
		}
		inline Iterator operator-(cs_int i) const { return operator+(-i); }
		inline Iterator &operator+=(cs_int i)
		{
			if (i > 0)
			{
				while (i-- && m_pNode)
				{
					m_pNode = m_pNode->Next();
				}
			}
			else if (i < 0)
			{
				while (i++ && m_pNode)
				{
					m_pNode = m_pNode->Previous();
				}
			}
			return *this;
		}
		inline Iterator &operator-=(cs_int i) { return operator+=(-i); }
		inline cs_bool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		inline cs_bool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }

	private:
		CsOrderSetNode *m_pNode;
	};
	friend class Iterator;

	class ConstIterator
	{
		friend class Iterator;
	public:
		inline ConstIterator() : m_pNode(0) { }
		inline ConstIterator(const CsOrderSetNode *node) : m_pNode(node) {}
		inline ConstIterator(const ConstIterator &citer) : m_pNode(citer.m_pNode) {}
		explicit inline ConstIterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}

		inline const KeyT &operator*() const { CS_ASSERT(m_pNode); return m_pNode->m_tKey; }
		inline const KeyT *operator->() const { CS_ASSERT(m_pNode); return &m_pNode->m_tKey; }

		inline cs_bool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		inline cs_bool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		inline ConstIterator &operator++()
		{
			CS_ASSERT(m_pNode);
			m_pNode = m_pNode->Next();
			return *this;
		}
		inline ConstIterator operator++(cs_int)
		{
			CS_ASSERT(m_pNode);
			const CsOrderSetNode *node = m_pNode;
			m_pNode = m_pNode->Next();
			return ConstIterator(node);
		}
		inline ConstIterator &operator--()
		{
			CS_ASSERT(m_pNode);
			m_pNode = m_pNode->Previous();
			return *this;
		}
		inline ConstIterator operator--(cs_int) {
			CS_ASSERT(m_pNode);
			const CsOrderSetNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return ConstIterator(node);
		}
		inline ConstIterator operator+(cs_int i) const
		{
			const CsOrderSetNode *node = m_pNode;
			if (i > 0)
			{
				while (i-- && node)
				{
					node = node->Next();
				}
			}
			else if (i < 0)
			{
				while (i++ && node)
				{
					node = node->Previous();
				}
			}
			return ConstIterator(node);
		}
		inline ConstIterator operator-(cs_int i) const { return operator+(-i); }
		inline ConstIterator &operator+=(cs_int i)
		{
			if (i > 0)
			{
				while (i-- && m_pNode)
				{
					m_pNode = m_pNode->Next();
				}
			}
			else if (i < 0)
			{
				while (i++ && m_pNode)
				{
					m_pNode = m_pNode->Previous();
				}
			}
			return *this;
		}
		inline ConstIterator &operator-=(cs_int i) { return operator+=(-i); }
		inline cs_bool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		inline cs_bool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }

	private:
		const CsOrderSetNode *m_pNode;
	};
	friend class ConstIterator;

public:
	CsOrderSet();
	CsOrderSet(const CsOrderSet<KeyT, CompareT> &);

	cs_size_t Size() const;
	cs_bool IsEmpty() const;
	cs_void Clear();
	cs_bool Contains(const KeyT &key) const;

	const KeyT &First() const;
	const KeyT &Last() const;

	cs_void Remove(const KeyT &);

	Iterator Begin();
	ConstIterator Begin() const;
	ConstIterator ConstBegin() const;
	Iterator End();
	ConstIterator End() const;
	ConstIterator ConstEnd() const;

	Iterator Find(const KeyT &);
	ConstIterator Find(const KeyT &) const;
	ConstIterator ConstFind(const KeyT &) const;

	Iterator Insert(const KeyT &);
	Iterator Erase(const Iterator &);

	CsOrderSet<KeyT, CompareT> &Intersect(const CsOrderSet<KeyT, CompareT> &);
	CsOrderSet<KeyT, CompareT> &Unite(const CsOrderSet<KeyT, CompareT> &);

	cs_bool operator==(const CsOrderSet<KeyT, CompareT> &) const;
	cs_bool operator!=(const CsOrderSet<KeyT, CompareT> &) const;

	CsOrderSet<KeyT, CompareT>  operator&(const CsOrderSet<KeyT, CompareT> &) const;
	CsOrderSet<KeyT, CompareT> &operator&=(const CsOrderSet<KeyT, CompareT> &);
	CsOrderSet<KeyT, CompareT> &operator&=(const KeyT &);

	CsOrderSet<KeyT, CompareT>  operator|(const CsOrderSet<KeyT, CompareT> &) const;
	CsOrderSet<KeyT, CompareT> &operator|=(const CsOrderSet<KeyT, CompareT> &);
	CsOrderSet<KeyT, CompareT> &operator|=(const KeyT &);

	CsOrderSet<KeyT, CompareT>  operator+(const CsOrderSet<KeyT, CompareT> &) const;
	CsOrderSet<KeyT, CompareT> &operator+=(const CsOrderSet<KeyT, CompareT> &);
	CsOrderSet<KeyT, CompareT> &operator+=(const KeyT &);

	CsOrderSet<KeyT, CompareT>  operator-(const CsOrderSet<KeyT, CompareT> &) const;
	CsOrderSet<KeyT, CompareT> &operator-=(const CsOrderSet<KeyT, CompareT> &);
	CsOrderSet<KeyT, CompareT> &operator-=(const KeyT &);

	CsOrderSet<KeyT, CompareT> &operator>>(KeyT &);
	CsOrderSet<KeyT, CompareT> &operator<<(const KeyT &);

	CsOrderSet<KeyT, CompareT> &operator=(const CsOrderSet<KeyT, CompareT> &);

private:
	CsReadBlackTree<KeyT, CsDummyNodeT, CompareT, CsOrderSetNode> m_tTree;
	cs_size_t m_nSize;
};

#include "CsOrderSet.inl"

#undef CS_ORDER_SET_NODE_BLACK
#undef CS_ORDER_SET_NODE_RED

#endif // _CORE_ORDER_SET_H_