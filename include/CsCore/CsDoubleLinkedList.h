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
class CsDoubleLinkedList 
	: public CsLinkedList<DataT>
{
	template<typename DataT>
	struct CsDoubleLinkedListNode
		: public CsDoubleLinkedListNodeT<CsDoubleLinkedListNode<DataT>>
		, public CsDataNodeT<DataT>
		, public CsNewT<CsDoubleLinkedListNode<DataT>>
	{
		CsDoubleLinkedListNode(const DataT &data = DataT(),
			CsDoubleLinkedListNode<DataT> *previous = NULL,
			CsDoubleLinkedListNode<DataT> *next = NULL)
			: CsDoubleLinkedListNodeT<CsDoubleLinkedListNode<DataT>>(previous, next)
			, CsDataNodeT<DataT>(data)
		{

		}
	};
	
	typedef CsDoubleLinkedListNode<DataT> Node;

public:
	CsDoubleLinkedList();
	CsDoubleLinkedList(const DataT &data);
	CsDoubleLinkedList(const CsDoubleLinkedList<DataT> &other);
	CsDoubleLinkedList<DataT>& operator=(const CsDoubleLinkedList<DataT> &other);
	~CsDoubleLinkedList();

public:
	cs_void Invert();
	cs_bool IsEmpty() const;
	cs_size_t Size() const;
	cs_bool InsertBefore(cs_size_t pos, const DataT &data);
	cs_bool InsertAfter(cs_size_t pos, const DataT &data);
	cs_bool AddHead(const DataT &data);
	cs_bool AddTail(const DataT &data);
	cs_void RemoveAt(cs_size_t pos);
	cs_void RemoveHead();
	cs_void RemoveTail();
	cs_void RemoveAll();
	DataT& GetTail();
	DataT  GetTail() const;
	DataT& GetHead();
	DataT  GetHead() const;
	DataT& GetAt(cs_size_t pos);
	DataT  GetAt(cs_size_t pos) const;
	cs_void SetAt(cs_size_t pos, const DataT &data);
	cs_size_t Find(const DataT &data) const;
	cs_size_t FindCircle() const;
	cs_size_t FindCross(const CsDoubleLinkedList &list);

	DataT &operator[](cs_size_t id);
	DataT operator[](cs_size_t id) const;

protected:
	cs_size_t m_nSize;
	Node *m_pHead;
	Node *m_pTail;
};

#include "CsDoubleLinkedList.inl"

#endif // _CORE_DOUBLE_LINKED_LIST_H_