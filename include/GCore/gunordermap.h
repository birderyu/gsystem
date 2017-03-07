#ifndef _CORE_UNORDER_MAP_H_
#define _CORE_UNORDER_MAP_H_

#include "ghashtable.h"

template <typename KeyT, typename ValueT,
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF<KeyT>>
class GUnorderMap
	: public GObject
{
public:
	struct GUnorderMapNode
		: public GNextNodeT<GUnorderMapNode>
		, public GPairNodeT<KeyT, ValueT>
		, public GNewT<GUnorderMapNode>
	{
		GUnorderMapNode(const KeyT &key = KeyT(),
			const ValueT &value = ValueT(),
			GUnorderMapNode *next = GNULL)
			: GNextNodeT<GUnorderMapNode>(next)
			, GPairNodeT<KeyT, ValueT>(key, value)
		{

		}
	};
	typedef GUnorderMapNode Node;
	typedef GHashTable<KeyT, ValueT, HashT, CompareT, GUnorderMapNode> Table;
	typedef GUnorderMap<KeyT, ValueT, HashT, CompareT> Map;

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		GINLINE Iterator() : m_pNode(GNULL), m_pTable(GNULL) {}
		GINLINE Iterator(GUnorderMapNode *node, GUnorderMap<KeyT, ValueT, HashT, CompareT> &map) 
			: m_pNode(node), m_pTable(&map.m_tTable) {}
		GINLINE Iterator(const Iterator &iter) : m_pNode(iter.m_pNode), m_pTable(iter.m_pTable) {}
		GINLINE Iterator(Iterator &&iter) 
			: m_pNode(iter.m_pNode), m_pTable(iter.m_pTable) { iter.m_pNode = iter.m_pTable = GNULL; }
		GINLINE const KeyT &Key() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		GINLINE ValueT &Value() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		GINLINE Iterator &operator=(const Iterator &iter)
		{ 
			if (this == *iter)
			{
				return *this;
			}
			m_pNode = iter.m_pNode;
			m_pTable = iter.m_pTable;
			return *this;
		}
		GINLINE Iterator &operator=(Iterator &&iter)
		{
			if (this == *iter)
			{
				return *this;
			}
			m_pNode = iter.m_pNode;
			m_pTable = iter.m_pTable;
			iter.m_pNode = iter.m_pTable = GNULL;
			return *this;
		}
		GINLINE ValueT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		GINLINE ValueT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tValue; }
		GINLINE gbool operator==(const Iterator &iter) const { return m_pNode == iter.m_pNode; }
		GINLINE gbool operator!=(const Iterator &iter) const { return m_pNode != iter.m_pNode; }
		GINLINE Iterator &operator++()
		{
			GASSERT(m_pNode && m_pTable);
			m_pNode = m_pTable->NextNode(m_pNode);
			return *this;
		}
		GINLINE Iterator operator++(gint)
		{
			GASSERT(m_pNode && m_pTable);
			GUnorderMapNode *node = m_pNode;
			m_pNode = m_pTable->NextNode(m_pNode);
			return Iterator(node, m_pTable);
		}
		GINLINE Iterator operator+(gint i) const
		{
			GASSERT(i >= 0);
			GUnorderMapNode *node = m_pNode;
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
		GINLINE gbool operator==(const ConstIterator &citer) const 
		{ 
			return m_pNode == citer.m_pNode && m_pTable == citer.m_pTable; 
		}
		GINLINE gbool operator!=(const ConstIterator &citer) const 
		{ 
			return m_pNode != citer.m_pNode || m_pTable != citer.m_pTable;
		}
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
		GINLINE Iterator(GUnorderMapNode *node, GHashTable<KeyT, ValueT, HashT, CompareT, GUnorderMapNode> *table)
			: m_pNode(node), m_pTable(table) {}
		GUnorderMapNode *m_pNode;
		GHashTable<KeyT, ValueT, HashT, CompareT, GUnorderMapNode> *m_pTable;
	};
	friend class Iterator;

	class ConstIterator
	{
		friend class Iterator;
	public:
		GINLINE ConstIterator() : m_pNode(0) { }
		GINLINE ConstIterator(const GUnorderMapNode *node, const GUnorderMap<KeyT, ValueT, HashT, CompareT> &map) 
			: m_pNode(node), m_pTable(&map.m_tTable) {}
		GINLINE ConstIterator(const ConstIterator &citer) : m_pNode(citer.m_pNode), m_pTable(citer.m_pTable) {}
		explicit GINLINE ConstIterator(const Iterator &iter) : m_pNode(iter.m_pNode), m_pTable(iter.m_pTable) {}
		GINLINE const KeyT &Key() const { GASSERT(m_pNode); return m_pNode->m_tKey; }
		GINLINE const ValueT &Value() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		GINLINE ConstIterator &operator=(const ConstIterator &citer)
		{
			if (this == *citer)
			{
				return *this;
			}
			m_pNode = citer.m_pNode;
			m_pTable = citer.m_pTable;
			return *this;
		}
		GINLINE ConstIterator &operator=(ConstIterator &&citer)
		{
			if (this == *citer)
			{
				return *this;
			}
			m_pNode = citer.m_pNode;
			m_pTable = citer.m_pTable;
			citer.m_pNode = citer.m_pTable = GNULL;
			return *this;
		}
		GINLINE const ValueT &operator*() const { GASSERT(m_pNode); return m_pNode->m_tValue; }
		GINLINE const ValueT *operator->() const { GASSERT(m_pNode); return &m_pNode->m_tValue; }
		GINLINE gbool operator==(const ConstIterator &citer) const 
		{ 
			return m_pNode == citer.m_pNode && m_pTable == citer.m_pTable; 
		}
		GINLINE gbool operator!=(const ConstIterator &citer) const 
		{ 
			return m_pNode != citer.m_pNode || m_pTable != citer.m_pTable;
		}
		GINLINE ConstIterator &operator++()
		{
			GASSERT(m_pNode && m_pTable);
			m_pNode = m_pTable->NextNode(m_pNode);
			return *this;
		}
		GINLINE ConstIterator operator++(gint)
		{
			GASSERT(m_pNode && m_pTable);
			const GUnorderMapNode *node = m_pNode;
			m_pNode = m_pTable->NextNode(m_pNode);
			return ConstIterator(node, m_pTable);
		}
		GINLINE ConstIterator operator+(gint i) const
		{
			GASSERT(i >= 0);
			const GUnorderMapNode *node = m_pNode;
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
		GINLINE gbool operator==(const Iterator &iter) const 
		{ 
			return m_pNode == iter.m_pNode && m_pTable == iter.m_pTable;
		}
		GINLINE gbool operator!=(const Iterator &iter) const
		{
			return m_pNode != iter.m_pNode || m_pTable != iter.m_pTable;
		}
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
		GINLINE ConstIterator(const GUnorderMapNode *node, const GHashTable<KeyT, ValueT, HashT, CompareT, GUnorderMapNode> *table)
			: m_pNode(node), m_pTable(table) {}
		const GUnorderMapNode *m_pNode;
		const GHashTable<KeyT, ValueT, HashT, CompareT, GUnorderMapNode> *m_pTable;
	};
	friend class ConstIterator;

public:
	GUnorderMap();
	GUnorderMap(const GUnorderMap<KeyT, ValueT, HashT, CompareT> &);
	GUnorderMap(GUnorderMap<KeyT, ValueT, HashT, CompareT> &&);

	gsize Size() const;
	gbool IsEmpty() const;
	gvoid Clear();
	gbool Contains(const KeyT &key) const;

	ValueT &First();
	const ValueT &First() const;
	const KeyT &FirstKey() const;

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

	GUnorderMap<KeyT, ValueT, HashT, CompareT> &operator=(const GUnorderMap<KeyT, ValueT, HashT, CompareT> &);
	GUnorderMap<KeyT, ValueT, HashT, CompareT> &operator=(GUnorderMap<KeyT, ValueT, HashT, CompareT> &&);
	gbool operator==(const GUnorderMap<KeyT, ValueT, HashT, CompareT> &) const;
	gbool operator!=(const GUnorderMap<KeyT, ValueT, HashT, CompareT> &) const;

private:
	GHashTable<KeyT, ValueT, HashT, CompareT, GUnorderMapNode> m_tTable;
};

#include "gunordermap.inl"

#endif // _CORE_UNORDER_MAP_H_