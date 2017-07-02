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
#include "gstruct.h"

namespace gsystem { // gsystem

template<typename DataT>
struct GSListNode
	: public GNextNodeT<GSListNode<DataT>>
	, public GDataNodeT<DataT>
	, public GNewT<GSListNode<DataT>>
{
	GSListNode(const DataT &data = DataT(),
		GSListNode<DataT> *next = GNULL)
		: GNextNodeT<GSListNode<DataT>>(next)
		, GDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT, typename NodeT = GSListNode<DataT>>
class GSList 
	: public GLinkedList<DataT, NodeT>
{
public:
	GSList();
	GSList(const DataT &data);
	GSList(DataT &&data);
	GSList(const GSList<DataT, NodeT> &list);
	GSList(GSList<DataT, NodeT> &&list);
	GSList<DataT, NodeT>& operator=(const GSList<DataT, NodeT> &list);
	GSList<DataT, NodeT>& operator=(GSList<DataT, NodeT> &&list);
	virtual ~GSList();

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
	virtual gvoid RemoveAt(gsize pos, DataT *data = GNULL);
	gvoid RemoveFirst(DataT *data = GNULL);
	gvoid RemoveLast(DataT *data = GNULL);
	gvoid RemoveAll(DataT *data = GNULL);

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

} // namespace gsystem

#include "inline/gslist.inl"

#endif // _CORE_SINGLE_LINKED_LIST_H_