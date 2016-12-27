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

#include "CsLinkedList.h"
#include "CsStructure.h"

template<typename DataT>
struct CsDoubleLinkedListNode
	: public CsPreviousNextNodeT<CsDoubleLinkedListNode<DataT>>
	, public CsDataNodeT<DataT>
	, public CsNewT<CsDoubleLinkedListNode<DataT>>
{
	CsDoubleLinkedListNode(const DataT &data = DataT(),
		CsDoubleLinkedListNode<DataT> *previous = NULL,
		CsDoubleLinkedListNode<DataT> *next = NULL)
		: CsPreviousNextNodeT<CsDoubleLinkedListNode<DataT>>(previous, next)
		, CsDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT, typename NodeT = CsDoubleLinkedListNode<DataT>>
class CsDoubleLinkedList 
	: public CsLinkedList<DataT, NodeT>
{
public:
	CsDoubleLinkedList();
	CsDoubleLinkedList(const DataT &data);
	CsDoubleLinkedList(const CsDoubleLinkedList<DataT, NodeT> &other);
	CsDoubleLinkedList<DataT, NodeT> &operator=(const CsDoubleLinkedList<DataT, NodeT> &other);
	~CsDoubleLinkedList();

public:
	cs_size_t Size() const;
	cs_bool IsEmpty() const;
	
	cs_void Invert();

	cs_bool InsertBefore(cs_size_t pos, const DataT &data);
	cs_bool InsertBefore(NodeT *node, const DataT &data);
	cs_bool InsertAfter(cs_size_t pos, const DataT &data);
	cs_bool InsertAfter(NodeT *node, const DataT &data);

	cs_bool AddFirst(const DataT &data);
	cs_bool AddLast(const DataT &data);

	cs_void Remove(NodeT *node);
	cs_void RemoveAt(cs_size_t pos);
	cs_void RemoveFirst();
	cs_void RemoveLast();
	cs_void RemoveAll();

	NodeT *GetFirstNode();
	const NodeT *GetFirstNode() const;
	NodeT *GetLastNode();
	const NodeT *GetLastNode() const;
	NodeT *GetNodeAt(cs_size_t pos);
	const NodeT *GetNodeAt(cs_size_t pos) const;

	DataT &GetFirstData();
	const DataT &GetFirstData() const;
	DataT &GetLastData();
	const DataT &GetLastData() const;
	DataT &GetDataAt(cs_size_t pos);
	const DataT &GetDataAt(cs_size_t pos) const;
	cs_void SetDataAt(cs_size_t pos, const DataT &data);

	cs_size_t IndexOf(const DataT &data) const;
	NodeT *Find(const DataT &data);
	const NodeT *Find(const DataT &data) const;

	cs_size_t IndexOfCircle() const;
	NodeT *FindCircle();
	const NodeT *FindCircle() const;

	cs_size_t IndexOfCross(const CsLinkedList<DataT, NodeT> &);

	DataT &operator[](cs_size_t pos);
	const DataT &operator[](cs_size_t pos) const;

protected:
	cs_size_t m_nSize;
	Node *m_pFirst;
	Node *m_pLast;
};

#include "CsDoubleLinkedList.inl"

#endif // _CORE_DOUBLE_LINKED_LIST_H_