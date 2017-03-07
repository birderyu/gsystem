// ÎÞÐò¼¯ºÏ
#ifndef _CORE_UNORDER_SET_H_
#define _CORE_UNORDER_SET_H_

#include "ghashtable.h"

template<typename KeyT, 
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF<KeyT>>
class GUnorderSet
	: public GObject
{
public:
	struct GUnorderSetNode
		: public GNextNodeT<GUnorderSetNode>
		, public GPairNodeT<KeyT, GDummyNodeT>
		, public GNewT<GUnorderSetNode>
	{
		GUnorderSetNode(const KeyT &key = KeyT(),
			const GDummyNodeT &value = GDummyNodeT(),
			GUnorderSetNode *next = GNULL)
			: GNextNodeT<GUnorderSetNode>(next)
			, GPairNodeT<KeyT, GDummyNodeT>(key, value)
		{

		}
	};
	typedef GUnorderSetNode Node;
	typedef GHashTable<KeyT, GDummyNodeT, HashT, CompareT, GUnorderSetNode> Table;
	typedef GUnorderSet<KeyT, HashT, CompareT> Set;

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		Iterator() : m_pNode(GNULL), m_pTable(GNULL) {}
		Iterator(GUnorderSetNode *node, GUnorderSet<KeyT, HashT, CompareT> &set) 
			: m_pNode(node), m_pTable(&set.m_tTable) {}
		Iterator(const Iterator &iter) : m_pNode(iter.m_pNode), m_pTable(iter.m_pTable) {}
		Iterator(Iterator &&iter) : m_pNode(iter.m_pNode), m_pTable(iter.m_pTable) { iter.m_pNode = iter.m_pTable = GNULL; }

		GINLINE Iterator &operator=(const Iterator &iter) const
		{
			if (this == &iter)
			{
				return *this;
			}
			m_pNode = iter.m_pNode;
			m_pTable = iter.m_pTable;
			return *this;
		}
		GINLINE Iterator &operator=(Iterator &&iter) const
		{
			if (this == &iter)
			{
				return *this;
			}
			m_pNode = iter.m_pNode;
			m_pTable = iter.m_pTable;
			iter.m_pNode = iter.m_pTable = GNULL;
			return *this;
		}
		GINLINE const KeyT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		GINLINE const KeyT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tKey; }
		GINLINE gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode && m_pTable == iter.m_pTable; }
		GINLINE gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode || m_pTable != iter.m_pTable; }
		GINLINE Iterator &operator++()
		{
			GASSERT(m_pNode && m_pTable);
			m_pNode = m_pTable->NextNode(m_pNode);
			return *this;
		}
		GINLINE Iterator operator++(gint)
		{
			GASSERT(m_pNode && m_pTable);
			GUnorderSetNode *node = m_pNode;
			m_pNode = m_pTable->NextNode(m_pNode);
			return Iterator(node, m_pTable);
		}
		GINLINE Iterator operator+(gint i) const
		{
			GASSERT(i >= 0);
			GUnorderSetNode *node = m_pNode;
			if (i > 0)
			{
				GASSERT(m_pTable);
				while (i-- && node)
				{
					node = m_pTable->NextNode(node);
				}
			}
			return Iterator(node, m_pTable);
		}
		GINLINE Iterator &operator+=(gint i)
		{
			GASSERT(i >= 0);
			if (i > 0)
			{
				GASSERT(m_pTable);
				while (i-- && m_pNode)
				{
					m_pNode = m_pTable->NextNode(m_pNode);
				}
			}
			return *this;
		}
		GINLINE gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode && m_pTable == citer.m_pTable; }
		GINLINE gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode || m_pTable != citer.m_pTable; }
		GINLINE Iterator Next() const
		{
			GASSERT(m_pTable && m_pNode);
			return Iterator(m_pTable->NextNode(m_pNode), m_pTable);
		}
		GINLINE gbool HasNext() const
		{
			return GNULL != m_pTable
				&& GNULL != m_pNode
				&& GNULL != m_pTable->NextNode(m_pNode);
		}

	private:
		GINLINE Iterator(GUnorderSetNode *node, GHashTable<KeyT, GDummyNodeT, HashT, CompareT, GUnorderSetNode> *table)
			: m_pNode(node), m_pTable(table) {}
		GUnorderSetNode *m_pNode;
		GHashTable<KeyT, GDummyNodeT, HashT, CompareT, GUnorderSetNode> *m_pTable;
	};
	friend class Iterator;

	class ConstIterator
	{
		friend class Iterator;
	public:
		GINLINE ConstIterator() : m_pNode(GNULL), m_pTable(GNULL) { }
		GINLINE ConstIterator(const GUnorderSetNode *node, const GUnorderSet<KeyT, HashT, CompareT> &set) 
			: m_pNode(node), m_pTable(&set.m_tTable) {}
		GINLINE ConstIterator(const ConstIterator &citer) : m_pNode(citer.m_pNode), m_pTable(citer.m_pTable) {}
		GINLINE ConstIterator(ConstIterator &&citer) : m_pNode(citer.m_pNode), m_pTable(citer.m_pTable) { citer.m_pNode = citer.m_pTable = GNULL; }
		explicit GINLINE ConstIterator(const Iterator &iter) : m_pNode(iter.m_pNode), m_pTable(iter.m_pTable) {}
		explicit GINLINE ConstIterator(Iterator &&iter) : m_pNode(iter.m_pNode), m_pTable(iter.m_pTable) { iter.m_pNode = iter.m_pTable = GNULL; }

		GINLINE ConstIterator &operator=(const ConstIterator &citer) const
		{
			if (this == &citer)
			{
				return *this;
			}
			m_pNode = citer.m_pNode;
			m_pTable = citer.m_pTable;
			return *this;
		}
		GINLINE ConstIterator &operator=(ConstIterator &&citer) const
		{
			if (this == &citer)
			{
				return *this;
			}
			m_pNode = citer.m_pNode;
			m_pTable = citer.m_pTable;
			citer.m_pNode = citer.m_pTable = GNULL;
			return *this;
		}
		GINLINE const KeyT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		GINLINE const KeyT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tKey; }
		GINLINE gbool operator==(const ConstIterator &citer) const { return m_pNode == citer.m_pNode && m_pTable == citer.m_pTable; }
		GINLINE gbool operator!=(const ConstIterator &citer) const { return m_pNode != citer.m_pNode || m_pTable != citer.m_pTable; }
		GINLINE ConstIterator &operator++()
		{
			GASSERT(m_pNode && m_pTable);
			m_pNode = m_pTable->NextNode(m_pNode);
			return *this;
		}
		GINLINE ConstIterator operator++(gint)
		{
			GASSERT(m_pNode && m_pTable);
			const GUnorderSetNode *node = m_pNode;
			m_pNode = m_pTable->NextNode(m_pNode);
			return ConstIterator(node, m_pTable);
		}
		GINLINE ConstIterator operator+(gint i) const
		{
			GASSERT(i >= 0);
			const GUnorderSetNode *node = m_pNode;
			if (i > 0)
			{
				GASSERT(m_pTable);
				while (i-- && node)
				{
					node = m_pTable->NextNode(node);
				}
			}
			return ConstIterator(node, m_pTable);
		}
		GINLINE ConstIterator &operator+=(gint i)
		{
			GASSERT(i >= 0);
			if (i > 0)
			{
				GASSERT(m_pTable);
				while (i-- && m_pNode)
				{
					m_pNode = m_pTable->NextNode(m_pNode);
				}
			}
			return *this;
		}
		GINLINE gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode && m_pTable == iter.m_pTable; }
		GINLINE gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode || m_pTable != iter.m_pTable; }
		GINLINE ConstIterator Next() const
		{
			GASSERT(m_pTable && m_pNode);
			return ConstIterator(m_pTable->NextNode(m_pNode), m_pTable);
		}
		GINLINE gbool HasNext() const
		{
			return GNULL != m_pTable
				&& GNULL != m_pNode
				&& GNULL != m_pTable->NextNode(m_pNode);
		}

	private:
		GINLINE ConstIterator(const GUnorderSetNode *node, const GHashTable<KeyT, GDummyNodeT, HashT, CompareT, GUnorderSetNode> *table)
			: m_pNode(node), m_pTable(table) {}
		const GUnorderSetNode *m_pNode;
		const GHashTable<KeyT, GDummyNodeT, HashT, CompareT, GUnorderSetNode> *m_pTable;
	};
	friend class ConstIterator;

