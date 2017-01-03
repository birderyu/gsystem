// ”––ÚMap
#ifndef _CORE_ORDER_MAP_H_
#define _CORE_ORDER_MAP_H_

#include "CsReadBlackTree.h"

#define CS_ORDER_MAP_NODE_RED	0
#define CS_ORDER_MAP_NODE_BLACK	1

template<typename KeyT, typename ValueT,
	typename CompareT = CsCompareToF<KeyT >>
class CsOrderMap 
	: public CsObject
{
public:
	struct CsOrderMapNode
		: public CsBinaryTreeNodeT<CsOrderMapNode>
		, public CsPairNodeT<KeyT, ValueT>
		, public CsNewT<CsOrderMapNode>
	{
		cs_small m_nColor;

		CsOrderMapNode(
			const KeyT &key = KeyT(),
			const ValueT &value = ValueT(),
			CsOrderMapNode *parent = NULL,
			CsOrderMapNode *left = NULL,
			CsOrderMapNode *right = NULL,
			cs_small color = CS_ORDER_MAP_NODE_RED)
			: CsBinaryTreeNodeT<CsOrderMapNode>(parent, left, right)
			, CsPairNodeT<KeyT, ValueT>(key, value)
			, m_nColor(color)
		{

		}
	};
	typedef CsOrderMapNode Node;

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		Iterator() : m_pNode(NULL) {}
		Iterator(CsOrderMapNode *node = NULL) : m_pNode(node) {}
		Iterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}
		inline const KeyT &Key() const { CS_ASSERT(m_pNode); return m_pNode->m_tKey; }
		inline ValueT &Value() const { CS_ASSERT(m_pNode); return m_pNode->m_tValue; }
		inline ValueT &operator*() const { CS_ASSERT(m_pNode); return m_pNode->m_tValue; }
		inline ValueT *operator->() const { CS_ASSERT(m_pNode); return &m_pNode->m_tValue; }
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
			CsOrderMapNode *node = m_pNode;
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
			CsOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return Iterator(node);
		}
		inline Iterator operator+(cs_int i) const
		{
			CsOrderMapNode *node = m_pNode;
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
		CsOrderMapNode *m_pNode;
	};
	friend class Iterator;

	class ConstIterator
	{
		friend class Iterator;
	public:
		inline ConstIterator() : m_pNode(0) { }
		inline ConstIterator(const CsOrderMapNode *node) : m_pNode(node) {}
		inline ConstIterator(const ConstIterator &citer) : m_pNode(citer.m_pNode) {}
		explicit inline ConstIterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}
		inline const KeyT &Key() const { CS_ASSERT(m_pNode); return m_pNode->m_tKey; }
		inline const ValueT &Value() const { CS_ASSERT(m_pNode); return m_pNode->m_tValue; }
		inline const ValueT &operator*() const { CS_ASSERT(m_pNode); return m_pNode->m_tValue; }
		inline const ValueT *operator->() const { CS_ASSERT(m_pNode); return &m_pNode->m_tValue; }
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
			const CsOrderMapNode *node = m_pNode;
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
			const CsOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return ConstIterator(node);
		}
		inline ConstIterator operator+(cs_int i) const
		{
			const CsOrderMapNode *node = m_pNode;
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
		const CsOrderMapNode *m_pNode;
	};
	friend class ConstIterator;

public:
	CsOrderMap();
	CsOrderMap(const CsOrderMap<KeyT, ValueT, CompareT> &);

	cs_size_t Size() const;
	cs_bool IsEmpty() const;
	cs_void Clear();
	cs_bool Contains(const KeyT &key) const;

	ValueT &First();
	const ValueT &First() const;
	const KeyT &FirstKey() const;
	ValueT &Last();
	const ValueT &Last() const;
	const KeyT &LastKey() const;

	cs_void Remove(const KeyT &);

	KeyT Key(const ValueT &value, const KeyT &defaultKey = KeyT()) const;
	ValueT Value(const KeyT &key, const ValueT &defaultValue = ValueT()) const;

	Iterator Begin();
	ConstIterator Begin() const;
	ConstIterator ConstBegin() const;
	Iterator End();
	ConstIterator End() const;
	ConstIterator ConstEnd() const;

	Iterator Find(const KeyT &);
	ConstIterator Find(const KeyT &) const;
	ConstIterator ConstFind(const KeyT &) const;

	Iterator Insert(const KeyT &, const ValueT &);
	Iterator Erase(const Iterator &);

	CsOrderMap<KeyT, ValueT, CompareT> &operator=(const CsOrderMap<KeyT, ValueT, CompareT> &);
	cs_bool operator==(const CsOrderMap<KeyT, ValueT, CompareT> &) const;
	cs_bool operator!=(const CsOrderMap<KeyT, ValueT, CompareT> &) const;
	ValueT &operator[](const KeyT &);
	//const ValueT &operator[](const KeyT &) const;

private:
	CsReadBlackTree<KeyT, ValueT, CompareT, CsOrderMapNode> m_tTree;
	cs_size_t m_nSize;
};

#include "CsOrderMap.inl"

#undef CS_ORDER_MAP_NODE_BLACK
#undef CS_ORDER_MAP_NODE_RED

#endif // _CORE_ORDER_MAP_H_