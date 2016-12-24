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
class CsSingleLinkedList 
	: public CsLinkedList<DataT>
{
protected:
	template<typename DataT>
	struct CsSingleLinkedListNode 
		: public CsSingleLinkedListNodeT<CsSingleLinkedListNode<DataT>>
		, public CsDataNodeT<DataT>
		, public CsNewT<CsSingleLinkedListNode<DataT>>
	{
		CsSingleLinkedListNode(const DataT &data = DataT(),
			CsSingleLinkedListNode<DataT> *next = NULL)
			: CsSingleLinkedListNodeT<CsSingleLinkedListNode<DataT>>(next)
			, CsDataNodeT<DataT>(data)
		{

		}
	};
	typedef CsSingleLinkedListNode<DataT> Node;

public:
	CsSingleLinkedList();
	CsSingleLinkedList(const DataT &data);
	CsSingleLinkedList(const CsSingleLinkedList<DataT> &other);
	CsSingleLinkedList<DataT>& operator=(const CsSingleLinkedList<DataT> &other);
	virtual ~CsSingleLinkedList();

public:
	cs_void Invert();
	cs_bool IsEmpty() const;
	cs_size_t Size() const;
	cs_bool InsertBefore(cs_size_t pos, const DataT &data);
	cs_bool InsertAfter(cs_size_t pos, const DataT &data);
	cs_bool AddHead(const DataT &data);
	cs_bool AddTail(const DataT &data);
	virtual cs_void RemoveAt(cs_size_t pos);
	cs_void RemoveHead();
	cs_void RemoveTail();
	cs_void RemoveAll();
	DataT& GetTail();
	DataT  GetTail() const;
	DataT& GetHead();
	DataT  GetHead() const;
	DataT& GetAt(cs_size_t id);
	DataT  GetAt(cs_size_t id) const;
	cs_void SetAt(cs_size_t pos, const DataT &data);

	// 不存在则返回NULL_POS
	cs_size_t IndexOf(const DataT &data) const; 

	// 不存在则返回NULL_POS，存在则返回首节点的位置
	cs_size_t FindCircle() const;

	// 不存在则返回NULL_POS，存在则返回首节点的位置
	cs_size_t FindCross(const CsSingleLinkedList<DataT>& list);

	DataT &operator[](cs_size_t id);
	DataT operator[](cs_size_t id) const;

protected:
	cs_size_t m_nLength;
	Node *m_pHead;
};

#include "CsSingleLinkedList.inl"

#endif // _CORE_SINGLE_LINKED_LIST_H_