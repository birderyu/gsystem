/////////////////////////////////////////////////////////////////////////////////
/// @brief 双向链表（double linked list）
/// 
///  双向链表的定义及实现
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_DOUBLE_LINKED_LIST_H_
#define _CORE_DOUBLE_LINKED_LIST_H_

#include "glinkedlist.h"
#include "gstructure.h"

template<typename DataT>
struct GDoubleLinkedListNode
	: public GPreviousNextNodeT<GDoubleLinkedListNode<DataT>>
	, public GDataNodeT<DataT>
	, public GNewT<GDoubleLinkedListNode<DataT>>
{
	GDoubleLinkedListNode(const DataT &data = DataT(),
		GDoubleLinkedListNode<DataT> *previous = NULL,
		GDoubleLinkedListNode<DataT> *next = NULL)
		: GPreviousNextNodeT<GDoubleLinkedListNode<DataT>>(previous, next)
		, GDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT, typename NodeT = GDoubleLinkedListNode<DataT>>
class GDoubleLinkedList 
	: public GLinkedList<DataT, NodeT>
{
public:
	GDoubleLinkedList();
	GDoubleLinkedList(const DataT &data);
	GDoubleLinkedList(const GDoubleLinkedList<DataT, NodeT> &other);
	GDoubleLinkedList<DataT, NodeT> &operator=(const GDoubleLinkedList<DataT, NodeT> &other);
	~GDoubleLinkedList();

public:
	gsize Size() const;
	gbool IsEmpty() const;
	
	gvoid Invert();

	gbool InsertBefore(gsize pos, const DataT &data);
	gbool InsertBefore(NodeT *node, const DataT &data);
	gbool InsertAfter(gsize pos, const DataT &data);
	gbool InsertAfter(NodeT *node, const DataT &data);

	gbool AddFirst(const DataT &data);
	gbool AddLast(const DataT &data);

	gvoid Remove(NodeT *node);
	gvoid RemoveAt(gsize pos);
	gvoid RemoveFirst();
	gvoid RemoveLast();
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

	gsize IndexOf(const DataT &data) const;
	NodeT *Find(const DataT &data);
	const NodeT *Find(const DataT &data) const;

	gsize IndexOfCircle() const;
	NodeT *FindCircle();
	const NodeT *FindCircle() const;

	gsize IndexOfCross(const GLinkedList<DataT, NodeT> &);

	DataT &operator[](gsize pos);
	const DataT &operator[](gsize pos) const;

protected:
	gsize m_nSize;
	Node *m_pFirst;
	Node *m_pLast;
};

#include "gdoublelinkedlist.inl"

#endif // _CORE_DOUBLE_LINKED_LIST_H_