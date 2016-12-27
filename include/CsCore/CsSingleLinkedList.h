/////////////////////////////////////////////////////////////////////////////////
/// @brief 单向链表（single linked list）
/// 
///  单向链表的定义及实现
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_SINGLE_LINKED_LIST_H_
#define _CORE_SINGLE_LINKED_LIST_H_

#include "CsLinkedList.h"
#include "CsStructure.h"

template<typename DataT>
struct CsSingleLinkedListNode
	: public CsNextNodeT<CsSingleLinkedListNode<DataT>>
	, public CsDataNodeT<DataT>
	, public CsNewT<CsSingleLinkedListNode<DataT>>
{
	CsSingleLinkedListNode(const DataT &data = DataT(),
		CsSingleLinkedListNode<DataT> *next = NULL)
		: CsNextNodeT<CsSingleLinkedListNode<DataT>>(next)
		, CsDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT, typename NodeT = CsSingleLinkedListNode<DataT>>
class CsSingleLinkedList 
	: public CsLinkedList<DataT, NodeT>
{
public:
	CsSingleLinkedList();
	CsSingleLinkedList(const DataT &data);
	CsSingleLinkedList(const CsSingleLinkedList<DataT, NodeT> &other);
	CsSingleLinkedList<DataT, NodeT>& operator=(const CsSingleLinkedList<DataT, NodeT> &other);
	virtual ~CsSingleLinkedList();

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
	virtual cs_void RemoveAt(cs_size_t pos);
	cs_void RemoveFirst();
	cs_void RemoveLast();
	cs_void RemoveAll();

	NodeT *GetFirstNode();
	const NodeT *GetFirstNode() const;
	NodeT *GetLastNode();
	const NodeT *GetLastNode() const;
	NodeT *GetNodeAt(cs_size_t pos);
	const NodeT *GetNodeAt(cs_size_t pos) const;

	DataT &GetLastData();
	const DataT &GetLastData() const;
	DataT &GetFirstData();
	const DataT &GetFirstData() const;
	DataT &GetDataAt(cs_size_t pos);
	const DataT &GetDataAt(cs_size_t pos) const;
	cs_void SetDataAt(cs_size_t pos, const DataT &data);

	// 不存在则返回NULL_POS
	cs_size_t IndexOf(const DataT &data) const;
	NodeT *Find(const DataT &data);
	const NodeT *Find(const DataT &data) const;

	// 不存在则返回NULL_POS，存在则返回首节点的位置
	cs_size_t IndexOfCircle() const;
	NodeT *FindCircle();
	const NodeT *FindCircle() const;

	// 不存在则返回NULL_POS，存在则返回首节点的位置
	cs_size_t IndexOfCross(const CsLinkedList<DataT, NodeT> &);

	DataT &operator[](cs_size_t pos);
	const DataT &operator[](cs_size_t pos) const;

protected:
	cs_size_t m_nSize;
	Node *m_pFirst;
};

#include "CsSingleLinkedList.inl"

#endif // _CORE_SINGLE_LINKED_LIST_H_