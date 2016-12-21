#ifndef _CORE_LINKED_LIST_INLINE_
#define _CORE_LINKED_LIST_INLINE_

template<typename DataT>
inline cs_uint CsLinkedList<DataT>::ClassCode() const
{
	return CsLinkedList<DataT>::CLASS_CODE;
}

#endif // _CORE_LINKED_LIST_INLINE_