// ”––ÚMap
#ifndef _CORE_ORDER_MAP_H_
#define _CORE_ORDER_MAP_H_

#include "greadblacktree.h"

#define CS_ORDER_MAP_NODE_RED	0
#define CS_ORDER_MAP_NODE_BLACK	1

template<typename KeyT, typename ValueT,
	typename CompareT = GCompareToF<KeyT >>
class GOrderMap 
	: public GObject
{
public:
	struct CsOrderMapNode
		: public GBinaryTreeNodeT<CsOrderMapNode>
		, public GPairNodeT<KeyT, ValueT>
		, public GNewT<CsOrderMapNode>
	{
		gsmall m_nColor;

		CsOrderMapNode(
			const KeyT &key = KeyT(),
			const ValueT &value = ValueT(),
			CsOrderMapNode *parent = NULL,
			CsOrderMapNode *left = NULL,
			CsOrderMapNode *right = NULL,
			gsmall color = CS_ORDER_MAP_NODE_RED)
			: GBinaryTreeNodeT<CsOrderMapNode>(parent, left, right)
			, GPairNodeT<KeyT, ValueT>(key, value)
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
		inline const KeyT &Key() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		inline ValueT &Value() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		inline ValueT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		inline ValueT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tValue; }
		inline gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		inline gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }
		inline Iterator &operator++() 
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Next();
			return *this;
		}
		inline Iterator operator++(gint)
		{
			GASSERT(m_pNode);
			CsOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Next();
			return Iterator(node);
		}
		inline Iterator &operator--()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Previous();
			return *this;
		}
		inline Iterator operator--(gint) {
			GASSERT(m_pNode);
			CsOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return Iterator(node);
		}
		inline Iterator operator+(gint i) const
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
		inline Iterator operator-(gint i) const { return operator+(-i); }
		inline Iterator &operator+=(gint i) 
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
		inline Iterator &operator-=(gint i) { return operator+=(-i); }
		inline gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		inline gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }

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
		inline const KeyT &Key() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		inline const ValueT &Value() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		inline const ValueT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		inline const ValueT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tValue; }
		inline gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		inline gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		inline ConstIterator &operator++()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Next();
			return *this;
		}
		inline ConstIterator operator++(gint)
		{
			GASSERT(m_pNode);
			const CsOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Next();
			return ConstIterator(node);
		}
		inline ConstIterator &operator--()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Previous();
			return *this;
		}
		inline ConstIterator operator--(gint) {
			GASSERT(m_pNode);
			const CsOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return ConstIterator(node);
		}
		inline ConstIterator operator+(gint i) const
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
		inline ConstIterator operator-(gint i) const { return operator+(-i); }
		inline ConstIterator &operator+=(gint i)
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
		inline ConstIterator &operator-=(gint i) { return operator+=(-i); }
		inline gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		inline gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }

	private:
		const CsOrderMapNode *m_pNode;
	};
	friend class ConstIterator;

public:
	GOrderMap();
	GOrderMap(const GOrderMap<KeyT, ValueT, CompareT> &);

	gsize Size() const;
	gbool IsEmpty() const;
	gvoid Clear();
	gbool Contains(const KeyT &key) const;

	ValueT &First();
	const ValueT &First() const;
	const KeyT &FirstKey() const;
	ValueT &Last();
	const ValueT &Last() const;
	const KeyT &LastKey() const;

	gvoid Remove(const KeyT &);

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

	GOrderMap<KeyT, ValueT, CompareT> &operator=(const GOrderMap<KeyT, ValueT, CompareT> &);
	gbool operator==(const GOrderMap<KeyT, ValueT, CompareT> &) const;
	gbool operator!=(const GOrderMap<KeyT, ValueT, CompareT> &) const;
	ValueT &operator[](const KeyT &);
	//const ValueT &operator[](const KeyT &) const;

private:
	GReadBlackTree<KeyT, ValueT, CompareT, CsOrderMapNode> m_tTree;
	gsize m_nSize;
};

#include "gordermap.inl"

#undef CS_ORDER_MAP_NODE_BLACK
#undef CS_ORDER_MAP_NODE_RED

#endif // _CORE_ORDER_MAP_H_