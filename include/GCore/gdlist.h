/////////////////////////////////////////////////////////////////////////////////
/// @brief 双向链表（double linked list）
/// 
///  双向链表的定义及实现
/// 
/// @author  birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_DOUBLE_LINKED_LIST_H_
#define _CORE_DOUBLE_LINKED_LIST_H_

#include "glinkedlist.h"
#include "gstruct.h"
#include "gnew.h"

namespace gsystem { // gsystem

template<typename DataT>
struct GDListNode
	: public GPreviousNextNodeT<GDListNode<DataT>>
	, public GDataNodeT<DataT>
	, public GNewT<GDListNode<DataT>>
{
	GDListNode(const DataT &data = DataT(),
		GDListNode<DataT> *previous = GNULL,
		GDListNode<DataT> *next = GNULL)
		: GPreviousNextNodeT<GDListNode<DataT>>(previous, next)
		, GDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT, typename NodeT = GDListNode<DataT>>
class GDList 
	: public GLinkedList<DataT, NodeT>
{
public:
	GDList();
	GDList(const DataT &data);
	GDList(DataT &&data);
	GDList(const GDList<DataT, NodeT> &list);
	GDList(GDList<DataT, NodeT> &&list);
	GDList<DataT, NodeT> &operator=(const GDList<DataT, NodeT> &list);
	GDList<DataT, NodeT> &operator=(GDList<DataT, NodeT> &&list);
	~GDList();

public:
	gsize Size() const;
	gbool IsEmpty() const;
	
	gvoid Invert();

	gvoid InsertBefore(gsize pos, const DataT &data);
	gvoid InsertBefore(gsize pos, DataT &&data);

	gvoid InsertBefore(NodeT *node, const DataT &data);
	gvoid InsertBefore(NodeT *node, DataT &&data);

	gvoid InsertAfter(gsize pos, const DataT &data);
	gvoid InsertAfter(gsize pos, DataT &&data);

	gvoid InsertAfter(NodeT *node, const DataT &data);
	gvoid InsertAfter(NodeT *node, DataT &&data);

	gvoid AddFirst(const DataT &data);
	gvoid AddFirst(DataT &&data);

	gvoid AddLast(const DataT &data);
	gvoid AddLast(DataT &&data);

	gvoid Remove(const NodeT *node);
	gvoid RemoveAt(gsize pos, DataT *data = GNULL);
	gvoid RemoveFirst(DataT *data = GNULL);
	gvoid RemoveLast(DataT *data = GNULL);
	gvoid RemoveAll();

	NodeT *GetFirstNode();
	const NodeT *GetFirstNode() const;
	NodeT *GetLastNode();
	const NodeT *GetLastNode() const;
	NodeT *GetNodeAt(gsize pos);
	const NodeT *GetNodeAt(gsize pos) const;

	DataT &GetFirstData();
	const DataT &GetFirstData() const;
	DataT &GetLastData();
	const DataT &GetLastData() const;
	DataT &GetDataAt(gsize pos);
	const DataT &GetDataAt(gsize pos) const;

	gvoid SetDataAt(gsize pos, const DataT &data);
	gvoid SetDataAt(gsize pos, DataT &&data);

	gsize IndexOf(const DataT &data) const;
	NodeT *Find(const DataT &data);
	const NodeT *Find(const DataT &data) const;

	gsize IndexOfCircle() const;
	NodeT *FindCircle();
	const NodeT *FindCircle() const;

	gsize IndexOfCross(const GLinkedList<DataT, NodeT> &);

	DataT &operator[](gsize pos);
	const DataT &operator[](gsize pos) const;

	GLinkedList<DataT, NodeT> &operator+=(const GDList<DataT, NodeT> &list);
	GLinkedList<DataT, NodeT> &operator+=(GDList<DataT, NodeT> &&list);

protected:
	gsize m_nSize;
	Node *m_pFirst;
	Node *m_pLast;
};

} // namespace gsystem

#include "inline/gdlist.inl"

#endif // _CORE_DOUBLE_LINKED_LIST_H_