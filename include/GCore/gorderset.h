// ÓÐÐò¼¯ºÏ
#ifndef _CORE_ORDER_SET_H_
#define _CORE_ORDER_SET_H_

#include "greadblacktree.h"

#define G_ORDER_SET_NODE_RED	0
#define G_ORDER_SET_NODE_BLACK	1

template < typename KeyT, typename CompareT = GCompareToF<KeyT>>
class GOrderSet
	: public GObject
{
public:
	struct GOrderSetNode
		: public GBinaryTreeNodeT<GOrderSetNode>
		, public GPairNodeT<KeyT, GDummyNodeT>
		, public GNewT<GOrderSetNode>
	{
		gsmall m_nColor;

		GOrderSetNode(
			const KeyT &key = KeyT(),
			const GDummyNodeT &value = GDummyNodeT(),
			GOrderSetNode *parent = GNULL,
			GOrderSetNode *left = GNULL,
			GOrderSetNode *right = GNULL,
			gsmall color = G_ORDER_SET_NODE_RED)
			: GBinaryTreeNodeT<GOrderSetNode>(parent, left, right)
			, GPairNodeT<KeyT, GDummyNodeT>(key, value)
			, m_nColor(color)
		{

		}

		GOrderSetNode(
			const KeyT &key, GDummyNodeT &&value,
			GOrderSetNode *parent = GNULL,
			GOrderSetNode *left = GNULL,
			GOrderSetNode *right = GNULL,
			gsmall color = G_ORDER_SET_NODE_RED)
			: GBinaryTreeNodeT<GOrderSetNode>(parent, left, right)
			, GPairNodeT<KeyT, GDummyNodeT>(key, GForward<GDummyNodeT>(value))
			, m_nColor(color)
		{

		}
	};
	typedef GOrderSetNode Node;

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		Iterator() : m_pNode(GNULL) {}
		Iterator(GOrderSetNode *node) : m_pNode(node) {}
		Iterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}
		Iterator(Iterator &&iter) : m_pNode(iter.m_pNode) { iter.m_pNode = GNULL; }

		GINLINE Iterator &operator=(const Iterator &iter) const
		{
			if (this == &iter)
			{
				return *this;
			}
			m_pNode = iter.m_pNode;
			return *this;
		}
		GINLINE Iterator &operator=(Iterator &&iter) const
		{
			if (this == &iter)
			{
				return *this;
			}
			m_pNode = iter.m_pNode;
			iter.m_pNode = GNULL;
			return *this;
		}
		GINLINE const KeyT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		GINLINE const KeyT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tKey; }
		GINLINE gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		GINLINE gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }
		GINLINE Iterator &operator++()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Next();
			return *this;
		}
		GINLINE Iterator operator++(gint)
		{
			GASSERT(m_pNode);
			GOrderSetNode *node = m_pNode;
			m_pNode = m_pNode->Next();
			return Iterator(node);
		}
		GINLINE Iterator &operator--()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Previous();
			return *this;
		}
		GINLINE Iterator operator--(gint) {
			GASSERT(m_pNode);
			GOrderSetNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return Iterator(node);
		}
		GINLINE Iterator operator+(gint i) const
		{
			GOrderSetNode *node = m_pNode;
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
		GINLINE Iterator operator-(gint i) const { return operator+(-i); }
		GINLINE Iterator &operator+=(gint i)
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
		GINLINE Iterator &operator-=(gint i) { return operator+=(-i); }
		GINLINE gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		GINLINE gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		GINLINE Iterator Next() const
		{
			GASSERT(m_pNode);
			return Iterator(m_pNode->Next());
		}
		GINLINE Iterator Previous() const
		{
			GASSERT(m_pNode);
			return Iterator(m_pNode->Previous());
		}
		GINLINE gbool HasNext() const
		{
			return GNULL != m_pNode
				&& GNULL != m_pNode->Next();
		}
		GINLINE gbool HasPrevious() const
		{
			return GNULL != m_pNode
				&& GNULL != m_pNode->Previous();
		}
	private:
		GOrderSetNode *m_pNode;
	};
	friend class Iterator;

	class ConstIterator
	{
		friend class Iterator;
	public:
		GINLINE ConstIterator() : m_pNode(GNULL) { }
		GINLINE ConstIterator(const GOrderSetNode *node) : m_pNode(node) {}
		GINLINE ConstIterator(const ConstIterator &citer) : m_pNode(citer.m_pNode) {}
		GINLINE ConstIterator(ConstIterator &&citer) : m_pNode(citer.m_pNode) { citer.m_pNode = GNULL; }
		explicit GINLINE ConstIterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}
		explicit GINLINE ConstIterator(Iterator &&iter) : m_pNode(iter.m_pNode) { iter.m_pNode = GNULL; }

		GINLINE ConstIterator &operator=(const ConstIterator &citer) const
		{
			if (this == &citer)
			{
				return *this;
			}
			m_pNode = citer.m_pNode;
			return *this;
		}
		GINLINE ConstIterator &operator=(ConstIterator &&citer) const
		{
			if (this == &citer)
			{
				return *this;
			}
			m_pNode = citer.m_pNode;
			citer.m_pNode = GNULL;
			return *this;
		}
		GINLINE const KeyT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		GINLINE const KeyT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tKey; }
		GINLINE gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		GINLINE gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		GINLINE ConstIterator &operator++()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Next();
			return *this;
		}
		GINLINE ConstIterator operator++(gint)
		{
			GASSERT(m_pNode);
			const GOrderSetNode *node = m_pNode;
			m_pNode = m_pNode->Next();
			return ConstIterator(node);
		}
		GINLINE ConstIterator &operator--()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Previous();
			return *this;
		}
		GINLINE ConstIterator operator--(gint) {
			GASSERT(m_pNode);
			const GOrderSetNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return ConstIterator(node);
		}
		GINLINE ConstIterator operator+(gint i) const
		{
			const GOrderSetNode *node = m_pNode;
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
		GINLINE ConstIterator operator-(gint i) const { return operator+(-i); }
		GINLINE ConstIterator &operator+=(gint i)
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
		GINLINE ConstIterator &operator-=(gint i) { return operator+=(-i); }
		GINLINE gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		GINLINE gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }
		GINLINE ConstIterator Next() const
		{
			GASSERT(m_pNode);
			return ConstIterator(m_pNode->Next());
		}
		GINLINE ConstIterator Previous() const
		{
			GASSERT(m_pNode);
			return ConstIterator(m_pNode->Previous());
		}
		GINLINE gbool HasNext() const
		{
			return GNULL != m_pNode
				&& GNULL != m_pNode->Next();
		}
		GINLINE gbool HasPrevious() const
		{
			return GNULL != m_pNode
				&& GNULL != m_pNode->Previous();
		}

	private:
		const GOrderSetNode *m_pNode;
	};
	friend class ConstIterator;

