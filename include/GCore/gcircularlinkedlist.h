/////////////////////////////////////////////////////////////////////////////////
/// @brief 循环链表（circular linked list）
/// 
///  循环链表的定义及实现
///  该版本的循环链表是概念上的，实际上链表的最后一个节点并未指向其头节点。
/// 
/// @author  birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_CIRCULAR_LINKED_LIST_H_
#define _CORE_CIRCULAR_LINKED_LIST_H_

#include "gsinglelinkedlist.h" 

template<typename DataT, typename NodeT = GSingleLinkedListNode<DataT>>
class GCircularLinkedList 
	: public GSingleLinkedList<DataT, NodeT>
{
public:
	GCircularLinkedList();

public:
	Node *GetNext();
	const Node *GetNext() const;
	gvoid RemoveAt(gsize pos);
	gsize GetCurrentIndex() const;
	Node *GetCurrentNode();
	const Node *GetCurrentNode() const;

protected:
	Node *m_pCursor;
};

#include "gcircularlinkedlist.inl"

#endif // _CORE_CIRCULAR_LINKED_LIST_H_