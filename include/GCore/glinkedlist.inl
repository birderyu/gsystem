#ifndef _CORE_LINKED_LIST_INLINE_
#define _CORE_LINKED_LIST_INLINE_

namespace gnova { // gnova

template<typename DataT, typename NodeT>
GINLINE guint GLinkedList<DataT, NodeT>::ClassCode() const
{
	return GLinkedList<DataT, NodeT>::CLASS_CODE;
}

} // namespace gnova

#endif // _CORE_LINKED_LIST_INLINE_