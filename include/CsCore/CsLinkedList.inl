#ifndef _CORE_LINKED_LIST_INLINE_
#define _CORE_LINKED_LIST_INLINE_

template<typename DataT, typename NodeT>
inline cs_uint CsLinkedList<DataT, NodeT>::ClassCode() const
{
	return CsLinkedList<DataT, NodeT>::CLASS_CODE;
}

#endif // _CORE_LINKED_LIST_INLINE_