#ifndef _CORE_LINKED_LIST_INLINE_
#define _CORE_LINKED_LIST_INLINE_

namespace gsystem { // gsystem

template<typename DataT, typename NodeT>
GINLINE guint GLinkedList<DataT, NodeT>::ClassCode() const
{
	return GLinkedList<DataT, NodeT>::CLASS_CODE;
}

} // namespace gsystem

#endif // _CORE_LINKED_LIST_INLINE_