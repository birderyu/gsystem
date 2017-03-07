/////////////////////////////////////////////////////////////////////////////////
/// @brief 单向链表（single linked list）
/// 
///  单向链表的定义及实现
/// 
/// @author  birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_SINGLE_LINKED_LIST_H_
#define _CORE_SINGLE_LINKED_LIST_H_

#include "glinkedlist.h"
#include "gstructure.h"

template<typename DataT>
struct GSingleLinkedListNode
	: public GNextNodeT<GSingleLinkedListNode<DataT>>
	, public GDataNodeT<DataT>
	, public GNewT<GSingleLinkedListNode<DataT>>
{
	GSingleLinkedListNode(const DataT &data = DataT(),
		GSingleLinkedListNode<DataT> *next = GNULL)
		: GNextNodeT<GSingleLinkedListNode<DataT>>(next)
		, GDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT, typename NodeT = GSingleLinkedListNode<DataT>>
class GSingleLinkedList 
	: public GLinkedList<DataT, NodeT>
{
public:
	GSingleLinkedList();
	GSingleLinkedList(const DataT &data);
	GSingleLinkedList(DataT &&data);
	GSingleLinkedList(const GSingleLinkedList<DataT, NodeT> &list);
	GSingleLinkedList(GSingleLinkedList<DataT, NodeT> &&list);
	GSingleLinkedList<DataT, NodeT>& operator=(const GSingleLinkedList<DataT, NodeT> &list);
	GSingleLinkedList<DataT, NodeT>& operator=(GSingleLinkedList<DataT, NodeT> &&list);
	virtual ~GSingleLinkedList();

public:
	gsize Size() const;
	gbool IsEmpty() const;
	
	gvoid Invert();

	gbool InsertBefore(gsize pos, const DataT &data);
	gbool InsertBefore(gsize pos, DataT &&data);

	gbool InsertBefore(NodeT *node, const DataT &data);
	gbool InsertBefore(NodeT *node, DataT &&data);

	gbool InsertAfter(gsize pos, const DataT &data);
	gbool InsertAfter(gsize pos, DataT &&data);

	gbool InsertAfter(NodeT *node, const DataT &data);
	gbool InsertAfter(NodeT *node, DataT &&data);

	gbool AddFirst(const DataT &data);
	gbool AddFirst(DataT &&data);

	gbool AddLast(const DataT &data);
	gbool AddLast(DataT &&data);

	gvoid Remove(const NodeT *node);
	virtual gvoid RemoveAt(gsize pos);
	gvoid RemoveFirst();
	gvoid RemoveLast();
	gvoid RemoveAll();

	NodeT *GetFirstNode();
	const NodeT *GetFirstNode() const;
	NodeT *GetLastNode();
	const NodeT *GetLastNode() const;
	NodeT *GetNodeAt(gsize pos);
	const NodeT *GetNodeAt(gsize pos) const;

	DataT &GetLastData();
	const DataT &GetLastData() const;
	DataT &GetFirstData();
	const DataT &GetFirstData() const;
	DataT &GetDataAt(gsize pos);
	const DataT &GetDataAt(gsize pos) const;

	gvoid SetDataAt(gsize pos, const DataT &data);
	gvoid SetDataAt(gsize pos, DataT &&data);

	// 不存在则返回NULL_POS
	gsize IndexOf(const DataT &data) const;
	NodeT *Find(const DataT &data);
	const NodeT *Find(const DataT &data) const;

	// 不存在则返回NULL_POS，存在则返回首节点的位置
	gsize IndexOfCircle() const;
	NodeT *FindCircle();
	const NodeT *FindCircle() const;

	// 不存在则返回NULL_POS，存在则返回首节点的位置
	gsize IndexOfCross(const GLinkedList<DataT, NodeT> &);

	DataT &operator[](gsize pos);
	const DataT &operator[](gsize pos) const;

protected:
	gsize m_nSize;
	Node *m_pFirst;
};

#include "gsinglelinkedlist.inl"

#endif // _CORE_SINGLE_LINKED_LIST_H_