public:
	GOrderSet();
	GOrderSet(const GOrderSet<KeyT, CompareT> &);
	GOrderSet(GOrderSet<KeyT, CompareT> &&);

	gsize Size() const;
	gbool IsEmpty() const;
	gvoid Clear();
	gbool Contains(const KeyT &key) const;

	const KeyT &First() const;
	const KeyT &Last() const;

	gvoid Remove(const KeyT &);

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

	GOrderSet<KeyT, CompareT> &Intersect(const GOrderSet<KeyT, CompareT> &);
	GOrderSet<KeyT, CompareT> &Unite(const GOrderSet<KeyT, CompareT> &);

	gbool operator==(const GOrderSet<KeyT, CompareT> &) const;
	gbool operator!=(const GOrderSet<KeyT, CompareT> &) const;

	GOrderSet<KeyT, CompareT>  operator&(const GOrderSet<KeyT, CompareT> &) const;
	GOrderSet<KeyT, CompareT> &operator&=(const GOrderSet<KeyT, CompareT> &);
	GOrderSet<KeyT, CompareT> &operator&=(const KeyT &);

	GOrderSet<KeyT, CompareT>  operator|(const GOrderSet<KeyT, CompareT> &) const;
	GOrderSet<KeyT, CompareT> &operator|=(const GOrderSet<KeyT, CompareT> &);
	GOrderSet<KeyT, CompareT> &operator|=(const KeyT &);

	GOrderSet<KeyT, CompareT>  operator+(const GOrderSet<KeyT, CompareT> &) const;
	GOrderSet<KeyT, CompareT> &operator+=(const GOrderSet<KeyT, CompareT> &);
	GOrderSet<KeyT, CompareT> &operator+=(const KeyT &);

	GOrderSet<KeyT, CompareT>  operator-(const GOrderSet<KeyT, CompareT> &) const;
	GOrderSet<KeyT, CompareT> &operator-=(const GOrderSet<KeyT, CompareT> &);
	GOrderSet<KeyT, CompareT> &operator-=(const KeyT &);

	GOrderSet<KeyT, CompareT> &operator>>(KeyT &);
	GOrderSet<KeyT, CompareT> &operator<<(const KeyT &);

	GOrderSet<KeyT, CompareT> &operator=(const GOrderSet<KeyT, CompareT> &);
	GOrderSet<KeyT, CompareT> &operator=(GOrderSet<KeyT, CompareT> &&);

private:
	GReadBlackTree<KeyT, GDummyNodeT, CompareT, GOrderSetNode> m_tTree;
	gsize m_nSize;
};

#include "gorderset.inl"

#undef G_ORDER_SET_NODE_BLACK
#undef G_ORDER_SET_NODE_RED

#endif // _CORE_ORDER_SET_H_