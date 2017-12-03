// ”––ÚMap
#ifndef _CORE_SORTED_MAP_H_
#define _CORE_SORTED_MAP_H_

#include "grbtree.h"

#define G_SORTED_MAP_NODE_RED	0
#define G_SORTED_MAP_NODE_BLACK	1

namespace gsystem { // gsystem

template<typename KeyT, typename ValueT,
	typename CompareT = GCompareToF<KeyT >>
class GSortedMap
	: public GObject
{
public:
	struct GOrderMapNode
		: public GBinTreeNodeT<GOrderMapNode>
		, public GPairNodeT<KeyT, ValueT>
		, public GNewT<GOrderMapNode>
	{
		gsmall m_nColor;

		GOrderMapNode(
			const KeyT &key = KeyT(),
			const ValueT &value = ValueT(),
			GOrderMapNode *parent = GNULL,
			GOrderMapNode *left = GNULL,
			GOrderMapNode *right = GNULL,
			gsmall color = G_SORTED_MAP_NODE_RED)
			: GBinTreeNodeT<GOrderMapNode>(parent, left, right)
			, GPairNodeT<KeyT, ValueT>(key, value)
			, m_nColor(color)
		{

		}

		GOrderMapNode(
			const KeyT &key, ValueT &&value,
			GOrderMapNode *parent = GNULL,
			GOrderMapNode *left = GNULL,
			GOrderMapNode *right = GNULL,
			gsmall color = G_SORTED_MAP_NODE_RED)
			: GBinTreeNodeT<GOrderMapNode>(parent, left, right)
			, GPairNodeT<KeyT, ValueT>(key, GForward<ValueT>(value))
			, m_nColor(color)
		{

		}
	};
	typedef GOrderMapNode Node;

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		GINLINE Iterator() : m_pNode(GNULL) {}
		GINLINE Iterator(GOrderMapNode *node) : m_pNode(node) {}
		GINLINE Iterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}
		GINLINE Iterator(Iterator &&iter) : m_pNode(iter.m_pNode) { iter.m_pNode = GNULL; }
		GINLINE const KeyT &Key() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		GINLINE ValueT &Value() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		GINLINE Iterator &operator=(const Iterator &iter)
		{
			if (*iter == this)
			{
				return *this;
			}
			m_pNode = iter.m_pNode;
			return *this;
		}
		GINLINE Iterator &operator=(Iterator &&iter)
		{
			if (*iter == this)
			{
				return *this;
			}
			m_pNode = iter.m_pNode;
			iter.m_pNode = GNULL;
			return *this;
		}
		GINLINE ValueT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		GINLINE ValueT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tValue; }
		GINLINE gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		GINLINE gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }
		GINLINE Iterator &operator++() 
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Next();
			return *this;
		}
		GINLINE const Iterator operator++(gint)
		{
			GASSERT(m_pNode);
			GOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Next();
			return Iterator(node);
		}
		GINLINE Iterator &operator--()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Previous();
			return *this;
		}
		GINLINE const Iterator operator--(gint) 
		{
			GASSERT(m_pNode);
			GOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return Iterator(node);
		}
		GINLINE Iterator operator+(gint i) const
		{
			GOrderMapNode *node = m_pNode;
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
		GOrderMapNode *m_pNode;
	};
	friend class Iterator;

	class ConstIterator
	{
		friend class Iterator;
	public:
		GINLINE ConstIterator() : m_pNode(GNULL) { }
		GINLINE ConstIterator(const GOrderMapNode *node) : m_pNode(node) {}
		GINLINE ConstIterator(const ConstIterator &citer) : m_pNode(citer.m_pNode) {}
		GINLINE ConstIterator(ConstIterator &&citer) : m_pNode(citer.m_pNode) { citer.m_pNode = GNULL; }
		explicit GINLINE ConstIterator(const Iterator &iter) : m_pNode(iter.m_pNode) {}
		GINLINE const KeyT &Key() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		GINLINE const ValueT &Value() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		GINLINE ConstIterator &operator=(const ConstIterator &citer)
		{
			if (*citer == this)
			{
				return *this;
			}
			m_pNode = citer.m_pNode;
			return *this;
		}
		GINLINE ConstIterator &operator=(ConstIterator &&citer)
		{
			if (*citer == this)
			{
				return *this;
			}
			m_pNode = citer.m_pNode;
			citer.m_pNode = GNULL;
			return *this;
		}
		GINLINE const ValueT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		GINLINE const ValueT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tValue; }
		GINLINE gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode; }
		GINLINE gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode; }
		GINLINE ConstIterator &operator++()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Next();
			return *this;
		}
		GINLINE const ConstIterator operator++(gint)
		{
			GASSERT(m_pNode);
			const GOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Next();
			return ConstIterator(node);
		}
		GINLINE ConstIterator &operator--()
		{
			GASSERT(m_pNode);
			m_pNode = m_pNode->Previous();
			return *this;
		}
		GINLINE const ConstIterator operator--(gint) 
		{
			GASSERT(m_pNode);
			const GOrderMapNode *node = m_pNode;
			m_pNode = m_pNode->Previous();
			return ConstIterator(node);
		}
		GINLINE ConstIterator operator+(gint i) const
		{
			const GOrderMapNode *node = m_pNode;
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
		const GOrderMapNode *m_pNode;
	};
	friend class ConstIterator;

public:
	GSortedMap();
	GSortedMap(const GSortedMap<KeyT, ValueT, CompareT> &);
	GSortedMap(GSortedMap<KeyT, ValueT, CompareT> &&);

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
	Iterator Insert(const KeyT &, ValueT &&);
	Iterator Erase(const Iterator &);

	GSortedMap<KeyT, ValueT, CompareT> &operator=(const GSortedMap<KeyT, ValueT, CompareT> &);
	GSortedMap<KeyT, ValueT, CompareT> &operator=(GSortedMap<KeyT, ValueT, CompareT> &&);
	gbool operator==(const GSortedMap<KeyT, ValueT, CompareT> &) const;
	gbool operator!=(const GSortedMap<KeyT, ValueT, CompareT> &) const;
	//ValueT &operator[](const KeyT &);
	//const ValueT &operator[](const KeyT &) const;

private:
	GRBTree<KeyT, ValueT, CompareT, GOrderMapNode> m_tTree;
	gsize m_nSize;
};

} // namespace gsystem

#include "inline/gsortedmap.inl"

#undef G_SORTED_MAP_NODE_BLACK
#undef G_SORTED_MAP_NODE_RED

#endif // _CORE_SORTED_MAP_H_