#ifndef _CORE_LINKED_LIST_H_
#define _CORE_LINKED_LIST_H_

#include "CsObject.h"
#include "CsSerialize.h"
#include "CsStructure.h"

// NodeT为节点类型，设置为从外部传入，以增加扩展性
template<typename DataT, typename NodeT>
class CsLinkedList
	: public CsListT<CsLinkedList<DataT, NodeT>>
	, public CsObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_LINKED_LIST, };

	typedef NodeT Node;

public:
	virtual ~CsLinkedList() = 0 {}
	
	virtual cs_size_t Size() const = 0;
	virtual cs_bool IsEmpty() const = 0;
	
	// 翻转
	virtual cs_void Invert() = 0;

	virtual cs_bool InsertBefore(cs_size_t pos, const DataT &data) = 0;
	virtual cs_bool InsertBefore(NodeT *node, const DataT &data) = 0;
	virtual cs_bool InsertAfter(cs_size_t pos, const DataT &data) = 0;
	virtual cs_bool InsertAfter(NodeT *node, const DataT &data) = 0;

	virtual cs_bool AddHead(const DataT &data) = 0;
	virtual cs_bool AddTail(const DataT &data) = 0;

	virtual cs_void Remove(NodeT *node) = 0;
	virtual cs_void RemoveAt(cs_size_t pos) = 0;
	virtual cs_void RemoveHead() = 0;
	virtual cs_void RemoveTail() = 0;
	virtual cs_void RemoveAll() = 0;

	virtual NodeT *GetHeadNode() = 0;
	virtual const NodeT *GetHeadNode() const = 0;
	virtual NodeT *GetTailNode() = 0;
	virtual const NodeT *GetTailNode() const = 0;
	virtual NodeT *GetNodeAt(cs_size_t pos) = 0;
	virtual const NodeT *GetNodeAt(cs_size_t pos) const = 0;

	virtual DataT &GetTail() = 0;
	virtual const DataT &GetTail() const = 0;
	virtual DataT &GetHead() = 0;
	virtual const DataT &GetHead() const = 0;
	virtual DataT &GetAt(cs_size_t pos) = 0;
	virtual const DataT &GetAt(cs_size_t pos) const = 0;
	virtual cs_void SetAt(cs_size_t pos, const DataT &data) = 0;

	virtual cs_size_t IndexOf(const DataT &data) const = 0;
	virtual NodeT *Find(const DataT &data) = 0;
	virtual const NodeT *Find(const DataT &data) const = 0;

	virtual cs_size_t IndexOfCircle() const = 0;
	virtual NodeT *FindCircle() = 0;
	virtual const NodeT *FindCircle() const = 0;

	// 由于要对链表做修改，因此这里未做const声明，后期改进
	virtual cs_size_t IndexOfCross(const CsLinkedList<DataT, NodeT> &) = 0;

	virtual DataT &operator[](cs_size_t pos) = 0;
	virtual const DataT &operator[](cs_size_t pos) const = 0;

	///
	virtual cs_uint ClassCode() const;
};

#include "CsLinkedList.inl"

#endif // _CORE_LINKED_LIST_H_