public:
	GUnorderSet();
	GUnorderSet(const GUnorderSet<KeyT, HashT, CompareT> &);
	GUnorderSet(GUnorderSet<KeyT, HashT, CompareT> &&);

	gsize Size() const;
	gbool IsEmpty() const;
	gvoid Clear();
	gbool Contains(const KeyT &key) const;

	const KeyT &First() const;

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

	GUnorderSet<KeyT, HashT, CompareT> &Intersect(const GUnorderSet<KeyT, HashT, CompareT> &);
	GUnorderSet<KeyT, HashT, CompareT> &Unite(const GUnorderSet<KeyT, HashT, CompareT> &);

	gbool operator==(const GUnorderSet<KeyT, HashT, CompareT> &) const;
	gbool operator!=(const GUnorderSet<KeyT, HashT, CompareT> &) const;

	GUnorderSet<KeyT, HashT, CompareT>  operator&(const GUnorderSet<KeyT, HashT, CompareT> &) const;
	GUnorderSet<KeyT, HashT, CompareT> &operator&=(const GUnorderSet<KeyT, HashT, CompareT> &);
	GUnorderSet<KeyT, HashT, CompareT> &operator&=(const KeyT &);

	GUnorderSet<KeyT, HashT, CompareT>  operator|(const GUnorderSet<KeyT, HashT, CompareT> &) const;
	GUnorderSet<KeyT, HashT, CompareT> &operator|=(const GUnorderSet<KeyT, HashT, CompareT> &);
	GUnorderSet<KeyT, HashT, CompareT> &operator|=(const KeyT &);

	GUnorderSet<KeyT, HashT, CompareT>  operator+(const GUnorderSet<KeyT, HashT, CompareT> &) const;
	GUnorderSet<KeyT, HashT, CompareT> &operator+=(const GUnorderSet<KeyT, HashT, CompareT> &);
	GUnorderSet<KeyT, HashT, CompareT> &operator+=(const KeyT &);

	GUnorderSet<KeyT, HashT, CompareT>  operator-(const GUnorderSet<KeyT, HashT, CompareT> &) const;
	GUnorderSet<KeyT, HashT, CompareT> &operator-=(const GUnorderSet<KeyT, HashT, CompareT> &);
	GUnorderSet<KeyT, HashT, CompareT> &operator-=(const KeyT &);

	GUnorderSet<KeyT, HashT, CompareT> &operator>>(KeyT &);
	GUnorderSet<KeyT, HashT, CompareT> &operator<<(const KeyT &);

	GUnorderSet<KeyT, HashT, CompareT> &operator=(const GUnorderSet<KeyT, HashT, CompareT> &);
	GUnorderSet<KeyT, HashT, CompareT> &operator=(GUnorderSet<KeyT, HashT, CompareT> &&);

private:
	GHashTable<KeyT, GDummyNodeT, HashT, CompareT, GUnorderSetNode> m_tTable;
};

#include "gunorderset.inl"

#endif // _CORE_UNORDER_SET_H_