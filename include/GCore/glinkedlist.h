#ifndef _CORE_LINKED_LIST_H_
#define _CORE_LINKED_LIST_H_

#include "gobject.h"
#include "gserialize.h"
#include "gstructure.h"

// NodeT为节点类型，设置为从外部传入，以增加扩展性
template<typename DataT, typename NodeT>
class GLinkedList
	: public GListT<GLinkedList<DataT, NodeT>>
	, public GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_LINKED_LIST, };

	typedef NodeT Node;

public:
	virtual ~GLinkedList() = 0 {}
	
	virtual gsize Size() const = 0;
	virtual gbool IsEmpty() const = 0;
	
	// 翻转
	virtual gvoid Invert() = 0;

	virtual gbool InsertBefore(gsize pos, const DataT &data) = 0;
	virtual gbool InsertBefore(gsize pos, DataT &&data) = 0;

	virtual gbool InsertBefore(NodeT *node, const DataT &data) = 0;
	virtual gbool InsertBefore(NodeT *node, DataT &&data) = 0;

	virtual gbool InsertAfter(gsize pos, const DataT &data) = 0;
	virtual gbool InsertAfter(gsize pos, DataT &&data) = 0;

	virtual gbool InsertAfter(NodeT *node, const DataT &data) = 0;
	virtual gbool InsertAfter(NodeT *node, DataT &&data) = 0;

	virtual gbool AddFirst(const DataT &data) = 0;
	virtual gbool AddFirst(DataT &&data) = 0;

	virtual gbool AddLast(const DataT &data) = 0;
	virtual gbool AddLast(DataT &&data) = 0;

	virtual gvoid Remove(const NodeT *node) = 0;
	virtual gvoid RemoveAt(gsize pos) = 0;
	virtual gvoid RemoveFirst() = 0;
	virtual gvoid RemoveLast() = 0;
	virtual gvoid RemoveAll() = 0;

	virtual NodeT *GetFirstNode() = 0;
	virtual const NodeT *GetFirstNode() const = 0;

	virtual NodeT *GetLastNode() = 0;
	virtual const NodeT *GetLastNode() const = 0;

	virtual NodeT *GetNodeAt(gsize pos) = 0;
	virtual const NodeT *GetNodeAt(gsize pos) const = 0;

	virtual DataT &GetFirstData() = 0;
	virtual const DataT &GetFirstData() const = 0;

	virtual DataT &GetLastData() = 0;
	virtual const DataT &GetLastData() const = 0;

	virtual DataT &GetDataAt(gsize pos) = 0;
	virtual const DataT &GetDataAt(gsize pos) const = 0;

	virtual gvoid SetDataAt(gsize pos, const DataT &data) = 0;
	virtual gvoid SetDataAt(gsize pos, DataT &&data) = 0;

	virtual gsize IndexOf(const DataT &data) const = 0;
	virtual NodeT *Find(const DataT &data) = 0;
	virtual const NodeT *Find(const DataT &data) const = 0;

	//virtual gbool Contains(const DataT &data) const = 0;
	//virtual gsize LastIndexOf(const DataT &data) const = 0;
	//virtual gsize CountOf(const DataT &data) const = 0;

	virtual gsize IndexOfCircle() const = 0;
	virtual NodeT *FindCircle() = 0;
	virtual const NodeT *FindCircle() const = 0;

	// 由于要对链表做修改，因此这里未做const声明，后期改进
	virtual gsize IndexOfCross(const GLinkedList<DataT, NodeT> &) = 0;

	virtual DataT &operator[](gsize pos) = 0;
	virtual const DataT &operator[](gsize pos) const = 0;

	///
	virtual guint ClassCode() const;
};

#include "glinkedlist.inl"

#endif // _CORE_LINKED_LIST_H_